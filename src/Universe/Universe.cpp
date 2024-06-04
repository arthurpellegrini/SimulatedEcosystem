#include "Universe.h"

#include <algorithm>
#include <cmath>

#include "../Animal/Wolf.h"
#include "../Animal/Sheep.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"

const float Universe::_percentageAnimal = 0.10;
const float Universe::_percentageWolves = 0.20;
const float Universe::_percentageSaltMinerals = 0.10;


Universe::Universe(const vector<int>& size) : _size(size), _generations(0), _isDead(false) {
    _cells.resize(size[0], vector<Cell>(size[1]));
    _nextCells.resize(size[0], vector<Cell>(size[1]));

    srand(static_cast<unsigned>(time(nullptr)));

    const int totalCells = size[0] * size[1];
    const int totalAnimals = floor(totalCells * _percentageAnimal);
    const int totalWolves = floor(totalAnimals * _percentageWolves);
    const int totalSheep = totalAnimals - totalWolves;

    const int totalSaltMinerals = floor(totalCells * _percentageSaltMinerals);
    const int totalGrass = totalCells - totalSaltMinerals;

    for (int i = 0; i < totalWolves; ++i) {
        auto wolf = make_unique<Wolf>(randomGender());
        placeRandomAnimal(move(wolf));
    }

    for (int i = 0; i < totalSheep; ++i) {
        auto sheep = make_unique<Sheep>(randomGender());
        placeRandomAnimal(move(sheep));
    }

    for (int i = 0; i < totalSaltMinerals; ++i) {
        auto salt_minerals = make_unique<SaltMinerals>();
        placeRandomNaturalElement(move(salt_minerals));
    }

    for (int i = 0; i < totalGrass; ++i) {
        auto grass = make_unique<Grass>();
        placeRandomNaturalElement(move(grass));
    }
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
    // Dans cette fonction, l'idée est de déplacer progressivement les entitées vers la prochaine génération
    // On déplace vers la case à la même position sur l'autre tableau
    // Voici l'ordre:

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

vector<vector<Cell>>& Universe::getCells() {
    return _cells;
}

Cell& Universe::getCell(const pair<int, int>& coordinates) {
    return _cells[coordinates.first][coordinates.second];
}

bool Universe::isDead() {
    return _isDead;
}

void Universe::processNaturalElement(int x, int y) {
    Cell& cell = _cells[x][y];
    Cell& nextCell = _nextCells[x][y];

    auto naturalElement = cell.getNaturalElement();
    if (cell.hasNaturalElement()) {

        // 1. SaltMinerals -> Les faire évoluer en grass
        // 2. Grass -> Rien de spécial à faire

        if (dynamic_cast<Grass*>(naturalElement)) {
            nextCell.addNaturalElement(make_unique<Grass>(*dynamic_cast<Grass*>(naturalElement))); // On garde l'herbe
            cell.removeNaturalElement();
        } else if (dynamic_cast<SaltMinerals*>(naturalElement)) {
            dynamic_cast<SaltMinerals*>(naturalElement)->incrementAge();
            if (dynamic_cast<SaltMinerals*>(naturalElement)->shouldTransform()) {
                nextCell.addNaturalElement(make_unique<Grass>());
                cell.removeNaturalElement();
            } else { // On garde les minéraux
                nextCell.addNaturalElement(make_unique<SaltMinerals>(*dynamic_cast<SaltMinerals*>(naturalElement)));
                cell.removeNaturalElement();
            }
        }
    }
}

void Universe::processAnimal(int x, int y) {
    Cell& cell = _cells[x][y];

    if (cell.hasAnimal()) {
        auto animal = cell.getAnimal();

        if (dynamic_cast<Sheep*>(animal)) {
            Sheep sheep = *dynamic_cast<Sheep*>(animal);
            sheep.increaseAge();

            if(!sheep.isDead()) {
                sheep.decreaseSatiety();

                Cell& nextCell = getNextRandomPosition(x, y);

                if(nextCell.hasNaturalElement()) {
                    if(dynamic_cast<Grass*>(nextCell.getNaturalElement())) {
                        sheep.eat();
                        nextCell.removeNaturalElement();
                    }
                }

                nextCell.addAnimal(make_unique<Sheep>(sheep));
            } else { // Mort Naturelle
                Cell& nextCell = _nextCells[x][y];
                nextCell.addNaturalElement(make_unique<SaltMinerals>());
                cell.removeAnimal();
            }

        }

        // 4. Wolf -> Les faire se déplacer sur une case aléatoire adjacente, si possible sinon rester au même endroit
        // Si le wolf n'est pas à sa max satiété alors manger le sheep (si existant) sur la case sur laquelle il a été déplacé
    }
}


Cell& Universe::getNextRandomPosition(int x, int y) {
    // 8 directions possibles
    vector <pair<int, int>> possibleMoves = {
        {x-1, y-1}, {x-1, y}, {x-1, y+1},
        {x, y-1}, {x, y+1},
        {x+1, y-1}, {x+1, y}, {x+1, y+1}
    };

    random_shuffle(possibleMoves.begin(), possibleMoves.end());

    for(auto move : possibleMoves) {
        if(move.first >= 0 && move.first < _size[0] && move.second >= 0 && move.second < _size[1]) {
            if(!_nextCells[move.first][move.second].hasAnimal()) {
                return _nextCells[move.first][move.second];
            }
        }
    }

    return _nextCells[x][y];
}
//
// void Universe::processSheep(int x, int y, Cell& cell, Cell& nextCell) {
//     Sheep* sheep = dynamic_cast<Sheep*>(cell.getAnimal());
//     sheep->increaseAge();
//     sheep->decreaseSatiety();
//
//     if (sheep->getAge() > Sheep::getLifespan() || sheep->getSatiety() <= 0) {
//         nextCell.addNaturalElement(make_unique<SaltMinerals>());
//         cell.removeAnimal();
//         return;
//     }
//
//     // Eating logic
//     if (dynamic_cast<Grass*>(cell.getNaturalElement())) {
//         sheep->eat();
//         cell.removeNaturalElement();
//     }
//
//     // Add movement and breeding logic here
// }
//
// void Universe::processWolf(int x, int y, Cell& cell, Cell& nextCell) {
//     Wolf* wolf = dynamic_cast<Wolf*>(cell.getAnimal());
//     wolf->increaseAge();
//     wolf->decreaseSatiety();
//
//     if (wolf->getAge() > Wolf::getLifespan() || wolf->getSatiety() <= 0) {
//         nextCell.addNaturalElement(make_unique<SaltMinerals>());
//         cell.removeAnimal();
//         return;
//     }
//
//     // Add movement and breeding logic here
// }

int Universe::getGenerations() {
    return _generations;
}
