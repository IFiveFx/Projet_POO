#include "Game.hpp"
#include <iostream>
#include <Cell.hpp>
#include <ctime>
#include "Window.hpp"
#include <nfd.hpp>

#include "Folder.hpp"

#include "Alive.hpp"
#include "Dead.hpp"
#include "Immortal.hpp"
#include "Damned.hpp"
#include <chrono>
using namespace std;

class Folder;

Game::Game(int UnderPop, int OverPop, int iteration, string mode) {
    if (OverPop < 0 || UnderPop < 0 || iteration < 0) {
     cerr << "les attributs de game ne peuvent être négatifs\n";
     return;   
    }
    GameRules* rules = new GameRules(UnderPop,OverPop);
    this->rules = rules;
    this->iteration = iteration;
    this->mode = mode;
}
Game::~Game() {
    delete rules;
}

bool Game::run() {
    if (mode == "-graph") {
        runGraphic();
    } else {
        runConsole();
    }
    return 1;
}


bool Game::runConsole() {
    double time = 0;
    bool run = true;

    int nbiteration = 0;

    Cell::setRules(rules);
    string FilePath = setFile();
    string fileN = setFileName(FilePath);
    File fichier(fileN, FilePath);
    Grid* grille = new Grid();

    Folder dossier(fichier.getName() + "_out");
    dossier.create();

    grille->init(&fichier);


    while (run)
    {    
        std::cout << "itération " << nbiteration << " :" << endl;
        grille->print();

       
            chrono::high_resolution_clock sc;   
            auto start = sc.now(); 
        if (hashes.find(grille->getHash()) == hashes.end()) {
            hashes.emplace(grille->getHash(), nbiteration);
        grille->getNeighbors();
        grille->update();

        File outFichier((fichier.getName() + to_string(nbiteration)).c_str(),dossier.getName() + "/" + fichier.getName() + to_string(nbiteration) + ".txt");

        outFichier.write(grille);
        
        
        nbiteration += 1;
        if (iteration != 0 && nbiteration == iteration)
        {
            run = false;
        }
          } else {
            std::cout << "répétition de l'itération : " << hashes.find(grille->getHash())->second << endl;
            std::cout << "total calc time : " << time << endl;
            delete grille;
            return 0;
        }

            auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
            auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
            time += time_span.count();
        }
        cout << "total calc time : " << time << endl;
    delete grille;
    return 0;
        
    }




bool Game::runGraphic() {
    double time = 0;
    bool run = true;

    int nbiteration = 0;

    Cell::setRules(rules);
    string FilePath = setFile();
    string fileN = setFileName(FilePath);
    File fichier(fileN, FilePath);
    Grid* grille = new Grid();

    grille->init(&fichier);

    Window* fenetre = new Window(grille, 20);

    fenetre->initWindow();
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
                    if(speed == 0) break;
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
            if(event.type == sf::Event::MouseButtonPressed) {
                 if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*fenetre->getSfWindow());
                    int mouseX = int(mousePosition.y / fenetre->getCellSize()); 
                    int mouseY = int(mousePosition.x / fenetre->getCellSize());
                    vector<vector<Cell*>> MousesCells = grille->getCells();
                    Cell* mousesCell;
                    if (dynamic_cast<Alive*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        MousesCells.at(mouseX).at(mouseY)->setState(new Immortal);
                        grille->setCells(MousesCells);
                    } else if (dynamic_cast<Dead*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        MousesCells.at(mouseX).at(mouseY)->setState(new Alive);
                        grille->setCells(MousesCells);
                    } else if (dynamic_cast<Immortal*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        MousesCells.at(mouseX).at(mouseY)->setState(new Damned);
                        grille->setCells(MousesCells);
                    } else if (dynamic_cast<Damned*>(MousesCells.at(mouseX).at(mouseY)->getState())) {
                        MousesCells.at(mouseX).at(mouseY)->setState(new Dead);
                        grille->setCells(MousesCells);
                    }
                 }
            }
        }
        }
        fenetre->renderWindow(nbiteration);
        if (!pause || rightPressed)
        {
            chrono::high_resolution_clock sc;   
            auto start = sc.now(); 
        if (hashes.find(grille->getHash()) == hashes.end()) {
            hashes.emplace(grille->getHash(), nbiteration);
        grille->getNeighbors();
        grille->update();
                
        nbiteration += 1;
        if (iteration != 0 && nbiteration == iteration)
        {
            run = false;
        }
          } else {
            std::cout << "itération de fin : " << nbiteration << endl;
            std::cout << "répétition de l'itération : " << hashes.find(grille->getHash())->second << endl;
            delete grille;
            return 0;
        }
            rightPressed = false;
            sf::sleep(sf::milliseconds(speed));

            auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
            auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
            time += time_span.count();
        }
        
        
    }
    cout << "total calc time : " << time << endl;
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
    for (int i = 1; i < path.length(); i++) {
        if (path.at(i) == char(47)) {
            nameStart = i + 1;

        }
    }
    for (int i = nameStart; i < (path.length()-4); i++) {
        res.push_back(path.at(i));
    }
    return res;

}
