/**
 * Project Untitled
 */


#ifndef _UNIVERSE_H
#define _UNIVERSE_H
#include <vector>

#include "Cell.h"


class Universe {
public:
    Universe(std::vector<int> dimensions);
    
    void nextGeneration();
    std::vector<std::vector<Cell>>& getField();
    
/**
 * @param cell

Cell [] neighborhood(Cell cell);
*/
private: 
    std::vector<int> dimensions;
    int generations;
    bool isDied;

    std::vector<std::vector<Cell>> field;
};

#endif //_UNIVERSE_H