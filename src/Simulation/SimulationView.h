#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>
#include <string>
#include "../Universe/Cell.h"
#include "../Universe/Universe.h"
#include "Center.h"


using namespace std;

class SimulationView {
public:
    SimulationView(bool showCoordinates, bool showQuantities, bool showMessages, bool showGeneration);
    SimulationView();

    void displayCells(Universe& universe);
    void printUniverse(Universe& universe);
    vector<int> requestDimensions() const;
    char displayPauseMenu() const;
    void displayEndSimulation(Universe& universe) const;

private:
    void printSeparator(int cols, bool header) const;
    int getValidIntegerInput(const string& prompt) const;

    bool showCoordinates_;
    bool showQuantities_;
    bool showMessages_;
    bool showGeneration_;
};

#endif // SIMULATIONVIEW_H
