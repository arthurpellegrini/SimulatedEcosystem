#include "SimulationView.h"
#include "Center.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>


char SimulationView::_lineChar = '-';
char SimulationView::_cornerChar = '+';
char SimulationView::_verticalChar = '|';

int SimulationView::_cellWidth = 5;


SimulationView::SimulationView(const bool showCoordinates, const bool showQuantities, const bool showMessages,
                               const bool showGeneration)
    : _showCoordinates(showCoordinates), _showQuantities(showQuantities), _showMessages(showMessages),
      _showGeneration(showGeneration) {
}

SimulationView::SimulationView()
    : SimulationView(true, true, true, true) {
}

void SimulationView::display(Universe &universe) const {
    printUniverse(universe);

    printMessages(universe);

    printInformations(universe);
}

void SimulationView::printUniverse(Universe &universe) const {
    const vector<vector<Cell> > &cells = universe.getCells();
    const int nbCols = cells[0].size();
    char letter = 'A';
    int letterCount = 0;

    if (_showCoordinates) printSeparator(nbCols, true);
    for (int i = 0; i < cells.size(); ++i) {
        printSeparator(nbCols, false);

        if (_showCoordinates) {
            string rowLabel = "";
            if (letterCount > 0) {
                rowLabel += to_string(letterCount);
            }
            rowLabel += string(1, letter);

            cout << setw(_cellWidth) << centered(rowLabel) << _verticalChar;
            if (letter == 'Z') {
                letter = 'A';
                letterCount++;
            } else {
                letter++;
            }
        } else {
            cout << _verticalChar;
        }
        for (int y = 0; y < nbCols; ++y) {
            cout << setw(_cellWidth) << centered(cells[i][y].display()) << _verticalChar;
        }
        cout << endl;

        if (i == cells.size() - 1) {
            printSeparator(nbCols, false);
        }
    }
}

void SimulationView::printSeparator(const int cols, const bool isHeader) const {
    if (isHeader) {
        cout << setw(_cellWidth + 1) << " ";
        for (int i = 0; i < cols; ++i) {
            cout << setw(_cellWidth) << centered(to_string(i+1)) << " ";
        }
        cout << endl;
    } else {
        if (_showCoordinates) cout << setw(_cellWidth + 1) << _cornerChar;
        else cout << _cornerChar;
        const string side = string(_cellWidth, _lineChar) + string(1, _cornerChar);
        for (int i = 0; i < cols; ++i) {
            cout << setw(_cellWidth) << side;
        }
        cout << endl;
    }
}

void SimulationView::printMessages(Universe &universe) const {
    if (_showMessages) {
        vector<string> messages = universe.getMessages(universe.getGenerations());
        for (const auto& message: messages) {
            if (_showCoordinates) cout << setw(_cellWidth + 1) << " ";
            cout << message << endl;
        }
    }
}

void SimulationView::printInformations(const Universe &universe) const {
    if (_showCoordinates) cout << setw(_cellWidth + 1) << " ";
    if (_showQuantities && _showGeneration) {
        cout << setw(20) << centered("Generation: " + to_string(universe.getGenerations()));
        cout << _verticalChar << setw(20) << centered("Sheep: " + to_string(universe.getSheepQuantity()));
        cout << _verticalChar << setw(20) << centered("Wolf: " + to_string(universe.getWolfQuantity()));
        cout << endl << endl;
    } else if (_showGeneration) {
        cout << setw(60) << centered("Generation: " + to_string(universe.getGenerations()));
        cout << endl << endl;
    } else if (_showQuantities) {
        cout << setw(30) << centered("Sheep: " + to_string(universe.getSheepQuantity()));
        cout << _verticalChar << setw(30) << centered("Wolf: " + to_string(universe.getWolfQuantity()));
        cout << endl << endl;
    } else {
        cout << endl;
    }
}

vector<int> SimulationView::requestDimensions() {
    int x = getValidIntegerInput("How many rows ?");
    int y = getValidIntegerInput("How many columns ?");
    cout << '\n';
    return {x, y};
}

int SimulationView::requestSheepQuantity() {
    return getValidIntegerInput("How many sheeps ?");
}

int SimulationView::requestWolfQuantity() {
    return getValidIntegerInput("How many wolves ?");
}

int SimulationView::getValidIntegerInput(const string &prompt) {
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

char SimulationView::displayPauseMenu() {
    char choice;
    cout << "Simulation en pause:" << endl;
    cout << "Options: [r]esume, [e]xit, [s]ave, [l]oad" << endl;

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

void SimulationView::displayEndSimulation(const Universe &universe) {
    cout << "The universe is dead after " << universe.getGenerations() << " generations." << endl;
}
