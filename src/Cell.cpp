#include <Cell.hpp>
#include <CellState.hpp>
#include <calculs.hpp>
#include <Alive.hpp>
#include <Dead.hpp>

Cell::Cell(CellState* state) : state(state) {}

void Cell::addNeighbour(Cell* neighbour) {
    neighbours.push_back(neighbour);
}

void Cell::checkNeighbour() {
    for (Cell* neighbour: neighbours) {
        if (dynamic_cast<Alive*>(neighbour->state)) {
            aliveNeighbour += 1;
        }
    }
}

Cell* Cell::evolution(){ //Fuite Mémoire ??
    Cell a(calc->use());
    return &a;
}

void Cell::setCalc(Calculs* givenCalc){
    calc = givenCalc;
}

Calculs* Cell::getCalc(){
    return calc;
}

