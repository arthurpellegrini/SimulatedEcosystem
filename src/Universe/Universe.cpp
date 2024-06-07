#include "Universe.h"

#include <cmath>
#include <algorithm>
#include <random>
#include <iterator>
#include <sstream>

#include "../Animal/Wolf.h"
#include "../Animal/Sheep.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"


Universe::Universe(const vector<int>& size) : Universe(size, 0, 0){
}

Universe::Universe(const vector<int>& size, const int sheepQuantity, const int wolfQuantity) :
    _size(size),
    _sheepQuantity(sheepQuantity),
    _wolfQuantity(wolfQuantity),
    _generations(0)
{
    _cells.resize(_size[0], vector<Cell>(_size[1]));

    generateRandomUniverse();
}

void Universe::generateRandomUniverse()
{
    srand(static_cast<unsigned>(time(nullptr)));

    if (_sheepQuantity + _wolfQuantity > _size[0] * _size[1]) {
        throw invalid_argument("The number of animals is greater than the number of cells");
    }

    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            _cells[i][j].addNaturalElement(make_unique<Grass>());
        }
    }

    vector<int> position;

    for (int i = 0; i < _wolfQuantity; ++i) {
        position = randomAnimalPosition();
        _cells[position[0]][position[1]].addAnimal(make_unique<Wolf>(randomGender()));
    }

    for (int i = 0; i < _sheepQuantity; ++i) {
        position = randomAnimalPosition();
        _cells[position[0]][position[1]].addAnimal(make_unique<Sheep>(randomGender()));
    }
}

vector<int> Universe::randomAnimalPosition() const {
    int x, y;
    do {
        x = rand() % _size[0];
        y = rand() % _size[1];
    } while (_cells[x][y].hasAnimal());

    return {x, y};
}

map<pair<int, int>, Cell *> Universe::neighboor(const int x, const int y) {
    map<pair<int, int>, Cell*> neighbors;

    const vector<pair<int, int>> moves = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto& move : moves) {
        int nx = x + move.first;
        int ny = y + move.second;

        if (nx >= 0 && nx < _size[0] && ny >= 0 && ny < _size[1]) {
            neighbors[{nx, ny}] = &_cells[nx][ny];
        }
    }

    return neighbors;
}

void Universe::nextGeneration() {
    _generations++;

    processNaturalElements();
    processAnimals();
}

void Universe::processNaturalElements() {
    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            if (_cells[i][j].hasSaltMinerals()) {
                processSaltMinerals(i, j);
            }
        }
    }
}

void Universe::processSaltMinerals(const int x, const int y) {
    NaturalElement* naturalElement = _cells[x][y].getNaturalElement();
    SaltMinerals& saltMinerals = *dynamic_cast<SaltMinerals*>(naturalElement);
    saltMinerals.incrementAge();

    if (saltMinerals.shouldTransform()) {
        _cells[x][y].removeNaturalElement();
        _cells[x][y].addNaturalElement(make_unique<Grass>());
        addMessage({x, y}, "Grass grew again");
    }
}

void Universe::processAnimals() {
    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            if (_cells[i][j].hasAnimal())
                _cells[i][j].getAnimal()->resetCanMove();
        }
    }

    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            if (_cells[i][j].hasWolf() && _cells[i][j].getAnimal()->canMove()) processWolf(i, j);
        }
    }

    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            if (_cells[i][j].hasSheep() && _cells[i][j].getAnimal()->canMove()) processSheep(i, j);
        }
    }
}

