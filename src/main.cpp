#include "file.hpp"

int main() {
    File fichier("test","test.txt");
    fichier.write("coucou c'est moi, moumou la reine des mouettes !");
    fichier.read();
    return 0;
}