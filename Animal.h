/**
 * Project Untitled
 */


#ifndef _ANIMAL_H
#define _ANIMAL_H
#include <iostream>

class Animal {

public:

    virtual std::string display() const = 0;

    void eat();

    void move();

    void breed();

    void die();

    virtual  ~Animal()  = default;


private: 
    int age;
    char gender;
    int DaysOfSatiety;
};

#endif //_ANIMAL_H