void Universe::processWolf(const int x, const int y) {
    Wolf wolf = *dynamic_cast<Wolf*>(_cells[x][y].getAnimal());
    wolf.move();
    wolf.increaseAge();

    if(wolf.isOldAgeDead()) {
        _cells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _wolfQuantity--;
        addMessage({x, y},"A wolf dies of old age");
    } else if(wolf.isHungerDead()) {
        _cells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _wolfQuantity--;
        addMessage({x, y},"A wolf dies of hunger");
    } else {
        wolf.decreaseSatiety();

        if (wolf.getGender() == Gender::Female && wolf.canBreed()) {
            breedWolf(x, y, wolf);
        }

        const vector<int> position = randomWolfPosition(x, y);
        Cell& nextCell = _cells[position[0]][position[1]];

        if (position[0] != x || position[1] != y)
            addMessage({position[0], position[1]}, "A wolf moves");

        if(nextCell.hasSheep()) {
            nextCell.removeAnimal();
            _sheepQuantity--;
            wolf.eat();
            addMessage({position[0], position[1]}, "A wolf eats a sheep");
        }
        _cells[x][y].removeAnimal();
        nextCell.addAnimal(make_unique<Wolf>(wolf));
    }
}

void Universe::processSheep(const int x, const int y) {
    Sheep sheep = *dynamic_cast<Sheep*>(_cells[x][y].getAnimal());
    sheep.move();
    sheep.increaseAge();

    if(sheep.isOldAgeDead()) {
        _cells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _sheepQuantity--;
        addMessage({x, y}, "A sheep dies of old age");
    } else if(sheep.isHungerDead()) {
        _cells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _sheepQuantity--;
        addMessage({x, y}, "A sheep dies of hunger");
    } else {
        sheep.decreaseSatiety();

        if (sheep.getGender() == Gender::Female && sheep.canBreed()) {
            breedSheep(x, y, sheep);
        }

        const vector<int> position = randomSheepPosition(x, y);
        Cell& nextCell = _cells[position[0]][position[1]];

        if (position[0] != x || position[1] != y)
            addMessage({position[0], position[1]}, "A sheep moves");

        if(nextCell.hasGrass()) {
            nextCell.removeNaturalElement();
            sheep.eat();
            addMessage({position[0], position[1]}, "A sheep ate grass");
        }
        _cells[x][y].removeAnimal();
        nextCell.addAnimal(make_unique<Sheep>(sheep));
    }
}

vector<int> Universe::randomWolfPosition(int x, int y) {
    map<pair<int, int>, Cell*> possibleMoves = neighboor(x, y);

    vector<pair<int, int>> positions;
    for (const auto& move : possibleMoves) {
        positions.push_back(move.first);
    }

    shuffle(positions.begin(), positions.end(), default_random_engine(rand()));

    for(auto displacement : positions) {
        if(displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            Cell& cell = _cells[displacement.first][displacement.second];
            if(cell.hasSheep()) { // Prioritize cells with sheep
                return {displacement.first, displacement.second};
            }
        }
    }

    // If no cell with a sheep is found, return a random position
    for(auto displacement : positions) {
        if(displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            Cell& cell = _cells[displacement.first][displacement.second];
            if(!cell.hasAnimal()) {
                return {displacement.first, displacement.second};
            }
        }
    }

    return {x, y};
}

vector<int> Universe::randomSheepPosition(int x, int y) {
    map<pair<int, int>, Cell*> possibleMoves = neighboor(x, y);

    vector<pair<int, int>> positions;
    for (const auto& move : possibleMoves) {
        positions.push_back(move.first);
    }

    shuffle(positions.begin(), positions.end(), default_random_engine(rand()));

    for(auto displacement : positions) {
        if(displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            Cell& cell = _cells[displacement.first][displacement.second];
            if(cell.hasGrass() && !cell.hasAnimal()) { // Prioritize cells with grass
                return {displacement.first, displacement.second};
            }
        }
    }

    // If no cell with grass is found, return a random position
    for(auto displacement : positions) {
        if(displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            Cell& cell = _cells[displacement.first][displacement.second];
            if(!cell.hasAnimal()) {
                return {displacement.first, displacement.second};
            }
        }
    }

    return {x, y};
}

