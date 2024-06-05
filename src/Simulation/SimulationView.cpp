#include "SimulationView.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>


const char line = '-';
const char corner = '+';
const char vertical = '|';

const int width = 5;


SimulationView::SimulationView(bool showCoordinates, bool showQuantities, bool showMessages, bool showGeneration)
    : showCoordinates_(showCoordinates), showQuantities_(showQuantities), showMessages_(showMessages), showGeneration_(showGeneration) {}

SimulationView::SimulationView()
    : SimulationView(true, true, true, true) {}

void SimulationView::displayCells(Universe& universe) {
    printUniverse(universe);

    if (showCoordinates_) cout << setw(width+1) << " ";
    if (showQuantities_ && showGeneration_) {
        cout << setw(20) << centered("Generation: " + to_string(universe.getGenerations()));
        cout << vertical << setw(20) << centered("Sheep: " + to_string(universe.getSheepQuantity()));
        cout << vertical << setw(20) << centered("Wolf: " + to_string(universe.getWolfQuantity()));
        cout << endl << endl;
    }
    else if (showGeneration_) {
        cout << setw(60) << centered("Generation: " + to_string(universe.getGenerations()));
        cout << endl << endl;
    }
    else if (showQuantities_) {
        cout << setw(30) << centered("Sheep: " + to_string(universe.getSheepQuantity()));
        cout << vertical << setw(30) << centered("Wolf: " + to_string(universe.getWolfQuantity()));
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

    if(showCoordinates_) printSeparator(nbCols, true);
    for (int i = 0; i < cells.size(); ++i) {
        printSeparator(nbCols, false);

        if(showCoordinates_) cout << setw(width) << centered(string(1, letter++)) << vertical;
        else cout << vertical;
        for (int y = 0; y < nbCols; ++y) {
            cout << setw(width) << centered(cells[i][y].display()) << vertical;

        }
        cout << endl;

        if (i == cells.size() - 1) {
            printSeparator(nbCols, false);
        }
    }
}

void SimulationView::printSeparator(int cols, bool header) const {
    if (header) {
        cout << setw(width+1) << " ";
        for (int i = 0; i < cols; ++i) {
            cout << setw(width) << centered(to_string(i)) << " ";
        }
        cout << endl;
    } else {
        if(showCoordinates_) cout <<  setw(width+1) << corner;
        else cout << corner;
        const string side = string(width, line) + string(1, corner);
        for (int i = 0; i < cols; ++i) {
            cout << setw(width) << side;
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
