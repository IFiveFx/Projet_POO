#include <calculsDead.hpp>
#include <Cell.hpp>
#include <Alive.hpp>
#include <Dead.hpp>

CellState* CalculsDead::use(Cell* c) {
    CellState* state;
    if (c->getAliveNeighbors() == 3) {
        state = new Alive;
    } else {
        state = new Dead;
    }
    return state;

}
