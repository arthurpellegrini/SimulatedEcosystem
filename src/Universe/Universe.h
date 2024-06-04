#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "Cell.h"

using namespace std;


class Universe {
public:
    Universe(const vector<int>& size);

    void nextGeneration();
    vector<vector<Cell>>& getCells();
    Cell& getCell(const std::pair<int, int>& coordinates);
    bool isDead();
    int getGenerations();

private:
    vector<int> _size;
    int _generations;
    bool _isDead;

    vector<vector<Cell>> _cells;
    vector<vector<Cell>> _nextCells;

    static Gender randomGender();
    void placeRandomAnimal(unique_ptr<Animal> animal);
    void placeRandomNaturalElement(unique_ptr<NaturalElement> natural_element);

    void processCell(int x, int y);
    void processNaturalElement(int x, int y);
    void processAnimal(int x, int y);
    void processSheep(int x, int y);
    Cell& getNextRandomPosition(int x, int y);

    static const float _percentageAnimal;
    static const float _percentageWolves;
    static const float _percentageSaltMinerals;
};

#endif // UNIVERSE_H
