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

    static int getLifespan();

private:
    static const int _maxSatiety;
    static const int _lifespan;
    static const int _fov; // Field of view for movement
};

#endif // SHEEP_H
