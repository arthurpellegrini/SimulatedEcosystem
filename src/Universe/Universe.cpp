#include "Universe.h"

#include <algorithm>
#include <cmath>
#include <random>

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

void Universe::processWolf(int x, int y) {
    Wolf wolf = *dynamic_cast<Wolf*>(_cells[x][y].getAnimal());
    wolf.move();
    wolf.increaseAge();
    string pos = positionToString(x, y);

    if(wolf.isDead()) { // Mort Naturelle
        _cells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _wolfQuantity--;
        // cout << "GEN" << _generations << ": Wolf died at " << pos << endl;
    } else {
        wolf.decreaseSatiety();

        vector<int> position = randomWolfPosition(x, y);
        Cell& nextCell = _cells[position[0]][position[1]];
        string nextPos = positionToString(position[0], position[1]);
        // cout << "GEN" << _generations << ": Wolf moved from " << pos << " to " << nextPos << endl;

        if(nextCell.hasSheep()) {
            nextCell.removeAnimal();
            _sheepQuantity--;
            wolf.eat();
            cout << "GEN" << _generations << ": Wolf ate sheep at " << nextPos << endl;
        }
        _cells[x][y].removeAnimal();
        nextCell.addAnimal(make_unique<Wolf>(wolf));
    }
}

void Universe::processSheep(const int x, const int y) {
    Sheep sheep = *dynamic_cast<Sheep*>(_cells[x][y].getAnimal());
    sheep.move();
    sheep.increaseAge();
    string pos = positionToString(x, y);

    if(sheep.isDead()) { // Mort Naturelle
        _cells[x][y].addNaturalElement(make_unique<SaltMinerals>());
        _cells[x][y].removeAnimal();
        _sheepQuantity--;
        // cout << "GEN" << _generations << ": Sheep died at " << pos << endl;
    } else {
        sheep.decreaseSatiety();

        vector<int> position = randomSheepPosition(x, y);
        Cell& nextCell = _cells[position[0]][position[1]];
        string nextPos = positionToString(position[0], position[1]);

        // cout << "GEN" << _generations << ": Sheep moved from " << pos << " to " << nextPos << endl;

        if(nextCell.hasGrass()) {
            nextCell.removeNaturalElement();
            sheep.eat();
            // cout << "GEN" << _generations << ": Sheep ate grass at " << nextPos << endl;
        }
        _cells[x][y].removeAnimal();
        nextCell.addAnimal(make_unique<Sheep>(sheep));
    }
}

vector<int> Universe::randomWolfPosition(int x, int y) {
    vector <pair<int, int>> possibleMoves = {
        {x-1, y-1}, {x-1, y}, {x-1, y+1},
        {x, y-1}, {x, y+1},
        {x+1, y-1}, {x+1, y}, {x+1, y+1}
    };

    // random_shuffle(possibleMoves.begin(), possibleMoves.end());
    shuffle(possibleMoves.begin(), possibleMoves.end(), default_random_engine(rand()));

    for(auto displacement : possibleMoves) {
        // If in the grid
        if(displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            // If there is no animals
            Cell& cell = _cells[displacement.first][displacement.second];
            if(!cell.hasWolf() || cell.hasSheep()) {
                return {displacement.first, displacement.second};
            }
        }
    }
    return {x, y};
}

vector<int> Universe::randomSheepPosition(int x, int y) {
    vector <pair<int, int>> possibleMoves = {
        {x-1, y-1}, {x-1, y}, {x-1, y+1},
        {x, y-1}, {x, y+1},
        {x+1, y-1}, {x+1, y}, {x+1, y+1}
    };

    // random_shuffle(possibleMoves.begin(), possibleMoves.end());
    shuffle(possibleMoves.begin(), possibleMoves.end(), default_random_engine(rand()));

    for(auto displacement : possibleMoves) {
        // If in the grid
        if(displacement.first >= 0 && displacement.first < _size[0] && displacement.second >= 0 && displacement.second < _size[1]) {
            // If there is no animals
            if(!_cells[displacement.first][displacement.second].hasAnimal()) {
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
    char coordX = 'A';
    coordX += x;
    return string(1, coordX) + to_string(y);
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
