#include "SimulationView.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>


void SimulationView::displayCells(Universe& universe) const {
    cout << "Generation " << universe.getGenerations() << endl;

    const auto& cells = universe.getCells();
    for (const auto& row : cells) {
        printSeparator(row.size());
        for (const auto& element : row) {
            cout << "| " << element << " ";
        }
        cout << "|\n";
    }
    printSeparator(cells[0].size());
}

vector<int> SimulationView::requestDimensions() const {
    int x = getValidIntegerInput("How many rows ?");
    int y = getValidIntegerInput("How many columns ?");
    cout << '\n';
    return {x, y};
}

void SimulationView::printSeparator(int cols) const {
    cout << '+';
    for (int i = 0; i < cols; ++i) {
        cout << "----+";
    }
    cout << '\n';
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
