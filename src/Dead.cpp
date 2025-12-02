#include <Dead.hpp>
#include <Cell.hpp>
#include <calculsDead.hpp>

Dead::Dead(Cell* givenCell) : cell(givenCell) { // Ne vas surement pas fonctionner correctement car initialisation meme sans changement dans la grid temp
    cell->checkNeighbour();
    Calculs* temp;
    temp = new CalculsDead;
    cell->setCalc(temp);

    for (Cell* c : cell->getNeighbors()) {
        c->subAliveN();
    }
}