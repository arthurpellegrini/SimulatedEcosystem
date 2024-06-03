/**
 * Project Untitled
 */


#ifndef _GRASS_H
#define _GRASS_H

#include "NaturalElement.h"


class Grass: public NaturalElement {


 std::string display() const override {
  return ";";
 }
};

#endif //_GRASS_H