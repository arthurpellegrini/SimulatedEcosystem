#include "Simulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>


Simulation::Simulation() : universe(nullptr), isPaused(false), isStopped(false) {
    simulationView = new SimulationView();
    const auto dimensions = simulationView->requestDimensions();
    universe = new Universe(dimensions);
    simulationView->displayCells(*universe);
}

void Simulation::start() {
    isStopped = false;
    isPaused = false;
    thread simThread(&Simulation::simulationLoop, this);
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
    cout << "WIP: Clément's method" << endl;
}

void Simulation::load() {
    cout << "WIP: Clément's method" << endl;
}

void Simulation::simulationLoop() {
    while (!isStopped) {
        if (!isPaused) {
            universe->nextGeneration();
            simulationView->displayCells(*universe);
        }

        if (_kbhit()) { 
            char key = _getch(); 
            if (key == 'p') {
                pause();
            } else if (key == 's') {
                stop();
            }
        }

        this_thread::sleep_for(chrono::seconds(1));
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
