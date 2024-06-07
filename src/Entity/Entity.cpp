#include "Entity.h"

ostream& operator<<(ostream &os, const Entity &entity) {
    return os << entity.display();
}