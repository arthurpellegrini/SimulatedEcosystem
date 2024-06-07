#include "Simulation.h"
#include "../Save/UniverseExporter.h"
#include "../Save/UniverseImporter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <filesystem>

const vector<int> Simulation::_dimensions = {5, 10};
int Simulation::_sheepQuantity = 5;
int Simulation::_wolfQuantity = 2;

Simulation::Simulation() : _universe(nullptr), _isPaused(false), _isStopped(false) {
    _simulationView = new SimulationView();
    // const auto dimensions = SimulationView::requestDimensions();
    // const auto sheepQuantity = SimulationView::requestSheepQuantity();
    // const auto wolfQuantity = SimulationView::requestWolfQuantity();
    try {
        _universe = new Universe(_dimensions, _sheepQuantity, _wolfQuantity, 0, true); // FOR TEST PURPOSES
        // _universe = new Universe(dimensions, sheepQuantity, wolfQuantity, 0, true);
    } catch (const exception& e) {
        cerr << "Error : " << e.what() << '\n';
    }

    _simulationView->display(*_universe);
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
    string fileName = UniverseExporter::exportToFile("save", _universe);
    ifstream file(fileName);
    if (file.good()) {
        cout << "Universe saved to " << fileName << endl;
    } else {
        cout << "Error: Could not save universe" << endl;
    }
    pause();
}

void Simulation::load() {
// On vérifie que le dossier 'save' existe ou non
    if (!filesystem::exists("save")) {
        cout << "Error: No save register, restart simulation." << endl;
        return;
    }

    // On vérifie que le dossier 'save' n'est pas vide
    if (filesystem::is_empty("save")) {
        cout << "Error: No save register, restart simulation." << endl;
        return;
    }

    vector<string> files;
    int index = 0;

    for (const auto &entry : filesystem::directory_iterator("save")) {
        cout << index << ": " << entry.path().filename() << endl;
        files.push_back(entry.path().string());
        index++;
    }

    cout << "Enter the index of the file to load: ";
    int fileIndex;
    cin >> fileIndex;

    if (fileIndex >= 0 && fileIndex < files.size()) {
        const string fileName = files[fileIndex];
        Universe* newUniverse = UniverseImporter::importFromFile(fileName);
        if (newUniverse) {
            delete _universe;
            _universe = newUniverse;
            _simulationView->display(*_universe);
            cout << "Universe loaded from " << fileName << endl;
        } else {
            cout << "Error: Could not load universe from " << fileName << endl;
        }
    } else {
        cout << "Invalid index" << endl;
    }

    pause();
}


void Simulation::simulationLoop() {
    while (!_isStopped) {
        if (!_isPaused) {
            if (!_universe->isDead()) {
                _universe->nextGeneration();
                _simulationView->display(*_universe);
            } else {
                SimulationView::displayEndSimulation(*_universe);
                stop();
                break;
            }
        }

        if (_kbhit()) {
            const char key = _getch();
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
    switch (SimulationView::displayPauseMenu()) {
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
