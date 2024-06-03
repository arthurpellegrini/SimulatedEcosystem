#ifndef CELL_H
#define CELL_H

#include <vector>
#include <memory>
#include <iostream>
#include "../Animal/Animal.h"
#include "../NaturalElement/NaturalElement.h"

using namespace std;

class Cell {
    bool _isEmpty;
    vector<int> _position;
    shared_ptr<Animal> _animalOnCell;
    shared_ptr<NaturalElement> _naturalElementOnCell;

    void updateIsEmpty();

public:
    Cell(const vector<int>& position = {0, 0});

    void addAnimal(unique_ptr<Animal> animal);
    void removeAnimal();
    void addNaturalElement(unique_ptr<NaturalElement> naturalElement);
    void removeNaturalElement();

    bool isEmpty() const;
    vector<int> getPosition() const;
    Animal* getAnimal() const;
    NaturalElement* getNaturalElement() const;

    friend ostream& operator<<(ostream& os, const Cell& s);
};

#endif // CELL_H
