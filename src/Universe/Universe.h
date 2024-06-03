#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <memory>
#include "Cell.h"

using namespace std;

class Universe {
public:
    Universe(int width, int height);
    Universe(const vector<int>& size);

    void nextGeneration();
    vector<vector<Cell>>& getCells();

private:
    vector<int> _size;
    int generations;
    bool isDied;

    vector<vector<Cell>> cells;
    vector<vector<Cell>> nextCells;

    void processCell(int x, int y);
    void processSheep(int x, int y, Cell& cell, Cell& nextCell);
    void processWolf(int x, int y, Cell& cell, Cell& nextCell);
    void processGrass(int x, int y, Cell& cell, Cell& nextCell);
    void processMinerals(int x, int y, Cell& cell, Cell& nextCell);
};

#endif // UNIVERSE_H
