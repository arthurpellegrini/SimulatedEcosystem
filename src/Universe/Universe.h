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
    vector<pair<int, vector<pair<vector<string>, string>>>> _messages;

    void generateRandomUniverse();

    vector<int> randomAnimalPosition() const;

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

    string positionToString(int x, int y);

    void addMessage(const pair<int, int>& coordinates, const string &message);
};

#endif // UNIVERSE_H
