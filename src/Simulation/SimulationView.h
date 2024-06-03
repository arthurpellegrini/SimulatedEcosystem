#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>

#include "../Universe/Cell.h"

class SimulationView {
public:
 // Méthode pour afficher le champ
    void displayField(std::vector<std::vector<Cell>>& field); // Méthode pour demander les dimensions et les retourner sous forme de vecteur
    std::vector<int> requestDimensions();
};

#endif // SIMULATIONVIEW_H
