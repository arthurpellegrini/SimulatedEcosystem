#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(Gender gender);

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

#endif // WOLF_H
