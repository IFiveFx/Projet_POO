#include "Game.hpp"
#include <iostream>
#include <Cell.hpp>
using namespace std;


Game::Game(int UnderPop, int OverPop, int iteration) {
    if (OverPop < 0 || UnderPop < 0 || iteration < 0) {
     cerr << "les attributs de game ne peuvent être négatifs\n";
     return;   
    }
    GameRules* rules = new GameRules(UnderPop,OverPop);
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
        cout << "itération " << nbiteration << " :" << endl;
            grille->print();
        if (hashes.find(grille->getHash()) == hashes.end()) {
            hashes.emplace(grille->getHash(), nbiteration);
            Grid* newGrid = new Grid(5,5);
            newGrid = grille->update();
            grille = newGrid;
            grille->getNeighbors();
            if (iteration != 0)
            {
                nbiteration += 1;
                if (nbiteration == iteration) run = false;
            }
        } else {
            cout << "répétition de l'itération : " << hashes.find(grille->getHash())->second << endl;
            delete grille;
            return 0;
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