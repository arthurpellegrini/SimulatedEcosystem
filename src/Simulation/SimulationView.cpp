#include "SimulationView.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void SimulationView::displayCells(Universe& universe) const {
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
    int x = getValidIntegerInput("Entrez le nombre de lignes (x) :");
    int y = getValidIntegerInput("Entrez le nombre de colonnes (y) :");
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
    int value;
    cout << prompt;
    while (!(cin >> value) || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrée invalide. Veuillez entrer un nombre entier positif :";
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
    cout << "La simulation est terminée après " << universe.getGenerations() << " générations." << endl;
}
