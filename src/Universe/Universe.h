#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <map>
#include <vector>
#include "Cell.h"

using namespace std;


class Universe {
public:
    Universe(const vector<int>& size);
    Universe(const vector<int>& size, int sheepQuantity, int wolfQuantity);

    void nextGeneration();
    bool isDead() const;
    int getGenerations() const;

    vector<vector<Cell>>& getCells();
    Cell& getCell(const std::pair<int, int>& coordinates);
    vector<string> getMessages(int generation);
    int getSheepQuantity() const;
    int getWolfQuantity() const;

    void setSheepQuantity(int sheepQuantity);
    void setWolfQuantity(int wolfQuantity);


private:
    vector<int> _size;

    int _sheepQuantity;
    int _wolfQuantity;
    int _generations;

    vector<vector<Cell>> _cells;
    vector<pair<int, map<string, vector<pair<int, int>>>>> _messages;

    void generateRandomUniverse();

    vector<int> randomAnimalPosition() const;

    map<pair<int, int>, Cell *> neighboor(int x, int y);

    void processNaturalElements();
    void processSaltMinerals(int x, int y);

    // void processAnimalBreed(int x, int y);
    // void processSheepBreed(int x, int y);
    // void processWolfBreed(int x, int y);
    // bool placeRandomBabyAnimal(int x, int y, unique_ptr<Animal> animal);

    void processAnimals();
    void processWolf(int x, int y);
    void processSheep(int x, int y);

    vector<int> randomWolfPosition(int x, int y);
    vector<int> randomSheepPosition(int x, int y);

    static string positionToString(int x, int y);

    void addMessage(const pair<int, int>& coordinates, const string &message);

    vector<pair<int, int>> findGrassWithinFov(int x, int y, int fov) const;
    vector<pair<int, int>> findSheepWithinFov(int x, int y, int fov) const;
};

#endif // UNIVERSE_H
