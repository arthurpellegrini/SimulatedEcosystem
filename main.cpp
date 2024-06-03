#include <iostream>

#include "Grass.h"
#include "Simulation.h"

int main() {
    try {
        Simulation simulation;
        simulation.displayField();

    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << '\n';
    }

    return 0;
}
