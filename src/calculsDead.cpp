#include <calculsDead.hpp>
#include <Cell.hpp>
#include <Alive.hpp>
#include <Dead.hpp>

CellState* CalculsDead::use(Cell* c) {
    CellState* state;
    if (c->getAliveNeighbors() == c->getRules()->getOverPop()) {
        state = new Alive;
    } else {
        state = new Dead;
    }
    return state;

}
