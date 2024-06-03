/**
 * Project Untitled
 */


#ifndef _CASE_H
#define _CASE_H
#include <vector>

#include "../Animal/Animal.h"
#include "../NaturalElement/NaturalElement.h"

class Cell {

public:
    Cell(const std::vector<int> &position={1,1});
    bool getSetEmpty(bool toSet=false);
    bool addAnimal(Animal* animal);
    bool addNaturalElement(NaturalElement* naturalElement);

    ~Cell(){
        delete animalOnCase;
        delete naturalElementOnCase;
    }


    friend std::ostream& operator<<(std::ostream& os, const Cell& s);

private: 
    std::vector<int> position;
    bool isEmpty;
    Animal* animalOnCase;
    NaturalElement* naturalElementOnCase;
};

#endif //_Case_H