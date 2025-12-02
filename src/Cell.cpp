#include <Cell.hpp>
#include <CellState.hpp>
#include <calculs.hpp>
#include <Alive.hpp>
#include <Dead.hpp>
#include <calculsAlive.hpp>
#include <calculsDead.hpp>

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
    Calculs* c;
    if (dynamic_cast<Alive*>(state)){
        c = new CalculsAlive;
    } else if (dynamic_cast<Dead*>(state)) {
        c = new CalculsDead;
    }
    a = new Cell(c->use(this));
    return a;
}

void Cell::addAliveN(){
    aliveNeighbour += 1;
}


CellState* Cell::getState() {
    return state;
}

int Cell::getAliveNeighbors() {
    return aliveNeighbour;
}