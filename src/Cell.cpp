#include <Cell.hpp>
#include <CellState.hpp>
#include <calculs.hpp>
#include <Alive.hpp>
#include <Dead.hpp>

Cell::Cell(CellState* state) : state(state) {}

void Cell::addNeighbour(Cell* neighbour) {
    neighbours.push_back(neighbour);
}

vector<Cell*> Cell::getNeighbors() {
    return neighbours;
}

void Cell::checkNeighbour() {
    for (Cell* neighbour: neighbours) {
        if (dynamic_cast<Alive*>(neighbour->state)) {
            aliveNeighbour += 1;
        }
    }
}

Cell* Cell::evolution(){ 
    Cell* a;
    a = new Cell(calc->use(aliveNeighbour));
    return a;
}

void Cell::setCalc(Calculs* givenCalc){
    calc = givenCalc;
}

Calculs* Cell::getCalc(){
    return calc;
}

void Cell::addAliveN(){
    aliveNeighbour += 1;
}


CellState* Cell::getState() {
    return state;
}
