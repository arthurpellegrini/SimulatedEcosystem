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

        // Lire les éléments
        std::getline(iss, part, ';');
        posX = std::stoi(part);

        std::getline(iss, part, ';');
        posY = std::stoi(part);

        std::getline(iss, part, ';');
        char element1 = part[0];
        char element2 = part[1];
        char elements[] = {element1, element2};

        int age = -1;
        int satiety = -1;
        Gender gender = Gender::Male;

        if (element1 == 'S' || element1 == 'W') {
            std::cout << "Reading animal data" << std::endl;

            std::getline(iss, part, ';');
            age = std::stoi(part);

            std::getline(iss, part, ';');
            satiety = std::stoi(part);

            std::getline(iss, part, ';');
            char genderChar = part[0];
            gender = (genderChar == 'M' ? Gender::Male : Gender::Female);
        }

        //std::cout << "Importing elements " << element1 << " and " << element2 << " at position (" << posX << ", " << posY << ")" << std::endl;

        Cell &cell = universe.getCell({posX, posY});

        for (char element : elements) {
            std::cout << "Importing element " << element << std::endl;
            switch (element) {
                case 'W':
                {
                    std::unique_ptr<Wolf> wolf = std::make_unique<Wolf>(age , satiety, gender);
                    cell.addAnimal(std::move(wolf));
                }
                    break;

                case 'S':
                {
                    std::unique_ptr<Sheep> sheep = std::make_unique<Sheep>(age, satiety, gender);
                    cell.addAnimal(std::move(sheep));
                }
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