void Universe::breedWolf(const int x, const int y, Wolf& wolf) {
    map<pair<int, int>, Cell*> neighbors = neighboor(x, y);

    bool hasBred = false;

    for (const auto& neighbor : neighbors) {
        if (neighbor.second->hasWolf()) {
            Wolf& otherWolf = *dynamic_cast<Wolf*>(neighbor.second->getAnimal());
            if (wolf.canBreedWith(otherWolf)) {
                hasBred = true;
            }
        }
    }

    if (hasBred) {
        vector<pair<int, int>> position;
        for (const auto& move : neighbors) {
            position.push_back(move.first);
        }

        shuffle(position.begin(), position.end(), default_random_engine(rand()));

        for(auto babyPosition : position) {
            if(babyPosition.first >= 0 && babyPosition.first < _size[0] && babyPosition.second >= 0 && babyPosition.second < _size[1]) {
                if(!_cells[babyPosition.first][babyPosition.second].hasAnimal()) {
                    _cells[babyPosition.first][babyPosition.second].addAnimal(make_unique<Wolf>(randomGender()));
                    _wolfQuantity++;
                    wolf.breed();
                    addMessage({babyPosition.first, babyPosition.second}, "A baby wolf is born");
                    break;
                }
            }
        }
    }
}

void Universe::breedSheep(const int x, const int y, Sheep& sheep) {
    map<pair<int, int>, Cell*> neighbors = neighboor(x, y);

    bool hasBred = false;

    for (const auto& neighbor : neighbors) {
        if (neighbor.second->hasSheep()) {
            Sheep& otherSheep = *dynamic_cast<Sheep*>(neighbor.second->getAnimal());
            if (sheep.canBreedWith(otherSheep)) {
                hasBred = true;
            }
        }
    }

    if (hasBred) {
        vector<pair<int, int>> position;
        for (const auto& move : neighbors) {
            position.push_back(move.first);
        }

        shuffle(position.begin(), position.end(), default_random_engine(rand()));

        for(auto babyPosition : position) {
            if(babyPosition.first >= 0 && babyPosition.first < _size[0] && babyPosition.second >= 0 && babyPosition.second < _size[1]) {
                if(!_cells[babyPosition.first][babyPosition.second].hasAnimal()) {
                    _cells[babyPosition.first][babyPosition.second].addAnimal(make_unique<Sheep>(randomGender()));
                    _sheepQuantity++;
                    sheep.breed();
                    addMessage({babyPosition.first, babyPosition.second}, "A baby sheep is born");
                    break;
                }
            }
        }
    }
}

string Universe::positionToString(const int x, const int y) {
    const char letter = 'A' + x;
    return string(1, letter) + to_string(y+1);
}

void Universe::addMessage(const pair<int, int>& coordinates, const string &message) {
    if (_messages.empty() || _messages.back().first != _generations) {
        _messages.push_back({_generations, {}});
    }
    _messages.back().second[message].push_back(coordinates);
}

string join(const vector<string>& vec, const char* delim)
{
    stringstream res;
    copy(vec.begin(), vec.end(), ostream_iterator<string>(res, delim));
    string result = res.str();
    return result.substr(0, result.length() - 2);  // enlève le délimiteur en trop à la fin
}

vector<string> Universe::getMessages(const int generation) {
    vector<string> result;
    for (const auto& gen_messages : _messages) {
        if (gen_messages.first == generation) {
            for (const auto& msg : gen_messages.second) {
                vector<string> coords;
                for (const auto& coord : msg.second) {
                    coords.push_back(positionToString(coord.first, coord.second));
                }
                string message = msg.first + " [" + join(coords, ", ") + "]";
                result.push_back(message);
            }
            break;
        }
    }
    return result;
}

int Universe::getGenerations() const {
    return _generations;
}

vector<vector<Cell>>& Universe::getCells() {
    return _cells;
}

Cell& Universe::getCell(const pair<int, int>& coordinates) {
    return _cells[coordinates.first][coordinates.second];
}

int Universe::getSheepQuantity() const {
    return _sheepQuantity;
}

int Universe::getWolfQuantity() const {
    return _wolfQuantity;
}

bool Universe::isDead() const {
    return _wolfQuantity == 0 && _sheepQuantity == 0;
}

void Universe::setSheepQuantity(const int sheepQuantity) {
    _sheepQuantity = sheepQuantity;
}

void Universe::setWolfQuantity(const int wolfQuantity) {
    _wolfQuantity = wolfQuantity;
}
