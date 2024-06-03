#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"


class Sheep : public Animal {
public:
    Sheep(Gender gender);

    string display() const override;
    void eat() override;
    void move() override;
    void breed() override;
    void die() override;

    int getSatiety();
    static int getLifespan();

private:
    int _satiety;
    static const int _maxSatiety;
    static const int _lifespan;
    static const int _fov;
};

#endif // SHEEP_H
