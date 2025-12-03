#include "Game.hpp"
#include <iostream>
#include <Cell.hpp>
#include <ctime>
#include "Window.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "Alive.hpp"
#include "Dead.hpp"
#include "Immortal.hpp"
#include "Damned.hpp"
using namespace std;

void delFolder(const string Path);

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

    Grid* grille = new Grid();

    File fichier("test","test.txt");

    struct stat info;
    if (stat((fichier.getName()+ "_out").c_str(),&info) == 0) {
        delFolder((fichier.getName()+ "_out").c_str());
    }
    mkdir((fichier.getName()+ "_out").c_str() ,0775);

    //cout << "oui13\n";
    grille->init(&fichier);

    Window* fenetre = new Window(grille);

    fenetre->initWindow();
    //cout << "oui12\n";
    int speed = 100;
    bool pause = true;
    bool rightPressed = false;

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
                case sf::Keyboard::Space :
                    pause = !pause;
                    break;
                }
                if (pause)
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Right:
                        rightPressed = true;
                        break;
                    }
                }
                
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                 if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*fenetre->getSfWindow());
                    int mouseX = mousePosition.x; 
                    int mouseY = mousePosition.y;
                    vector<vector<Cell*>> MousesCells = grille->getCells();
                    Cell* mousesCell;
                    cout << "mouse1\n";
                    if (dynamic_cast<Alive*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        cout << "mouse2\n";
                        MousesCells.at(mouseX).at(mouseY)->setState(new Immortal);
                        grille->setCells(MousesCells);
                    } else if (dynamic_cast<Dead*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        cout << "mouse3\n";
                        MousesCells.at(mouseX).at(mouseY)->setState(new Alive);
                        grille->setCells(MousesCells);
                    } else if (dynamic_cast<Immortal*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        cout << "mouse4\n";
                        MousesCells.at(mouseX).at(mouseY)->setState(new Damned);
                        grille->setCells(MousesCells);
                    } else if (dynamic_cast<Damned*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        cout << "mouse5\n";
                        MousesCells.at(mouseX).at(mouseY)->setState(new Dead);
                        grille->setCells(MousesCells);
                    }
                 }
            }
        }
        }
        //cout << "oui11\n";
        fenetre->renderWindow();
        //cout << "oui7\n";
        cout << "itération " << nbiteration << " :" << endl;

        grille->print();

        if (!pause || rightPressed)
        {
        if (hashes.find(grille->getHash()) == hashes.end()) {
            hashes.emplace(grille->getHash(), nbiteration);
        
        grille->update();

        File outFichier((fichier.getName() + to_string(nbiteration)).c_str(),fichier.getName()+ "_out/" + fichier.getName() + to_string(nbiteration) + ".txt");

        outFichier.write(grille);
        
        grille->getNeighbors();
        
        nbiteration += 1;
        if (iteration != 0 && nbiteration == iteration)
        {
            run = false;
        }
          } else {
            cout << "répétition de l'itération : " << hashes.find(grille->getHash())->second << endl;
            delete grille;
            return 0;
        }
            rightPressed = false;
            sf::sleep(sf::milliseconds(speed));
        }
        
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

void delFolder(const string Path) {
    DIR* dir = opendir(Path.c_str());

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;

        if (name == "." || name == "..") continue;

        string fullPath = Path + "/" + name;

        remove(fullPath.c_str());
    }

    closedir(dir);

    rmdir(Path.c_str()) != 0;
        
}

void newIteration() {}
