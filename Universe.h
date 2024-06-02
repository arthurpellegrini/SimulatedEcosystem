/**
 * Project Untitled
 */


#ifndef _UNIVERSE_H
#define _UNIVERSE_H

class Universe {
public: 
    
void nextGeneration();
    
/**
 * @param cell
 */
Cell [] neighborhood(Cell cell);
private: 
    static vect size;
    int generations;
    bool isDied;
};

#endif //_UNIVERSE_H