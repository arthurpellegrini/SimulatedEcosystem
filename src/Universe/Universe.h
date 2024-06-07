#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <map>
#include <vector>
#include "Cell.h"
#include "../Animal/Wolf.h"
#include "../Animal/Sheep.h"

using namespace std;


class Universe {
public:
    explicit Universe(const vector<int>& size);
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

    void processAnimals();
    void processWolf(int x, int y);
    void processSheep(int x, int y);

    vector<int> randomWolfPosition(int x, int y);
    vector<int> randomSheepPosition(int x, int y);

    void breedWolf(int x, int y, Wolf& wolf);
    void breedSheep(int x, int y, Sheep& sheep);

    static string positionToString(int x, int y);
    void addMessage(const pair<int, int>& coordinates, const string &message);
};

#endif // UNIVERSE_H
