#include <Dead.hpp>
#include <Cell.hpp>
#include <calculsDead.hpp>

Dead::Dead(Cell* givenCell) : cell(givenCell) { 
    cell->checkNeighbour();
    Calculs* temp;
    temp = new CalculsDead;
    cell->setCalc(temp);
}