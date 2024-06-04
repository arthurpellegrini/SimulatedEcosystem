#include "UniverseExporter.h"
#include <iostream>
#include <fstream>
#include <ctime>

void UniverseExporter::exportToFile(const std::string &filename, Universe &universe) {
    // Get the current date and time
    std::time_t t = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "_%d-%m-%Y_%H-%M-%S", std::localtime(&t));

    // Create the filename
    std::string dateFilename = filename + std::string(buffer) + ".txt";

    std::ofstream outFile(dateFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    const std::vector<std::vector<Cell>> &field = universe.getCells();
    int rows = field.size();
    int cols = rows > 0 ? field[0].size() : 0;

    // Affiche dans la console les dimensions de l'univers
    std::cout << "Dimensions de l'univers: " << rows << " x " << cols << std::endl;

    outFile << rows << " " << cols << std::endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outFile << i << ";" << j << "; " << field[i][j] << std::endl;
        }
    }

    outFile.close();
}
