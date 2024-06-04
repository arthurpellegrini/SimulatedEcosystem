#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "Cell.h"

using namespace std;


class Universe {
public:
    Universe(const vector<int>& size);

    void nextGeneration();
    vector<vector<Cell>>& getCells();
    bool isDead();
    int getGenerations();

private:
    vector<int> _size;
    int _generations;
    bool _isDead;

    vector<vector<Cell>> _cells;
    vector<vector<Cell>> _nextCells;

    static Gender randomGender();
    void placeRandomAnimal(unique_ptr<Animal> animal);

    void placeRandomNaturalElement(unique_ptr<NaturalElement> natural_element);

    void processCell(int x, int y);
    void processSheep(int x, int y, Cell& cell, Cell& nextCell);
    void processWolf(int x, int y, Cell& cell, Cell& nextCell);
    void processGrass(int x, int y, Cell& cell, Cell& nextCell);
    void processMinerals(int x, int y, Cell& cell, Cell& nextCell);

    static const float _percentageAnimal;
    static const float _percentageWolves;
    static const float _percentageSaltMinerals;
};

#endif // UNIVERSE_H
