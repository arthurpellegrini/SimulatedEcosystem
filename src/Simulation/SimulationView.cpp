#include "SimulationView.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>


constexpr char LINE_CHAR = '-';
constexpr char CORNER_CHAR = '+';
constexpr char VERTICAL_CHAR = '|';

constexpr int CELL_WIDTH = 5;


SimulationView::SimulationView(bool showCoordinates, bool showQuantities, bool showMessages, bool showGeneration)
    : _showCoordinates(showCoordinates), _showQuantities(showQuantities), _showMessages(showMessages), _showGeneration(showGeneration) {}

SimulationView::SimulationView()
    : SimulationView(true, true, true, true) {}

void SimulationView::display(Universe& universe) {
    printUniverse(universe);


    if (_showCoordinates) cout << setw(CELL_WIDTH+1) << " ";
    // printMessages(universe);
    cout << "TODO: print messages" << endl;

    if (_showCoordinates) cout << setw(CELL_WIDTH+1) << " ";
    if (_showQuantities && _showGeneration) {
        cout << setw(20) << centered("Generation: " + to_string(universe.getGenerations()));
        cout << VERTICAL_CHAR << setw(20) << centered("Sheep: " + to_string(universe.getSheepQuantity()));
        cout << VERTICAL_CHAR << setw(20) << centered("Wolf: " + to_string(universe.getWolfQuantity()));
        cout << endl << endl;
    }
    else if (_showGeneration) {
        cout << setw(60) << centered("Generation: " + to_string(universe.getGenerations()));
        cout << endl << endl;
    }
    else if (_showQuantities) {
        cout << setw(30) << centered("Sheep: " + to_string(universe.getSheepQuantity()));
        cout << VERTICAL_CHAR << setw(30) << centered("Wolf: " + to_string(universe.getWolfQuantity()));
        cout << endl << endl;
    }
    else {
        cout << endl;
    }
}

void SimulationView::printUniverse(Universe& universe) {
    const vector<vector<Cell>>& cells = universe.getCells();
    const int nbCols = cells[0].size();
    char letter = 'A';

    if(_showCoordinates) printSeparator(nbCols, true);
    for (int i = 0; i < cells.size(); ++i) {
        printSeparator(nbCols, false);

        if(_showCoordinates) cout << setw(CELL_WIDTH) << centered(string(1, letter++)) << VERTICAL_CHAR;
        else cout << VERTICAL_CHAR;
        for (int y = 0; y < nbCols; ++y) {
            cout << setw(CELL_WIDTH) << centered(cells[i][y].display()) << VERTICAL_CHAR;

        }
        cout << endl;

        if (i == cells.size() - 1) {
            printSeparator(nbCols, false);
        }
    }
}

void SimulationView::printSeparator(int cols, bool header) const {
    if (header) {
        cout << setw(CELL_WIDTH+1) << " ";
        for (int i = 0; i < cols; ++i) {
            cout << setw(CELL_WIDTH) << centered(to_string(i)) << " ";
        }
        cout << endl;
    } else {
        if(_showCoordinates) cout <<  setw(CELL_WIDTH+1) << CORNER_CHAR;
        else cout << CORNER_CHAR;
        const string side = string(CELL_WIDTH, LINE_CHAR) + string(1, CORNER_CHAR);
        for (int i = 0; i < cols; ++i) {
            cout << setw(CELL_WIDTH) << side;
        }
        cout << endl;
    }
}

vector<int> SimulationView::requestDimensions() const {
    int x = getValidIntegerInput("How many rows ?");
    int y = getValidIntegerInput("How many columns ?");
    cout << '\n';
    return {x, y};
}

int SimulationView::getValidIntegerInput(const string& prompt) const {
    string input;
    int value;
    cout << prompt;
    while (true) {
        getline(cin, input);
        if (all_of(input.begin(), input.end(), ::isdigit)) {
            value = stoi(input);
            if (value > 0) {
                break;
            }
        }
        cout << "Not Integer ! " << prompt;
    }
    return value;
}

char SimulationView::displayPauseMenu() const {
    char choice;
    cout << "Simulation en pause:" << endl;
    cout << "Options: r => resume, e => exit, s => save, l => load" << endl;

    while (true) {
        choice = cin.get();
        if (choice == '\n' || choice == '\r') {
            continue;
        }
        if (choice == 'r' || choice == 'e' || choice == 's' || choice == 'l') {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entree invalide. Veuillez entrer un caractere unique parmi les options r, e, s, l :" << endl;
    }

    return choice;
}

void SimulationView::displayEndSimulation(Universe& universe) const {
    cout << "The universe is dead after " << universe.getGenerations() << " generations." << endl;
}
