#include <fstream>
#include <sstream>
#include <limits>
#include "UniverseImporter.h"
#include "../NaturalElement/Grass.h"
#include "../NaturalElement/SaltMinerals.h"
#include "../Animal/Sheep.h"
#include "../Animal/Wolf.h"

Universe* UniverseImporter::importFromFile(const string &filename) {

    cout << "Importing universe from file: " << filename << endl;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return nullptr;
    }

    int rows, cols;
    inFile >> rows >> cols;

    inFile.ignore(numeric_limits<streamsize>::max(), '\n');

    Universe* universe = new Universe({rows, cols});

    string line;

    int numSheep = 0;
    int numWolves = 0;

    while (getline(inFile, line)) {
        istringstream iss(line);
        string part;
        int posX, posY;

        // Lire les éléments
        getline(iss, part, ';');
        posX = stoi(part);

        getline(iss, part, ';');
        posY = stoi(part);

        getline(iss, part, ';');
        char element1 = part[0];
        char element2 = part[1];
        char elements[] = {element1, element2};

        int age = -1;
        int satiety = -1;
        Gender gender = Gender::Male;

        if (element1 == 'S' || element1 == 'W') {
            cout << "Reading animal data" << endl;

            getline(iss, part, ';');
            age = stoi(part);

            getline(iss, part, ';');
            satiety = stoi(part);

            getline(iss, part, ';');
            char genderChar = part[0];
            gender = (genderChar == 'M' ? Gender::Male : Gender::Female);
        }

        Cell &cell = universe->getCell({posX, posY});

        for (char element : elements) {
            switch (element) {
                case 'W':
                {
                    unique_ptr<Wolf> wolf = make_unique<Wolf>(gender, age, satiety);
                    cell.addAnimal(move(wolf));
                    numWolves++;
                }
                    break;

                case 'S':
                {
                    unique_ptr<Sheep> sheep = make_unique<Sheep>(gender, age, satiety);
                    cell.addAnimal(move(sheep));
                    numSheep++;
                }
                    break;

                case ',':
                    cell.addNaturalElement(make_unique<Grass>());
                    break;

                case '*':
                    cell.addNaturalElement(make_unique<SaltMinerals>());
                    break;

                case ' ':
                    break;

                default:
                    cerr << "Element inconnu: " << element << endl;
                    break;
            }
        }
    }

    universe->setSheepQuantity(numSheep);
    universe->setWolfQuantity(numWolves);

    inFile.close();

    return universe;
}
