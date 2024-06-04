cmake_minimum_required(VERSION 3.28)
project(SimulatedEcosystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimulatedEcosystem main.cpp
        src/Universe/Universe.cpp
        src/Simulation/Simulation.cpp
        src/Simulation/SimulationView.cpp
        src/Universe/Cell.cpp
        src/NaturalElement/NaturalElement.cpp
        src/Animal/Animal.cpp
        src/NaturalElement/Grass.cpp
        src/NaturalElement/SaltMinerals.cpp
        src/Animal/Wolf.cpp
        src/Animal/Sheep.cpp
        src/Save/UniverseExporter.cpp
        src/Save/UniverseImporter.h
        src/Save/UniverseImporter.cpp)
