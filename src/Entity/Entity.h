#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;

class Entity {
public:
    virtual ~Entity() = default;
    virtual string display() const = 0;
};


ostream& operator<<(ostream &os, const Entity &entity);

#endif //ENTITY_H
