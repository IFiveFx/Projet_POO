#include <Alive.hpp>
#include <Cell.hpp>
#include <calculsAlive.hpp>
#include <CellState.hpp>

Alive::Alive(Cell* givenCell) : cell(givenCell) { 
    cell->checkNeighbour();
    Calculs* temp;
    temp = new CalculsAlive;
    cell->setCalc(temp);

    for (Cell* c : cell->getNeighbors()) {
        c->addAliveN();
    }
}