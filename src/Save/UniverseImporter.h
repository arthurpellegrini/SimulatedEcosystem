//
// Created by Admin on 03/06/2024.
//

#ifndef SIMULATEDECOSYSTEM_UNIVERSEIMPORTER_H
#define SIMULATEDECOSYSTEM_UNIVERSEIMPORTER_H


#include "../Universe/Universe.h"

class UniverseImporter {
    public:
    static Universe* importFromFile(const std::string& filename);

};


#endif //SIMULATEDECOSYSTEM_UNIVERSEIMPORTER_H
