#include "Game.hpp"
#include <iostream>
#include <Cell.hpp>
using namespace std;


Game::Game(int OverPop, int UnderPop, int iteration) {
    if (OverPop < 0 || UnderPop < 0 || iteration < 0) {
     cerr << "les attributs de game ne peuvent être négatifs\n";
     return;   
    }
    GameRules* rules = new GameRules(OverPop,UnderPop);
    this->rules = rules;
    this->iteration = iteration;
}
Game::~Game() {
    delete rules;
}
bool Game::run() {
    bool run = true;
    int nbiteration = 0;
    Cell::setRules(rules);
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
    delete grille;
    return 0;
}

void Game::setRules(GameRules* rules) {
    this->rules = rules;
}
GameRules* Game::getRules() {
    return this->rules;
}