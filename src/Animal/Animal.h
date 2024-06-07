#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include "Gender.h"

using namespace std;

class Animal {
public:
    Animal(Gender gender, int maxSatiety, int lifespan);
    Animal(Gender gender, int maxSatiety, int lifespan, int age, int satiety);

    ~Animal();
    virtual string display() const = 0;

    void move();
    bool canMove() const;
    void resetCanMove();

    void increaseAge();
    bool isOldAgeDead() const;
    bool isHungerDead() const;

    void eat();
    void decreaseSatiety();

    bool canBreed(const Animal &animal) const;
    void breed();

    int getAge() const;
    int getSatiety() const;
    Gender getGender() const;

protected:
    int _age;
    int _satiety;
    int _maxSatiety;
    int _lifespan;
    Gender _gender;

    bool _canMove = true;
};

ostream& operator<<(ostream &os, const Animal &animal);

#endif // ANIMAL_H
