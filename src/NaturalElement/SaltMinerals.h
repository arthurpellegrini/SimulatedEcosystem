#ifndef SALTMINERALS_H
#define SALTMINERALS_H

#include "NaturalElement.h"

class SaltMinerals : public NaturalElement {
    static const int lifespan = 1;
    int age;

public:
    SaltMinerals();

    string display() const override;
    void incrementAge();
    bool shouldTransform() const;
};

#endif // SALTMINERALS_H
