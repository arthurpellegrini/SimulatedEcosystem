#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

using namespace std;

enum class Gender {
    Male,
    Female
};

class Animal {
protected:
    int _age;
    Gender _gender;
    int _satiety;
    static const int _maxSatiety;

public:
    Animal(Gender gender);

    virtual string display() const;
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
};

// Surcharge de l'opérateur << pour l'affichage des animaux
ostream& operator<<(ostream &os, const Animal &animal);

#endif // ANIMAL_H
