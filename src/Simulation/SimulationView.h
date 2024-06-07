#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>
#include <string>
#include "../Universe/Universe.h"

using namespace std;

class SimulationView {
public:
    SimulationView(bool showCoordinates, bool showQuantities, bool showMessages, bool showGeneration);
    SimulationView();

    void display(Universe& universe) const;
    void printUniverse(Universe& universe) const;

    static vector<int> requestDimensions();
    static int requestSheepQuantity();
    static int requestWolfQuantity();

    static char displayPauseMenu();
    static void displayEndSimulation(const Universe& universe);

private:
    void printSeparator(int cols, bool isHeader) const;
    void printMessages(Universe &universe) const;
    void printInformations(const Universe &universe) const;

    static int getValidIntegerInput(const string& prompt);

    bool _showCoordinates;
    bool _showQuantities;
    bool _showMessages;
    bool _showGeneration;

    static char _lineChar;
    static char _cornerChar;
    static char _verticalChar;
    static int _cellWidth;
};

#endif // SIMULATIONVIEW_H
