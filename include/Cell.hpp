#ifndef CELL_HPP
#define CELL_HPP
#include <vector>
#include <CellState.hpp>
#include <calculs.hpp>
using namespace std;

class Cell {
    private:
    vector<Cell*> neighbours;
    int aliveNeighbour;
    CellState* state;
    Calculs* calc;
    public:
    Cell(CellState* state);
    void checkNeighbour();
    void addNeighbour(Cell* neighbour);
    vector<Cell*> getNeighbors();
    Cell* evolution();
    void setCalc(Calculs* calc);
    Calculs* getCalc();
    void addAliveN();
    void subAliveN();
};





#endif