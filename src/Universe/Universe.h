#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "Cell.h"

using namespace std;


class Universe {
public:
    Universe(const vector<int>& size);
    Universe(const vector<int>& size, int sheepQuantity, int wolfQuantity);

    void nextGeneration();
    bool isDead();
    int getGenerations();

    vector<vector<Cell>>& getCells();
    Cell& getCell(const std::pair<int, int>& coordinates);
    int getSheepQuantity();
    int getWolfQuantity();

    void setSheepQuantity(int sheepQuantity);
    void setWolfQuantity(int wolfQuantity);


private:
    vector<int> _size;

    int _sheepQuantity;
    int _wolfQuantity;

    int _generations;

    vector<vector<Cell>> _cells;
    vector<vector<Cell>> _nextCells;

    void generateRandomUniverse();

    vector<int> randomAnimalPosition() const;

    vector<int> randomAnimalPosition(unique_ptr<Animal> animal) const;
    void placeRandomNaturalElement(unique_ptr<NaturalElement> natural_element);

    void processNaturalElements();
    void processSaltMinerals(int x, int y);

    void processAnimalBreed(int x, int y);
    void processSheepBreed(int x, int y);
    void processWolfBreed(int x, int y);

    void processAnimals();

    bool placeRandomBabyAnimal(int x, int y, unique_ptr<Animal> animal);

    void processAnimal(int x, int y);
    void processSheep(int x, int y);
    void processWolf(int x, int y);

    Cell& getNextRandomSheepPosition(int x, int y);
    Cell& getNextRandomWolfPosition(int x, int y);
};

#endif // UNIVERSE_H
