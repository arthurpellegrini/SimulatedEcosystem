/**
 * Project Untitled
 */


#ifndef _UNIVERSE_H
#define _UNIVERSE_H
#include <vector>

class Universe {
public:
    Universe(std::vector<int> dimensions);
    
    void nextGeneration();
    std::vector<std::vector<int>>& getField();
    
/**
 * @param cell

Cell [] neighborhood(Cell cell);
*/
private: 
    std::vector<int> dimensions;
    int generations;
    bool isDied;

    std::vector<std::vector<int>> field;
};

#endif //_UNIVERSE_H