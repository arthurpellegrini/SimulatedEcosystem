/**
 * Project Untitled
 */


#include "Simulation.h"

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
    return;
}

/**
 * @return void
 */
void Simulation::pause() {
    return;
}

/**
 * @return void
 */
void Simulation::resume() {
    return;
}

/**
 * @return void
 */
void Simulation::stop() {
    return;
}

/**
 * @return void
 */
void Simulation::save() {
    return;
}

/**
 * @return void
 */
void Simulation::load() {
    return;
}

/**
 * @return void
 */
void Simulation::displayField() {
    simulationView->displayField(universe->getField());
}
