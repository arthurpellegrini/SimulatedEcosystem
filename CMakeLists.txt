cmake_minimum_required(VERSION 3.28)
project(SimulatedEcosystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimulatedEcosystem main.cpp
        Universe.cpp
        Simulation.cpp
        SimulationView.cpp)
