#ifndef ALIVE_HPP
#define ALIVE_HPP
#include <CellState.hpp>

class Alive : public CellState {
    private:
    Cell* cell;
    public:
    Alive(Cell* givenCell);

};



#endif