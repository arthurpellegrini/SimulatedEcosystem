#include "Universe.h"

#include <algorithm>
#include <cmath>

#include "../Animal/Wolf.h"
#include "../Animal/Sheep.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"


Universe::Universe(const vector<int>& size) : Universe(size, 0, 0){
}

Universe::Universe(const vector<int>& size, int sheepQuantity, int wolfQuantity) : _size(size), _generations(0), _sheepQuantity(sheepQuantity), _wolfQuantity(wolfQuantity) {
    _cells.resize(_size[0], vector<Cell>(_size[1]));
    _nextCells.resize(_size[0], vector<Cell>(_size[1]));

    generateRandomUniverse();
}

void Universe::generateRandomUniverse() {
    srand(static_cast<unsigned>(time(nullptr)));

    const int totalCells = _size[0] * _size[1];
    const int totalAnimals = _sheepQuantity + _wolfQuantity;

    // Formaliser une erreur si le nombre d'animaux est supérieur au nombre de cellules
    if (totalAnimals > totalCells) {
        throw invalid_argument("The number of animals is greater than the number of cells");
        exit(0);
    }
    //
    //
    // const int totalAnimals = floor(totalCells * _percentageAnimal);
    // const int totalWolves = floor(totalAnimals * _percentageWolves);
    // const int totalSheep = totalAnimals - totalWolves;
    //
    // const int totalSaltMinerals = floor(totalCells * _percentageSaltMinerals);
    // const int totalGrass = totalCells - totalSaltMinerals;

    for (int x = 0; x < _size[0]; ++x) {
        for (int y = 0; y < _size[1]; ++y) {
            _cells[x][y].addNaturalElement(make_unique<Grass>());
        }
    }

    for (int i = 0; i < _wolfQuantity; ++i) {
        auto wolf = make_unique<Wolf>(randomGender());
        placeRandomAnimal(move(wolf));
    }

    for (int i = 0; i < _sheepQuantity; ++i) {
        auto sheep = make_unique<Sheep>(randomGender());
        placeRandomAnimal(move(sheep));
    }

    // for (int i = 0; i < totalSaltMinerals; ++i) {
    //     auto salt_minerals = make_unique<SaltMinerals>();
    //     placeRandomNaturalElement(move(salt_minerals));
    // }
    //
    // for (int i = 0; i < totalGrass; ++i) {
    //     auto grass = make_unique<Grass>();
    //     placeRandomNaturalElement(move(grass));
    // }
}

Gender Universe::randomGender() {
    return rand() % 2 == 0 ? Gender::Male : Gender::Female;
}

void Universe::placeRandomAnimal(unique_ptr<Animal> animal) {
    int x, y;
    do {
        x = rand() % _size[0];
        y = rand() % _size[1];
    } while (_cells[x][y].hasAnimal());

    _cells[x][y].addAnimal(move(animal));
}

void Universe::placeRandomNaturalElement(unique_ptr<NaturalElement> natural_element) {
    int x, y;
    do {
        x = rand() % _size[0];
        y = rand() % _size[1];
    } while (_cells[x][y].hasNaturalElement());

    _cells[x][y].addNaturalElement(move(natural_element));
}

void Universe::nextGeneration() {
    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            processNaturalElement(i, j);
        }
    }

    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            processAnimal(i, j);
        }
    }

    _cells = move(_nextCells);
    _nextCells.resize(_size[0], vector<Cell>(_size[1]));
    _generations++;
}

void Universe::processNaturalElement(int x, int y) {
    Cell& cell = _cells[x][y];

    if (cell.hasNaturalElement()) {
        NaturalElement* naturalElement = cell.getNaturalElement();

        if (dynamic_cast<Grass*>(naturalElement)) {
            processGrass(x, y);
        } else if (dynamic_cast<SaltMinerals*>(naturalElement)) {
            processSaltMinerals(x, y);
        }
    }
}


void Universe::processGrass(int x, int y) {
    Grass* grass = dynamic_cast<Grass*>(_cells[x][y].getNaturalElement());
    _nextCells[x][y].addNaturalElement(make_unique<Grass>(*grass));
    _cells[x][y].removeNaturalElement();
}

void Universe::processSaltMinerals(int x, int y) {
    SaltMinerals* saltMinerals = dynamic_cast<SaltMinerals*>(_cells[x][y].getNaturalElement());
    saltMinerals->incrementAge();

    if (saltMinerals->shouldTransform()) {
        _nextCells[x][y].addNaturalElement(make_unique<Grass>());
    } else {
        _nextCells[x][y].addNaturalElement(make_unique<SaltMinerals>(*saltMinerals));
    }

    _cells[x][y].removeNaturalElement();
}

void Universe::processAnimal(int x, int y) {
    Cell& cell = _cells[x][y];

    if (cell.hasAnimal()) {
        Animal* animal = cell.getAnimal();
        if (dynamic_cast<Sheep*>(animal)) {
            processSheep(x, y);
        } else if (dynamic_cast<Wolf*>(animal)) {
            processWolf(x, y);
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

        if(nextCell.hasNaturalElement()) {
            if(dynamic_cast<Grass*>(nextCell.getNaturalElement())) {
                sheep.eat();
                nextCell.removeNaturalElement();
            }
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

        if(nextCell.hasAnimal()) {
            if(dynamic_cast<Sheep*>(nextCell.getAnimal())) {
                wolf.eat();
                nextCell.removeAnimal();
                _sheepQuantity--;
            }
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
