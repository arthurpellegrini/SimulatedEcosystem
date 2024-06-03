#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationView.h"
#include "../Universe/Universe.h"
#include <thread>
#include <atomic>

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
 std::atomic<bool> isPaused;
 std::atomic<bool> isStopped;

 void simulationLoop();
 void handlePauseMenu();
};

#endif // SIMULATION_H
