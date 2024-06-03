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



char SimulationView::displayPauseMenu() {
 char choice;

 std::cout << "Vous avez mis la generation en pause :" << std::endl;
 std::cout << "Selectionnez une des options suivantes : r=>resume, e=>exit, s=>save, l=>load" << std::endl;

 while (true) {
  choice = std::cin.get();

  // Ignorer les caractères de nouvelle ligne ou de retour chariot
  if (choice == '\n' || choice == '\r') {
   continue;
  }

  // Vérifier si l'entrée est l'une des options valides
  if (choice == 'r' || choice == 'e' || choice == 's' || choice == 'l') {
   break; // Sortir de la boucle si l'entrée est valide
  }

  // Entrée invalide, afficher un message d'erreur
  std::cin.clear(); // Effacer l'état d'erreur de std::cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer l'entrée invalide
  std::cout << "Entree invalide. Veuillez entrer un caractere unique parmi les options r, e, s, l :" << std::endl;
 }

 return choice;

}


void SimulationView::displayEndSimulation(Universe& universe) {

 std::cout << "La simulation est finis, merci pour tous il faut faire une méthode display de l'univers pour recap le nombre de gen etc." /*<< univers->display()*/<< std::endl;
}