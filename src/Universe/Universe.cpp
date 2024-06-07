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


// void Universe::processAnimalBreed(int x, int y) {
//     Cell& cell = _cells[x][y];
//
//     if (cell.hasAnimal()) {
//         Animal* animal = cell.getAnimal();
//         if (dynamic_cast<Sheep*>(animal)) {
//             processSheepBreed(x, y);
//         }
//         else if (dynamic_cast<Wolf*>(animal)) {
//             processWolfBreed(x, y);
//         }
//     }
// }
//
// bool Universe::placeRandomBabyAnimal(int x, int y, unique_ptr<Animal> animal) {
//     vector <pair<int, int>> possibleBirth = {
//         {x-1, y-1}, {x-1, y}, {x-1, y+1},
//         {x, y-1}, {x, y+1},
//         {x+1, y-1}, {x+1, y}, {x+1, y+1}
//     };
//
//     random_shuffle(possibleBirth.begin(), possibleBirth.end());
//
//     for(auto birthPosition : possibleBirth) {
//         // If in the grid
//         if(birthPosition.first >= 0 && birthPosition.first < _size[0] && birthPosition.second >= 0 && birthPosition.second < _size[1]) {
//             // If there is no animals
//             if(!_cells[birthPosition.first][birthPosition.second].hasAnimal()) {
//                 cout << "GEN" << _generations << ": Baby born at " << birthPosition.first << " " << birthPosition.second << endl;
//                 _cells[birthPosition.first][birthPosition.second].addAnimal(move(animal));
//                 return true;
//             }
//         }
//     }
//     cout << "GEN" << _generations << ": No place to give birth" << endl;
//     return false;
// }
//
// void Universe::processSheepBreed(int x, int y) {
//     Sheep sheep = *dynamic_cast<Sheep*>(_cells[x][y].getAnimal());
//
//     // Check neighboors that are sheeps to see if they can breed
//     vector<pair<int, int>> possibleMoves = {
//         {x-1, y-1}, {x-1, y}, {x-1, y+1},
//         {x, y-1}, {x, y+1},
//         {x+1, y-1}, {x+1, y}, {x+1, y+1}
//     };
//
//     for (auto move : possibleMoves) {
//         if (move.first >= 0 && move.first < _size[0] && move.second >= 0 && move.second < _size[1]) {
//             if (_cells[move.first][move.second].hasAnimal()) {
//                 Animal *neighboorAnimal = _cells[move.first][move.second].getAnimal();
//                 if (dynamic_cast<Sheep*>(neighboorAnimal)) {
//                     Sheep neighboorSheep = *dynamic_cast<Sheep*>(neighboorAnimal);
//                     if (sheep.canBreed(neighboorSheep)) {
//                         // if (rand() % 2 == 0) {
//                         bool hasBeenplaced = placeRandomBabyAnimal(x, y, make_unique<Sheep>(randomGender()));
//                         if (hasBeenplaced) {
//                             sheep.breed();
//                             neighboorSheep.breed();
//                             _sheepQuantity++;
//                         }
//                         // }
//                     }
//                 }
//             }
//         }
//     }
// }
//
//
// void Universe::processWolfBreed(int x, int y) {
//     Wolf wolf = *dynamic_cast<Wolf*>(_cells[x][y].getAnimal());
//
// }

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

        const vector<int> position = randomWolfPosition(x, y);
        Cell& nextCell = _cells[position[0]][position[1]];
        // TODO: Remove this debug message
        // cout << positionToString(position[0], position[1]) << "A wolf came from " + positionToString(x, y));
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
    const string pos = positionToString(x, y);

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

        const vector<int> position = randomSheepPosition(x, y);
        Cell& nextCell = _cells[position[0]][position[1]];
        // TODO: Remove this debug message
        // cout << positionToString(position[0], position[1]) << "A sheep came from " + positionToString(x, y));
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
            if(!cell.hasWolf()) {
                return {displacement.first, displacement.second};
            }
        }
    }

    return {x, y};
}

