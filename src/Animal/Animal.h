#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include "Gender.h"

using namespace std;

class Animal {
public:
    Animal(Gender gender, int adultAge, int lifespan, int maxSatiety, int cooldown);
    Animal(Gender gender, int age, int adultAge, int lifespan, int satiety, int maxSatiety, int cooldown);

    virtual ~Animal();
    virtual string display() const = 0;

    void move();
    bool canMove() const;
    void resetCanMove();

    void increaseAge();
    bool isOldAgeDead() const;
    bool isHungerDead() const;

    void eat();
    void decreaseSatiety();

    void breed();
    void updateBreedCooldown();
    bool canBreed() const;
    bool canBreedWith(const Animal &animal) const;

    Gender getGender() const;
    int getAge() const;
    int getAdultAge() const;
    int getSatiety() const;
    static int getFOV();

protected:
    Gender _gender;

    int _age;
    int _adultAge;
    int _lifespan;

    int _cooldown;
    int _breedCooldown;

    int _satiety;
    int _maxSatiety;

    static int _fov;

    bool _canMove = true;
    bool _canBreed = false;
};

ostream& operator<<(ostream &os, const Animal &animal);

#endif // ANIMAL_H
