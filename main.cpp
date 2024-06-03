#include <iostream>

#include "src/Simulation/Simulation.h"

int main() {
    try {
        Simulation simulation;
        simulation.displayCells();

    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << '\n';
    }

    return 0;
}
