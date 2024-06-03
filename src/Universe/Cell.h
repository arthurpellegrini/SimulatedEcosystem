#ifndef CELL_H
#define CELL_H
#include <vector>

#include "../Animal/Animal.h"
#include "../NaturalElement/NaturalElement.h"

using namespace std;


class Cell {
    bool _isEmpty;
    vector<int> _position;
    Animal* _animalOnCell;
    NaturalElement* _naturalElementOnCell;

public:
    Cell(const vector<int> &position={1,1});

    void addAnimal(Animal* animal);
    void addNaturalElement(NaturalElement* naturalElement);
    void updateIsEmpty();

    bool isEmpty();
    void setIsEmpty(bool value);

    ~Cell(){
        delete _animalOnCell;
        delete _naturalElementOnCell;
    }

    friend ostream& operator<<(ostream& os, const Cell& s);
};

#endif //CELL_H