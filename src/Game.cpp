#include "Game.hpp"
#include <iostream>
#include <Cell.hpp>
#include <ctime>
#include "Window.hpp"
#include <nfd.hpp>

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
    string FilePath = setFile();
    string fileN = setFileName(FilePath);
    File fichier(fileN, FilePath);
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
        //cout << "oui11\n";
        fenetre->renderWindow();
        //cout << "oui7\n";
        cout << "itération " << nbiteration << " :" << endl;
         grille->print();
        if (hashes.find(grille->getHash()) == hashes.end()) {
            hashes.emplace(grille->getHash(), nbiteration);
        grille->update();
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



string Game::setFile() {
    NFD_Init();

    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = { { "Text", "txt" }};
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outPath);
        return outPath;
        NFD_FreePathU8(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else 
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
    return "test.txt";
}

string Game::setFileName(string path) {
    int nameStart = 0;
    string res;
    cout << path << endl;
    for (int i = 1; i < path.length(); i++) {
        if (path.at(i) == char(47)) {
            nameStart = i + 1;

        }
    }
    for (int i = nameStart; i < (path.length()-4); i++) {
        res.push_back(path.at(i));
    }
    cout << res << endl;
    return res;

}