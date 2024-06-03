#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>
#include "../Universe/Cell.h"
#include "../Universe/Universe.h"

using namespace std;


class SimulationView {
public:
    void displayCells(Universe& universe) const;
    vector<int> requestDimensions() const;
    char displayPauseMenu() const;
    void displayEndSimulation(Universe& universe) const;

private:
    void printSeparator(int cols) const;
    int getValidIntegerInput(const string& prompt) const;
};

#endif // SIMULATIONVIEW_H
