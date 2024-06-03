#ifndef GRASS_H
#define GRASS_H

#include "NaturalElement.h"


class Grass : public NaturalElement {
public:
    string display() const override;
};

#endif // GRASS_H
