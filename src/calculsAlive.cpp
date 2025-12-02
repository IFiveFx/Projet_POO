#include <calculsAlive.hpp>
#include <Cell.hpp>
#include <Alive.hpp>
#include <Dead.hpp>

CellState* CalculsAlive::use(Cell* c) {
    CellState* state;
    if (c->getAliveNeighbors() >= 2 && c->getAliveNeighbors() <= 3 ) {
        state = new Alive;
    } else {
        state = new Dead;
    }
    return state;
}