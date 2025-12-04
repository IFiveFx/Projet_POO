#ifndef CELL_HPP
#define CELL_HPP
#include <vector>
#include <CellState.hpp>
#include <calculs.hpp>
#include "GameRules.hpp"
using namespace std;

class GameRules;

class Cell {
    private:
    static GameRules* rules;
    vector<Cell*> neighbours;
    int aliveNeighbour;
    CellState* state;
    public:
    Cell(CellState* state);
    void checkNeighbour();
    void addNeighbour(Cell* neighbour);
    void clearNeighbours();
    vector<Cell*> getNeighbors();
    Cell* evolution();
    void addAliveN();
    CellState* getState();
    void setState(CellState* state);
    int getAliveNeighbors();
    static void setRules(GameRules* newRules);
    static GameRules* getRules();
};





#endif