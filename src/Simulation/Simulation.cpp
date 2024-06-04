#include "Simulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

const vector<int> Simulation::_dimensions = {10, 10};

Simulation::Simulation() : _universe(nullptr), _isPaused(false), _isStopped(false) {
    _simulationView = new SimulationView();
    // const auto dimensions = simulationView->requestDimensions();
    _universe = new Universe(_dimensions);
    _simulationView->displayCells(*_universe);
}

void Simulation::start() {
    _isStopped = false;
    _isPaused = false;
    thread simThread(&Simulation::simulationLoop, this);
    simThread.join();
}

void Simulation::pause() {
    _isPaused = true;
    handlePauseMenu();
}

void Simulation::resume() {
    _isPaused = false;
}

void Simulation::stop() {
    _isStopped = true;
}

void Simulation::save() {
    cout << "WIP: Clément's method" << endl;
}

void Simulation::load() {
    cout << "WIP: Clément's method" << endl;
}

void Simulation::simulationLoop() {
    while (!_isStopped) {
        if (!_isPaused) {
            _universe->nextGeneration();
            _simulationView->displayCells(*_universe);
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

    _simulationView->displayEndSimulation(*_universe);
}

void Simulation::handlePauseMenu() {
    char choice = _simulationView->displayPauseMenu();
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
