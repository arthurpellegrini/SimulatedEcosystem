cmake_minimum_required(VERSION 3.28)
project(SimulatedEcosystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimulatedEcosystem main.cpp
        src/Simulation/SimulationView.h
        src/Simulation/SimulationView.cpp
        src/Simulation/Simulation.h
        src/Simulation/Simulation.cpp

        src/Save/UniverseExporter.h
        src/Save/UniverseExporter.cpp
        src/Save/UniverseImporter.h
        src/Save/UniverseImporter.cpp

        src/Universe/Universe.h
        src/Universe/Universe.cpp
        src/Universe/Cell.h
        src/Universe/Cell.cpp

        src/Animal/Gender.h
        src/Animal/Gender.cpp
        src/Animal/Animal.h
        src/Animal/Animal.cpp
        src/Animal/Wolf.h
        src/Animal/Wolf.cpp
        src/Animal/Sheep.h
        src/Animal/Sheep.cpp

        src/NaturalElement/NaturalElement.h
        src/NaturalElement/NaturalElement.cpp
        src/NaturalElement/SaltMinerals.h
        src/NaturalElement/SaltMinerals.cpp
        src/NaturalElement/Grass.h
        src/NaturalElement/Grass.cpp
)
