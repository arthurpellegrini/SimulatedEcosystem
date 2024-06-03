#include "SimulationView.h"
#include <iostream>
#include <iomanip>
#include <limits>


// Définition de la méthode displayField
void SimulationView::displayField(std::vector<std::vector<Cell>>& field) {
 const int cellWidth = 2; // Largeur de chaque valeur (2 caractères)

 // Fonction pour afficher une ligne de séparation
 auto printSeparator = [&](int cols) {
  std::cout << '+';
  for (int i = 0; i < cols; ++i) {
   std::cout << "----+";
  }
  std::cout << '\n';
 };

 // Affichage du tableau avec bordures
 for ( const auto& row : field) {
  printSeparator(row.size()); // Ligne de séparation avant chaque ligne
  for ( const auto& element : row) {
   std::cout << "| " << std::setw(cellWidth) << element << ' ';
  }
  std::cout << "|\n";
 }
 printSeparator(field[0].size()); // Ligne de séparation finale
}

// Définition de la méthode askForDimensions
std::vector<int> SimulationView::requestDimensions() {
 int x, y;
 std::cout << "Entrez le nombre de lignes (x) :";
 while (!(std::cin >> x) || x <= 0) {
  std::cin.clear(); // Clear the error state of std::cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
  std::cout << "Entrée invalide. Veuillez entrer un nombre entier positif pour les lignes (x) :";
 }
 std::cout << "Entrez le nombre de colonnes (y) :";
 while (!(std::cin >> y) || y <= 0) {
  std::cin.clear(); // Clear the error state of std::cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
  std::cout << "Entrée invalide. Veuillez entrer un nombre entier positif pour les colonnes (y) :";
 }
 return {x, y};
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