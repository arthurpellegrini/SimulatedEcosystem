#ifndef CELL_H
#define CELL_H

#include <vector>
#include <memory>
#include <iostream>
#include "../Animal/Animal.h"
#include "../NaturalElement/NaturalElement.h"

using namespace std;


class Cell {
public:
    explicit Cell();

    void addAnimal(unique_ptr<Animal> animal);
    void removeAnimal();

    void addNaturalElement(unique_ptr<NaturalElement> naturalElement);
    void removeNaturalElement();

    bool isEmpty() const;
    bool hasAnimal() const;
    bool hasSheep() const;
    bool hasWolf() const;
    bool hasNaturalElement() const;
    bool hasGrass() const;
    bool hasSaltMinerals() const;

    Animal* getAnimal() const;
    NaturalElement* getNaturalElement() const;

    string display() const;
    friend ostream& operator<<(ostream& os, const Cell& cell);

private:
    bool _isEmpty;
    shared_ptr<Animal> _animal;
    shared_ptr<NaturalElement> _natural_element;

    void updateIsEmpty();
};

#endif // CELL_H
