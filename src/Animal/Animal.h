#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>
#include "Gender.h"

using namespace std;


class Animal {
public:
    Animal(Gender gender);

    virtual string display() const = 0;

    virtual void eat() = 0;
    virtual void move() = 0;
    virtual void breed() = 0;
    virtual void die() = 0;

    int getAge() const;
    Gender getGender() const;
    int getSatiety() const;
    void increaseAge();
    void resetSatiety(int value);
    void decreaseSatiety();

    virtual ~Animal();

protected:
    int _age;
    Gender _gender;
    int _satiety;
    static const int _maxSatiety;
};

ostream& operator<<(ostream &os, const Animal &animal);

#endif // ANIMAL_H
