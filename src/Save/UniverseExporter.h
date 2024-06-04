//
// Created by Admin on 03/06/2024.
//

#ifndef SIMULATEDECOSYSTEM_UNIVERSEEXPORTER_H
#define SIMULATEDECOSYSTEM_UNIVERSEEXPORTER_H


#include <string>
#include "../Universe/Universe.h"

class UniverseExporter {
    public:
        static void exportToFile(const std::string& filename, Universe& universe);
};


#endif //SIMULATEDECOSYSTEM_UNIVERSEEXPORTER_H
