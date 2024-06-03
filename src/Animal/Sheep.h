#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

using namespace std;


class Sheep : public Animal {
public:
    Sheep(Gender gender);

    string display() const override;
    void eat() override;
    void move() override;
    void breed() override;
    void die() override;

    static int getSatiety();
    static int getLifespan();

private:
    static const int satiety;
    static const int lifespan;
    static const int fov;
};

#endif // SHEEP_H
