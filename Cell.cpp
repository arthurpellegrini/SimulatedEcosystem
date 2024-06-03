/**
 * Project Untitled
 */


#include "Cell.h"

#include "Grass.h"

/**
 * Case implementation
 */
Cell::Cell(const std::vector<int> &position) : position(position){

 naturalElementOnCase = new Grass();
 animalOnCase = nullptr;
 getSetEmpty(true);

}

/**
 *@param bool toSet, if true we are ajusting the variable else we are juste getting it
 * @return bool
 */
bool Cell::getSetEmpty(bool toSet) {

  if(toSet) {
   isEmpty = (animalOnCase == nullptr && naturalElementOnCase == nullptr);

  }

 return isEmpty;
}

/**
 *@param Animal, we are assigning an Animal to this Case
 * @return void
 */
bool Cell::addAnimal(Animal* animal) {
 animalOnCase = animal;

 return getSetEmpty(true);
}


/**
 *@param NaturalElement, we are assigning an NaturalElement to this Case
 * @return void
 */
bool Cell::addNaturalElement(NaturalElement* NaturalElement) {
 naturalElementOnCase = NaturalElement;

 return getSetEmpty(true);
}

std::ostream& operator << (std::ostream &os, const Cell &s) {

 if(s.animalOnCase != nullptr) {
  os <<s.animalOnCase->display();
 }
 if(s.naturalElementOnCase != nullptr) {
  os <<s.naturalElementOnCase->display();
 }
 return (os);
}
