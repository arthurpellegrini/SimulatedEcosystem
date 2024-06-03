#include "Simulation.h"

Simulation::Simulation() : universe(nullptr) {
    simulationView = new SimulationView();
    const auto dimensions = simulationView->requestDimensions();
    universe = new Universe(dimensions);
}

void Simulation::start() {}
void Simulation::pause() {}
void Simulation::resume() {}
void Simulation::stop() {}
void Simulation::save() {}
void Simulation::load() {}
void Simulation::displayCells() {
    auto cells = universe->getCells();
    simulationView->displayCells(cells);
}
