#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationView.h"
#include "../Universe/Universe.h"
#include <atomic>

using namespace std;


class Simulation {
public:
    Simulation();
    void start();
    void pause();
    void resume();
    void stop();
    void save();
    void load();

private:
    Universe* universe;
    SimulationView* simulationView;
    atomic<bool> isPaused;
    atomic<bool> isStopped;

    void simulationLoop();
    void handlePauseMenu();
};

#endif // SIMULATION_H
