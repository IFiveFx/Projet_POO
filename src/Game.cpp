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
    while (run)
    {
        if (iteration != 0)
        {
            nbiteration += 1;
            if (nbiteration == iteration) run = false;
        }
    }
}
void Game::setOverPop(int OverPop) {}
void Game::setUnderPop(int UnderPop) {}
int Game::getOverPop() const {}
int Game::getUnderPop() const {}