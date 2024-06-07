#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>
#include <string>
#include "../Universe/Universe.h"
#include "Center.h"

using namespace std;

class SimulationView {
public:
    SimulationView(bool showCoordinates, bool showQuantities, bool showMessages, bool showGeneration);
    SimulationView();

    void display(Universe& universe) const;
    void printUniverse(Universe& universe) const;
    vector<int> requestDimensions() const;
    char displayPauseMenu() const;
    void displayEndSimulation(Universe& universe) const;

private:
    void printSeparator(int cols, bool isHeader) const;

    void printMessages(Universe &universe) const;

    void printInformations(const Universe &universe) const;

    int getValidIntegerInput(const string& prompt) const;

    bool _showCoordinates;
    bool _showQuantities;
    bool _showMessages;
    bool _showGeneration;
};

#endif // SIMULATIONVIEW_H
