#include "Universe.h"
#include "../Animal/Wolf.h"
#include "../Animal/Sheep.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"

Universe::Universe(int width, int height) : _size{width, height}, generations(0), isDied(false) {
    cells.resize(width, std::vector<Cell>(height));
    nextCells.resize(width, std::vector<Cell>(height));

    // Todo: Random generation of initial cells
}

Universe::Universe(const std::vector<int>& size) : _size(size), generations(0), isDied(false) {
    cells.resize(size[0], std::vector<Cell>(size[1]));
    nextCells.resize(size[0], std::vector<Cell>(size[1]));

    // Todo: Random generation of initial cells
}

void Universe::nextGeneration() {
    for (int i = 0; i < _size[0]; ++i) {
        for (int j = 0; j < _size[1]; ++j) {
            processCell(i, j);
        }
    }
    cells = std::move(nextCells);
    nextCells.resize(_size[0], std::vector<Cell>(_size[1]));
    generations++;
}

std::vector<std::vector<Cell>>& Universe::getCells() {
    return cells;
}

void Universe::processCell(int x, int y) {
    Cell& cell = cells[x][y];
    Cell& nextCell = nextCells[x][y];

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
        nextCell.addNaturalElement(std::make_unique<SaltMinerals>());
        cell.removeAnimal();
        return;
    }

    // Eating logic
    if (dynamic_cast<Grass*>(cell.getNaturalElement())) {
        sheep->eat();
        cell.removeNaturalElement();
    }

    // Breeding logic
    // ...
}

void Universe::processWolf(int x, int y, Cell& cell, Cell& nextCell) {
    Wolf* wolf = dynamic_cast<Wolf*>(cell.getAnimal());
    wolf->increaseAge();
    wolf->decreaseSatiety();

    if (wolf->getAge() > Wolf::getLifespan() || wolf->getSatiety() <= 0) {
        nextCell.addNaturalElement(std::make_unique<SaltMinerals>());
        cell.removeAnimal();
        return;
    }

    // Eating logic
    // ...

    // Breeding logic
    // ...
}

void Universe::processGrass(int x, int y, Cell& cell, Cell& nextCell) {
    nextCell.addNaturalElement(std::make_unique<Grass>());
}

void Universe::processMinerals(int x, int y, Cell& cell, Cell& nextCell) {
    nextCell.addNaturalElement(std::make_unique<Grass>());
}
