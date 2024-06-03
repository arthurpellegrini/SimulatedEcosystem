/**
 * Project Untitled
 */


#ifndef _WOLF_H
#define _WOLF_H

#include "Animal.h"


class Wolf: public Animal {

public:
    std::string display() const override {
        return "W";
    }

private: 
    static int satiety;
    static int lifespan;
    static int fov;
};

#endif //_WOLF_H