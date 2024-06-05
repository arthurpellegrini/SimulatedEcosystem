#include "Simulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

const vector<int> Simulation::_dimensions = {10, 10};

Simulation::Simulation() : _universe(nullptr), _isPaused(false), _isStopped(false) {
    _simulationView = new SimulationView();
    // const auto dimensions = simulationView->requestDimensions();
    try {
        _universe = new Universe(_dimensions, 20, 2);
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << '\n';
    }

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
            if (!_universe->isDead()) {
                _universe->nextGeneration();
                _simulationView->displayCells(*_universe);
            } else {
                _simulationView->displayEndSimulation(*_universe);
                stop();
                break;
            }
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