vector<pair<int, int>> Universe::findGrassWithinFov(int x, int y, int fov) const {
    vector<pair<int, int>> grassPositions;
    for (int i = -fov; i <= fov; ++i) {
        for (int j = -fov; j <= fov; ++j) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < _size[0] && ny >= 0 && ny < _size[1]) {
                if (_cells[nx][ny].hasGrass() && !_cells[nx][ny].hasAnimal()) {
                    grassPositions.emplace_back(nx, ny);
                }
            }
        }
        if (!grassPositions.empty()) {
            shuffle(grassPositions.begin(), grassPositions.end(), default_random_engine(rand()));
            return { grassPositions.front() };
        }
    }
    return grassPositions;
}

vector<int> Universe::randomSheepPosition(int x, int y) {
    int fov = 3; // Champ de vision du mouton

    vector<pair<int, int>> grassPositions = findGrassWithinFov(x, y, fov);
    if (!grassPositions.empty()) {
        // Trouver la position de l'herbe la plus proche
        pair<int, int> target = grassPositions[0];
        int minDistance = abs(target.first - x) + abs(target.second - y);
        for (const auto& pos : grassPositions) {
            int distance = abs(pos.first - x) + abs(pos.second - y);
            if (distance < minDistance) {
                target = pos;
                minDistance = distance;
            }
        }
        // Se déplacer vers la position cible
        int moveX = x + (target.first > x ? 1 : (target.first < x ? -1 : 0));
        int moveY = y + (target.second > y ? 1 : (target.second < y ? -1 : 0));

        if (!_cells[moveX][moveY].hasAnimal()) {
            return {moveX, moveY};
        }
    }

    // Si aucune herbe n'est trouvée dans le fov, faire un déplacement aléatoire comme avant
    map<pair<int, int>, Cell*> possibleMoves = neighboor(x, y);

    vector<pair<int, int>> positions;
    for (const auto& move : possibleMoves) {
        positions.push_back(move.first);
    }

    shuffle(positions.begin(), positions.end(), default_random_engine(rand()));

    for (auto displacement : positions) {
        if (displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            Cell& cell = _cells[displacement.first][displacement.second];
            if (!cell.hasAnimal()) {
                return {displacement.first, displacement.second};
            }
        }
    }

    return {x, y};
}




