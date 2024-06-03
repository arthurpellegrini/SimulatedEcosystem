/**
 * Project Untitled
 */


#include "Simulation.h"

#include <thread>
#include <chrono>
#include <conio.h> // Pour _kbhit et _getch

/**
 * Simulation implementation
 */
// Constructeur

Simulation::Simulation() : universe(nullptr) {

    simulationView = new SimulationView();
    universe = new Universe(simulationView->requestDimensions());
}


/**
 * @return void
 */
void Simulation::start() {
    while (!universe->getisDead()) {
        if (_kbhit()) { // Vérifie si une touche a été pressée
            _getch();// Lit la touche pressée pour vider le buffer
            pause(); // Appelle la fonction pause
        }

        if (!universe->getisDead()) {

            std::cout<< "j'ai mis en commentaire les vrais fonctions a decommenter. Qaund ca sera finis"<< std::endl;
            //universe->nextGeneration();
            //simulationView->displayField(universe->getField());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Attend 0,2 secondes
    }
}

/**
 * @return void
 */
void Simulation::pause() {
    switch (simulationView->displayPauseMenu()) {
        case 'r' : break;
        case 'e' :
            stop();
            break;
        case 's' :
            save();
            break;
        case 'l' :
            load();
            break;
        default: pause();
    }
}

/**
 * @return void
 */
void Simulation::resume() { // sert a rien au final
}

/**
 * @return void
 */
void Simulation::stop() {
    universe->setisDead(true);
    simulationView->displayEndSimulation(*universe);
}

/**
 * @return void
 */
void Simulation::save() {
    std::cout<< "SAVE on ajoute le methode de clement"<< std::endl;
}

/**
 * @return void
 */
void Simulation::load() {
    std::cout<< "LAOD on ajoute le methode de clement"<< std::endl;
}

/**
 * @return void
 */
void Simulation::displayField() {
    simulationView->displayField(universe->getField());
}
