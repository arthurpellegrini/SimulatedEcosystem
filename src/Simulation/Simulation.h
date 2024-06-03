#ifndef SIMULATION_H
#define SIMULATION_H
#include "SimulationView.h"
#include "../Universe/Universe.h"

class Simulation {
public:
 Simulation();

 void start();
 void pause();
 void resume();
 void stop();
 void save();
 void load();
 void displayCells();

private:
 Universe* universe;
 SimulationView* simulationView;

};

#endif //SIMULATION_H