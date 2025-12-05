#include "Game.hpp"

int main(int argc, char * argv[]) {
    if (argc == 1) argv[1] = "-g";
    Game jeu(2,3,0,argv[1]);
    jeu.run();
    return 0;
}