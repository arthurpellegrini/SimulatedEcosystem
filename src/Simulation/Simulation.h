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
    Universe* _universe;
    SimulationView* _simulationView;
    atomic<bool> _isPaused;
    atomic<bool> _isStopped;

    void simulationLoop();
    void handlePauseMenu();

    static const vector<int> _dimensions;
};

#endif // SIMULATION_H
