cmake_minimum_required(VERSION 3.28)
project(SimulatedEcosystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimulatedEcosystem main.cpp
        src/Universe/Universe.cpp
        src/Simulation/Simulation.cpp
        src/Simulation/SimulationView.cpp
        src/Universe/Cell.cpp
        src/Entity/NaturalElement/NaturalElement.cpp
        src/Entity/Animal/Animal.cpp
        src/Entity/NaturalElement/Grass.cpp
        src/Entity/NaturalElement/SaltMinerals.cpp
        src/Entity/Animal/Wolf.cpp
        src/Entity/Animal/Sheep.cpp
        src/Save/UniverseExporter.cpp
        src/Save/UniverseImporter.h
        src/Save/UniverseImporter.cpp
        src/Entity/Animal/Gender.cpp
        src/Entity/Entity.cpp)
