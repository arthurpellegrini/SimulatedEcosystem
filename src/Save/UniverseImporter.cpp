//
// Created by Admin on 03/06/2024.
//

#include <fstream>
#include <sstream>
#include <limits>
#include "UniverseImporter.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"
#include "../Animal/Sheep.h"
#include "../Animal/Wolf.h"

Universe UniverseImporter::importFromFile(const std::string &filename) {

    std::cout << "Importing universe from file: " << filename << std::endl;
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return Universe({0, 0});
    }

    int rows, cols;
    inFile >> rows >> cols;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Universe universe({rows, cols});

    std::string line;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string part;
        int posX, posY;

        std::getline(iss, part, ';');
        posX = std::stoi(part);

        std::getline(iss, part, ';');
        posY = std::stoi(part);

        // Lire les éléments
        std::getline(iss, part, ';');
        char element1 = part[0];
        char element2 = part[1];

        std::cout << "Importing elements " << element1 << " and " << element2 << " at position (" << posX << ", " << posY << ")" << std::endl;

        Cell& cell = universe.getCell({posX, posY});

        char elements[] = {element1, element2};

        for (char element : elements) {
            switch (element) {
                case 'W':
                    cell.addAnimal(std::make_unique<Wolf>(Gender::Male)); // Assumons que tous les loups importés sont des mâles
                    break;

                case 'S':
                    cell.addAnimal(std::make_unique<Sheep>(Gender::Male)); // Assumons que tous les moutons importés sont des mâles
                    break;

                case 'G':
                    cell.addNaturalElement(std::make_unique<Grass>());
                    break;

                case 'M':
                    cell.addNaturalElement(std::make_unique<SaltMinerals>());
                    break;

                case ' ':
                    break;

                default:
                    std::cerr << "Element inconnu: " << element << std::endl;
                    break;
            }
        }
    }

    inFile.close();

    return universe;
}
