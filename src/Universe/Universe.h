#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "Cell.h"

using namespace std;

class Universe {
public:
    Universe(int width, int height);
    Universe(const vector<int> &size);

    void nextGeneration();
    vector<vector<Cell>>& getCells();

private:
    int width;
    int height;
    int generations;
    bool isDied;

    vector<vector<Cell>> cells;
    vector<vector<Cell>> nextCells;
};

#endif //UNIVERSE_H
