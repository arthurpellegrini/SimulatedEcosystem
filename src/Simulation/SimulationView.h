#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <vector>

#include "../Universe/Cell.h"
#include "../Universe/Universe.h"

class SimulationView {
public:
 // Méthode pour afficher le champ
    void displayField(std::vector<std::vector<Cell>>& field); // Méthode pour demander les dimensions et les retourner sous forme de vecteur
    std::vector<int> requestDimensions();

    char displayPauseMenu();
    void displayEndSimulation(Universe& universe);
};

#endif // SIMULATIONVIEW_H
