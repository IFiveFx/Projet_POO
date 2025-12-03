#include <Cell.hpp>
#include <CellState.hpp>
#include <calculs.hpp>
#include <Alive.hpp>
#include <Dead.hpp>
#include <Immortal.hpp>
#include <Damned.hpp>
#include <calculsAlive.hpp>
#include <calculsDead.hpp>
#include <iostream>
using namespace std;

GameRules* Cell::rules = nullptr;

Cell::Cell(CellState* state) : state(state), aliveNeighbour(0) {}

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
        } else if (dynamic_cast<Immortal*>(neighbour->state)) {
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
    } else if (dynamic_cast<Immortal*>(state)) {
        return this;
    } else if (dynamic_cast<Damned*>(state)) {
        return this;
    }
    a = new Cell(c->use(this));
    delete c;
    return a;
}

void Cell::addAliveN(){
    aliveNeighbour += 1;
}


CellState* Cell::getState() {
    return state;
}
void Cell::setState(CellState* state) {
    this->state = state;
}

int Cell::getAliveNeighbors() {
    return aliveNeighbour;
}
void Cell::setRules(GameRules* newRules) {
    rules = newRules;
}
GameRules* Cell::getRules() {
    return rules;
}