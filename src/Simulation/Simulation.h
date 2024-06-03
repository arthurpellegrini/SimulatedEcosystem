/**
 * Project Untitled
 */


#ifndef _SIMULATION_H
#define _SIMULATION_H
#include "SimulationView.h"
#include "../Universe/Universe.h"

class Simulation {
public:

 // Constructeur
 Simulation();
    
 void start();
    
 void pause();
    
 void resume();
    
 void stop();
    
 void save();
    
 void load();

 void displayField();

private:
 Universe* universe;
 SimulationView* simulationView;

};

#endif //_SIMULATION_H