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

    virtual string display() const = 0;

    bool isBreeding() const;
    void setIsBreeding(bool isBreeding);

    int getAge() const;
    static int getAdultAge();

    int getSatiety() const;
    Gender getGender() const;

protected:
    int _age;
    Gender _gender;

    bool _canMove = true;
    int _satiety;
    int _maxSatiety;
    int _lifespan;
    bool _isBreeding = false;
    int _lastBreed = -1;
    static const int _breedCooldown;
    static const int _adultAge;
};

ostream& operator<<(ostream &os, const Animal &animal);

#endif // ANIMAL_H
