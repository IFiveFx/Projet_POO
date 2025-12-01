#ifndef CELL_HPP
#define CELL_HPP
#include <vector>
#include <CellState.hpp>
#include <Calculs.hpp>
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
    Cell* evolution();
    void setCalc(Calculs* calc);
    Calculs* getCalc();
};





#endif