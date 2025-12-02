#include <calculsAlive.hpp>
#include <Cell.hpp>
#include <Alive.hpp>
#include <Dead.hpp>

CellState* CalculsAlive::use(Cell* c) {
    CellState* state;
    if (c->getAliveNeighbors() >= c->getRules()->getUnderPop() && c->getAliveNeighbors() <= c->getRules()->getOverPop() ) {
        state = new Alive;
    } else {
        state = new Dead;
    }
    return state;
}