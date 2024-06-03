#include "Universe.h"
#include "../Animal/Wolf.h"
#include "../Animal/Sheep.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"


Universe::Universe(const vector<int>& size) : _size(size), _generations(0), _isDead(false) {
    _cells.resize(size[0], vector<Cell>(size[1]));
    _nextCells.resize(size[0], vector<Cell>(size[1]));

    // Todo: Random generation of initial cells
}

void Universe::nextGeneration() {
    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            processCell(i, j);
        }
    }
    _cells = move(_nextCells);
    _nextCells.resize(_size[0], vector<Cell>(_size[1]));
    _generations++;
}

vector<vector<Cell>>& Universe::getCells() {
    return _cells;
}

bool Universe::isDead() {
    return _isDead;
}

void Universe::processCell(int x, int y) {
    Cell& cell = _cells[x][y];
    Cell& nextCell = _nextCells[x][y];

    if (cell.getAnimal() != nullptr) {
        if (dynamic_cast<Sheep*>(cell.getAnimal())) {
            processSheep(x, y, cell, nextCell);
        } else if (dynamic_cast<Wolf*>(cell.getAnimal())) {
            processWolf(x, y, cell, nextCell);
        }
    } else if (dynamic_cast<Grass*>(cell.getNaturalElement())) {
        processGrass(x, y, cell, nextCell);
    } else if (dynamic_cast<SaltMinerals*>(cell.getNaturalElement())) {
        processMinerals(x, y, cell, nextCell);
    }
}

void Universe::processSheep(int x, int y, Cell& cell, Cell& nextCell) {
    Sheep* sheep = dynamic_cast<Sheep*>(cell.getAnimal());
    sheep->increaseAge();
    sheep->decreaseSatiety();

    if (sheep->getAge() > Sheep::getLifespan() || sheep->getSatiety() <= 0) {
        nextCell.addNaturalElement(make_unique<SaltMinerals>());
        cell.removeAnimal();
        return;
    }

    // Eating logic
    if (dynamic_cast<Grass*>(cell.getNaturalElement())) {
        sheep->eat();
        cell.removeNaturalElement();
    }

    // Add movement and breeding logic here
}

void Universe::processWolf(int x, int y, Cell& cell, Cell& nextCell) {
    Wolf* wolf = dynamic_cast<Wolf*>(cell.getAnimal());
    wolf->increaseAge();
    wolf->decreaseSatiety();

    if (wolf->getAge() > Wolf::getLifespan() || wolf->getSatiety() <= 0) {
        nextCell.addNaturalElement(make_unique<SaltMinerals>());
        cell.removeAnimal();
        return;
    }

    // Add movement and breeding logic here
}

void Universe::processGrass(int x, int y, Cell& cell, Cell& nextCell) {
    nextCell.addNaturalElement(make_unique<Grass>());
}

void Universe::processMinerals(int x, int y, Cell& cell, Cell& nextCell) {
    SaltMinerals* minerals = dynamic_cast<SaltMinerals*>(cell.getNaturalElement());
    minerals->incrementAge();
    if (minerals->shouldTransform()) {
        nextCell.addNaturalElement(make_unique<Grass>());
    } else {
        nextCell.addNaturalElement(make_unique<SaltMinerals>(*minerals));
    }
}

int Universe::getGenerations() {
    return _generations;
}
