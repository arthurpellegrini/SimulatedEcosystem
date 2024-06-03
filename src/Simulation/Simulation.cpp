#include "Simulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h> // Pour _kbhit et _getch

Simulation::Simulation() : universe(nullptr), isPaused(false), isStopped(false) {
    simulationView = new SimulationView();
    const auto dimensions = simulationView->requestDimensions();
    universe = new Universe(dimensions);
    simulationView->displayCells(*universe);
}

void Simulation::start() {
    isStopped = false;
    isPaused = false;
    std::thread simThread(&Simulation::simulationLoop, this);
    simThread.join();
}

void Simulation::pause() {
    isPaused = true;
    handlePauseMenu();
}

void Simulation::resume() {
    isPaused = false;
}

void Simulation::stop() {
    isStopped = true;
}

void Simulation::save() {
    std::cout << "WIP: Clément's method" << std::endl;
}

void Simulation::load() {
    std::cout << "WIP: Clément's method" << std::endl;
}

void Simulation::simulationLoop() {
    while (!isStopped) {
        if (!isPaused) {
            universe->nextGeneration();
            simulationView->displayCells(*universe);
        }

        if (_kbhit()) { // Check if a key has been pressed
            char key = _getch(); // Read the pressed key
            if (key == 'p') { // Pause key
                pause();
            } else if (key == 's') { // Stop key
                stop();
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second
    }

    simulationView->displayEndSimulation(*universe);
}

void Simulation::handlePauseMenu() {
    char choice = simulationView->displayPauseMenu();
    switch (choice) {
        case 'r':
            resume();
        break;
        case 'e':
            stop();
        break;
        case 's':
            save();
        break;
        case 'l':
            load();
        break;
        default:
            break;
    }
}
