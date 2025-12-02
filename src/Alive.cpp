#include <Alive.hpp>
#include <Cell.hpp>
#include <calculsAlive.hpp>

Alive::Alive(Cell* givenCell) : cell(givenCell) { // Ne vas surement pas fonctionner correctement car initialisation meme sans changement dans la grid temp
    cell->checkNeighbour();
    Calculs* temp;
    temp = new CalculsAlive;
    cell->setCalc(temp);

    for (Cell* c : cell->getNeighbors()) {
        c->addAliveN();
    }
}