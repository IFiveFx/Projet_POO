#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game jeu(2,3,0,argv[1]);
    jeu.run();
    return 0;
}