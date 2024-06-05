#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>
#include "Gender.h"

using namespace std;

class Animal {
public:
    Animal(Gender gender, int maxSatiety, int lifespan);
    Animal(Gender gender, int maxSatiety, int lifespan, int age, int satiety);

    virtual ~Animal();

    void increaseAge();
    bool isDead() const;

    void eat();
    void decreaseSatiety();

    bool canBreed(const Animal &animal) const;

    virtual string display() const = 0;

    int getAge() const;
    int getSatiety() const;
    Gender getGender() const;

protected:
    int _age;
    Gender _gender;
    int _satiety;
    int _maxSatiety;
    int _lifespan;
};

ostream& operator<<(ostream &os, const Animal &animal);

#endif // ANIMAL_H
