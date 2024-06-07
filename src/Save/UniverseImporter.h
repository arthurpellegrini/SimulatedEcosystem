#ifndef SIMULATEDECOSYSTEM_UNIVERSEIMPORTER_H
#define SIMULATEDECOSYSTEM_UNIVERSEIMPORTER_H


#include "../Universe/Universe.h"

class UniverseImporter {
    public:
    static Universe* importFromFile(const string& filename);

};


#endif //SIMULATEDECOSYSTEM_UNIVERSEIMPORTER_H
