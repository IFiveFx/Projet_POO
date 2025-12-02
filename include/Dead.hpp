#ifndef DEAD_HPP
#define DEAD_HPP
#include <CellState.hpp>
#include <Cell.hpp>

class Dead : public CellState {
    private:
    Cell* cell;
    public:
    Dead(Cell* givenCell);
};




#endif