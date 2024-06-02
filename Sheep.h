/**
 * Project Untitled
 */


#ifndef _SHEEP_H
#define _SHEEP_H

#include "Animal.h"


class Sheep: public Animal {
private: 
    static int satiety;
    static int  lifespan;
    static int fov;
};

#endif //_SHEEP_H