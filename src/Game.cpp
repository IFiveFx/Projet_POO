#include "Game.hpp"
#include <iostream>
#include <Cell.hpp>
#include <ctime>
#include "Window.hpp"
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
    //cout << "oui13\n";
    grille->init(&fichier);
    Window* fenetre = new Window(grille);
    fenetre->initWindow();
    //cout << "oui12\n";
    int speed = 100;
    while (run)
    {
        if (fenetre->getSfWindow()->isOpen()) {
            sf::Event event;
            while (fenetre->getSfWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre->getSfWindow()->close();
                run = false;
                }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    if(speed == 10) break;
                    speed -= 10;
                    break;
                
                case sf::Keyboard::Down :
                    if(speed == 1000) break;
                    speed += 10;
                    break;
                }
            }
        }
        }
        cout << "oui11\n";
        fenetre->renderWindow();
        //cout << "oui7\n";
        
        grille->update();
        grille->getNeighbors();
        if (iteration != 0)
        {
            nbiteration += 1;
            if (nbiteration == iteration) run = false;
        }
        sf::sleep(sf::milliseconds(speed));
    }
    delete grille;
    delete fenetre;
    return 0;
}

void Game::setRules(GameRules* rules) {
    this->rules = rules;
}
GameRules* Game::getRules() {
    return this->rules;
}