#include "UniverseExporter.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>

string UniverseExporter::exportToFile(const std::string &filename, Universe* universe) {
    std::time_t t = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "_%d-%m-%Y_%H-%M-%S", std::localtime(&t));

    std::string dateFilename = "save/" + filename + std::string(buffer) + ".txt";

    std::filesystem::create_directories("save");

    std::ofstream outFile(dateFilename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return "";
    }

    const std::vector<std::vector<Cell>> &field = universe->getCells();
    int rows = field.size();
    int cols = rows > 0 ? field[0].size() : 0;

    outFile << rows << " " << cols << std::endl;

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
                outFile << posX << ";" << posY << ";" << cell << ";" << age << ";" << satiety << ";" << gender << std::endl;
            }
            else {
                outFile << posX << ";" << posY << ";" << cell << std::endl;
            }
        }
    }

    outFile.close();
    return dateFilename;
}