// Cell& Universe::getNextPreciseWolfPosition(int x, int y) {
//     int fov = 2;  // Champ de vision du loup
//
//     vector<pair<int, int>> sheepPositions;
//
//     // Rechercher les moutons dans le champ de vision
//     for (int i = -fov; i <= fov; ++i) {
//         for (int j = -fov; j <= fov; ++j) {
//             int nx = x + i;
//             int ny = y + j;
//
//             if (nx >= 0 && nx < _size[0] && ny >= 0 && ny < _size[1]) {
//                 if (_cells[nx][ny].hasAnimal() && dynamic_cast<Sheep*>(_cells[nx][ny].getAnimal())) {
//                     std::cout << "Sheep found at (" << nx << ", " << ny << ")" << std::endl;
//                     sheepPositions.emplace_back(nx, ny);
//                 }
//             }
//         }
//     }
//
//     // Vérifier s'il y a un mouton adjacent
//     for (const auto& position : sheepPositions) {
//         int sheepX = position.first;
//         int sheepY = position.second;
//
//         if (abs(sheepX - x) <= 1 && abs(sheepY - y) <= 1) {
//             return _nextCells[sheepX][sheepY];
//         }
//     }
//
//     // Si aucun mouton adjacent, se déplacer vers le mouton le plus proche
//     if (!sheepPositions.empty()) {
//         // Sélection du mouton le plus proche
//         int targetX = sheepPositions[0].first;
//         int targetY = sheepPositions[0].second;
//         int minDistance = abs(targetX - x) + abs(targetY - y);
//
//         for (const auto& position : sheepPositions) {
//             int distance = abs(position.first - x) + abs(position.second - y);
//             if (distance < minDistance) {
//                 targetX = position.first;
//                 targetY = position.second;
//                 minDistance = distance;
//             }
//         }
//
//         // Calcul du déplacement d'une case vers le mouton le plus proche
//         int moveX = x + (targetX > x ? 1 : (targetX < x ? -1 : 0));
//         int moveY = y + (targetY > y ? 1 : (targetY < y ? -1 : 0));
//
//         // Vérifier si la cellule cible est libre ou contient un mouton
//         if (!_nextCells[moveX][moveY].hasAnimal() || dynamic_cast<Sheep*>(_nextCells[moveX][moveY].getAnimal())) {
//             return _nextCells[moveX][moveY];
//         } else {
//             // Trouver une cellule adjacente libre ou contenant un mouton
//             vector<pair<int, int>> possibleMoves = {
//                     {moveX - 1, moveY - 1}, {moveX - 1, moveY}, {moveX - 1, moveY + 1},
//                     {moveX, moveY - 1},                     {moveX, moveY + 1},
//                     {moveX + 1, moveY - 1}, {moveX + 1, moveY}, {moveX + 1, moveY + 1}
//             };
//
//             for (const auto& move : possibleMoves) {
//                 int adjX = move.first;
//                 int adjY = move.second;
//                 if (adjX >= 0 && adjX < _size[0] && adjY >= 0 && adjY < _size[1]) {
//                     if (!_nextCells[adjX][adjY].hasAnimal() || dynamic_cast<Sheep*>(_nextCells[adjX][adjY].getAnimal())) {
//                         return _nextCells[adjX][adjY];
//                     }
//                 }
//             }
//         }
//     }
//
//     // Si aucun mouton n'est trouvé ou que toutes les cellules adjacentes sont occupées, déplacement aléatoire
//     return getNextRandomWolfPosition(x, y);
// }
//
// Cell& Universe::getNextPreciseSheepPosition(int x, int y) {
//     int fov = dynamic_cast<Sheep*>(_cells[x][y].getAnimal())->getFov();
//
//     vector<pair<int, int>> grassPositions;
//
//     for (int i = -fov; i <= fov; ++i) {
//         for (int j = -fov; j <= fov; ++j) {
//             int nx = x + i;
//             int ny = y + j;
//
//             if (nx >= 0 && nx < _size[0] && ny >= 0 && ny < _size[1]) {
//                 if (_cells[nx][ny].hasNaturalElement() && dynamic_cast<Grass*>(_cells[nx][ny].getNaturalElement())) {
//                     std::cout << "Grass found at (" << nx << ", " << ny << ")" << std::endl;
//                     grassPositions.emplace_back(nx, ny);
//                 }
//             }
//         }
//     }
//
//     for (const auto& position : grassPositions) {
//         std::cout << "(" << position.first << ", " << position.second << ")" << std::endl;
//     }
//
//     if (!grassPositions.empty()) {
//         // Sélection de la première herbe trouvée
//         int targetX = grassPositions[0].first;
//         int targetY = grassPositions[0].second;
//
//         // Calcul du déplacement d'une case vers l'herbe la plus proche
//         int moveX = x + (targetX > x ? 1 : (targetX < x ? -1 : 0));
//         int moveY = y + (targetY > y ? 1 : (targetY < y ? -1 : 0));
//
//         // Vérifier si la cellule cible est libre
//         if (!_nextCells[moveX][moveY].hasAnimal()) {
//             return _nextCells[moveX][moveY];
//         } else {
//             // Trouver une cellule adjacente libre
//             vector<pair<int, int>> possibleMoves = {
//                     {moveX - 1, moveY - 1}, {moveX - 1, moveY}, {moveX - 1, moveY + 1},
//                     {moveX, moveY - 1},                     {moveX, moveY + 1},
//                     {moveX + 1, moveY - 1}, {moveX + 1, moveY}, {moveX + 1, moveY + 1}
//             };
//
//             for (const auto& move : possibleMoves) {
//                 int adjX = move.first;
//                 int adjY = move.second;
//                 if (adjX >= 0 && adjX < _size[0] && adjY >= 0 && adjY < _size[1]) {
//                     if (!_nextCells[adjX][adjY].hasAnimal()) {
//                         return _nextCells[adjX][adjY];
//                     }
//                 }
//             }
//         }
//     }
//
//     // Si aucune herbe n'est trouvée ou que toutes les cellules adjacentes sont occupées, déplacement aléatoire
//     return getNextRandomSheepPosition(x, y);
// }

string Universe::positionToString(const int x, const int y) {
    const char letter = 'A' + x;
    return string(1, letter) + to_string(y);
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
