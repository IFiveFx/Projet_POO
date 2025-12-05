#include "Game.hpp"
#include <iostream>
#include <string.h>

int main(int argc, char * argv[]) {
    int underPop = 2;
    int overPop = 3;
    int iteration = 0;
    string mode = "";
    if (argc > 1) 
    { 
        for (int i = 1; i < argc; i++) { 
        if (strcmp(argv[i],"-u") == 0) {
            underPop = atoi(argv[i+1]);
        } else if (strcmp(argv[i],"-o") == 0) {
            overPop = atoi(argv[i+1]);
        } else if (strcmp(argv[i],"-i") == 0) {
            iteration = atoi(argv[i+1]);
        } else if (strcmp(argv[i],"-g") == 0){
            mode = "-g";
            } else if ((strcmp(argv[i],"--help") == 0) | (strcmp(argv[i],"-h") == 0)) {
                std::cout << "All parameters are optional, if none are provided, game will start in console mode, with no limit of iterations and with the following parameters : -u 2 -o 3" << endl;
                std::cout << "-u [number]     :     Define the number of alive neighbor cells one needs to stay alive" << endl;
                std::cout << "-o [number]     :     Define the number of alive neighbor cells is too much to stay alive, it is also the number of neighbor cells a dead cell needs to live" << endl;
                std::cout << "-i [number]     :     Define the number of iterations before the game automatically stops " << endl;
                std::cout << "-g              :     start the game in graphical interface mode, otherwise, game starts in the console, with output to file" << endl;
                std::cout << "--help or -h    :     Get this message" << endl;
                return 0;

            }
        }
    }
    Game jeu(underPop, overPop, iteration, mode);
    jeu.run();
    return 0;
}