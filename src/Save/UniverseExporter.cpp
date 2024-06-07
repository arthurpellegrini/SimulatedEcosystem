#include "UniverseExporter.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>

string UniverseExporter::exportToFile(const string &filename, Universe* universe) {
    time_t t = time(nullptr);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "_%d-%m-%Y_%H-%M-%S", localtime(&t));

    string dateFilename = "save/" + filename + string(buffer) + ".txt";

    filesystem::create_directories("save");

    ofstream outFile(dateFilename);

    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return "";
    }

    const vector<vector<Cell>> &field = universe->getCells();
    int rows = field.size();
    int cols = rows > 0 ? field[0].size() : 0;

    outFile << rows << " " << cols << endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int posX = i;
            int posY = j;

            int age = -1;
            int satiety = -1;
            string gender = "N";

            const Cell &cell = field[i][j];
            if (cell.hasAnimal()) {
                Animal *animal = cell.getAnimal();
                age = animal->getAge();
                satiety = animal->getSatiety();
                gender = (animal->getGender() == Gender::Male ? "M" : "F");
                outFile << posX << ";" << posY << ";" << cell << ";" << age << ";" << satiety << ";" << gender << endl;
            }
            else {
                outFile << posX << ";" << posY << ";" << cell << endl;
            }
        }
    }

    outFile.close();
    return dateFilename;
}
