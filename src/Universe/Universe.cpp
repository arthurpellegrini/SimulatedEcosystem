#include "Universe.h"

#include <algorithm>
#include <cmath>

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

void Universe::nextGeneration() {
    processNaturalElements();
    processAnimals();

    _cells = move(_nextCells);
    _generations++;
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
            if (_cells[i][j].hasWolf()) {
                processWolf(i, j);
            }
        }
    }

    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            if (_cells[i][j].hasSheep()) {
                processSheep(i, j);
            }
        }
    }
}

void Universe::processSheep(int x, int y) {
    Sheep sheep = *dynamic_cast<Sheep*>(_cells[x][y].getAnimal());
    sheep.increaseAge();

    if(sheep.isDead()) { // Mort Naturelle
        _nextCells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _sheepQuantity--;
    } else {
        sheep.decreaseSatiety();

        Cell& nextCell = getNextRandomSheepPosition(x, y);

        if(nextCell.hasGrass()) {
            sheep.eat();
            nextCell.removeNaturalElement();
        }
        nextCell.addAnimal(make_unique<Sheep>(sheep));
    }
}


void Universe::processWolf(int x, int y) {
    Wolf wolf = *dynamic_cast<Wolf*>(_cells[x][y].getAnimal());
    wolf.increaseAge();

    if(wolf.isDead()) { // Mort Naturelle
        _nextCells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _wolfQuantity--;
    } else {
        wolf.decreaseSatiety();

        Cell& nextCell = getNextRandomWolfPosition(x, y);

        if(nextCell.hasSheep()) {
            wolf.eat();
            nextCell.removeAnimal();
            _sheepQuantity--;
        }
        nextCell.addAnimal(make_unique<Wolf>(wolf));
    }
}

Cell& Universe::getNextRandomSheepPosition(int x, int y) {
    vector <pair<int, int>> possibleMoves = {
        {x-1, y-1}, {x-1, y}, {x-1, y+1},
        {x, y-1}, {x, y+1},
        {x+1, y-1}, {x+1, y}, {x+1, y+1}
    };

    random_shuffle(possibleMoves.begin(), possibleMoves.end());

    for(auto move : possibleMoves) {
        // If in the grid
        if(move.first >= 0 && move.first < _size[0] && move.second >= 0 && move.second < _size[1]) {
            // If there is no animals
            if(!_nextCells[move.first][move.second].hasAnimal()) {
                return _nextCells[move.first][move.second];
            }
        }
    }

    return _nextCells[x][y];
}

Cell& Universe::getNextRandomWolfPosition(int x, int y) {
    vector <pair<int, int>> possibleMoves = {
        {x-1, y-1}, {x-1, y}, {x-1, y+1},
        {x, y-1}, {x, y+1},
        {x+1, y-1}, {x+1, y}, {x+1, y+1}
    };

    random_shuffle(possibleMoves.begin(), possibleMoves.end());

    for(auto move : possibleMoves) {
        // If in the grid
        if(move.first >= 0 && move.first < _size[0] && move.second >= 0 && move.second < _size[1]) {
            // If there is no wolf
            if (dynamic_cast<Sheep*>(_nextCells[move.first][move.second].getAnimal()) || !_nextCells[move.first][move.second].hasAnimal()) {
                return _nextCells[move.first][move.second];
            }
        }
    }
    return _nextCells[x][y];
}

int Universe::getGenerations() {
    return _generations;
}

vector<vector<Cell>>& Universe::getCells() {
    return _cells;
}

Cell& Universe::getCell(const pair<int, int>& coordinates) {
    return _cells[coordinates.first][coordinates.second];
}

int Universe::getSheepQuantity() {
    return _sheepQuantity;
}

int Universe::getWolfQuantity() {
    return _wolfQuantity;
}

bool Universe::isDead() {
    return _wolfQuantity == 0 && _sheepQuantity == 0;
}

void Universe::setSheepQuantity(int sheepQuantity) {
    _sheepQuantity = sheepQuantity;
}

void Universe::setWolfQuantity(int wolfQuantity) {
    _wolfQuantity = wolfQuantity;
}
