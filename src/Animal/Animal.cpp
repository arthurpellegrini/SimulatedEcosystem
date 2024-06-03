/**
 * Project Untitled
 */


#include "Animal.h"

/**
 * Animal implementation
 */


/**
 * @return void
 */
void Animal::eat() {
    return;
}

/**
 * @return void
 */
void Animal::move() {
    return;
}

/**
 * @return void
 */
void Animal::breed() {
    return;
}

/**
 * @return void
 */
void Animal::die() {
    return;
}

std::ostream& operator << (std::ostream &os, Animal &s) {
 return (os << 'A' << std::endl);
}