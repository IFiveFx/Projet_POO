#include "Game.hpp"
#include <iostream>
using namespace std;

Game::Game(int OverPop, int UnderPop, int iteration) {
    if (OverPop < 0 || UnderPop < 0 || iteration < 0) {
     cerr << "les attributs de game ne peuvent être négatifs\n";
     return;   
    }
    this->OverPop = OverPop;
    this->UnderPop = UnderPop;
    this->iteration = iteration;
}
bool Game::run() {
    bool run = true;
    int nbiteration = 0;
    Grid* grille = new Grid(5,5);
    File fichier("test","test.txt");
    grille->init(&fichier);
    while (run)
    {
        grille->print();
        grille = grille->update();
        if (iteration != 0)
        {
            nbiteration += 1;
            if (nbiteration == iteration) run = false;
        }
    }
}
void Game::setOverPop(int OverPop) {
    if(OverPop < 0) {
        cerr << "Overpop ne peut être inferieur a 0\n";
        return;
    }
    this->OverPop = OverPop;
}
void Game::setUnderPop(int UnderPop) {
    if(UnderPop < 0) {
        cerr << "UnderPop ne peut être inferieur a 0\n";
        return;
    }
    this->UnderPop = UnderPop;
}
int Game::getOverPop() const {
    return OverPop;
}
int Game::getUnderPop() const {
    return UnderPop;
}