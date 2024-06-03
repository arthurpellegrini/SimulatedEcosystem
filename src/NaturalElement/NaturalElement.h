/**
 * Project Untitled
 */


#ifndef _NATURALELEMENT_H
#define _NATURALELEMENT_H
#include <iostream>

class NaturalElement {

public:
 virtual  ~NaturalElement()  = default;

 virtual std::string display() const = 0;
};

#endif //_NATURALELEMENT_H