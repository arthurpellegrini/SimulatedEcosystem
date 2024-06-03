#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>
#include "../Universe/Cell.h"

using namespace std;

class SimulationView {
public:
    void displayCells(const vector<vector<Cell>>& cells) const;
    vector<int> requestDimensions() const;

private:
    void printSeparator(int cols) const;
    int getValidIntegerInput(const string& prompt) const;
};

#endif // SIMULATIONVIEW_H
