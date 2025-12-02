#include <Grid.hpp>
#include <string>
#include <Dead.hpp>
#include <Alive.hpp>
#include <iostream>
using namespace std;

Grid::Grid(int l, int c) : lines(l), columns(c) {}

void Grid::init(File* f) {
    string textfile = f->read();
    int count = 0;
    for (char c : textfile) {
        if (c == char(10)) {
            vector<Cell*> v; 
            cells.push_back(v);
            count += 1;
        }
        if (c == '0') {
            Cell* tempcell;
            CellState* s;
            s = new Dead;
            tempcell = new Cell(s);
            cells.at(count).push_back(tempcell);
        } else if (c == '1' ) {
            Cell* tempcell;
            CellState* s;
            s = new Alive;
            tempcell = new Cell(s);
            cells.at(count).push_back(tempcell);
        }
    }

    for (int a = 0; a < cells.size(); a++) {
        for (int b = 0; b < cells.at(a).size(); b++) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if(i == 0 && j == 0) continue;
                    int xNeighbour = (a + i + cells.size()) % cells.size();
                    int yNeighbour = (b + j + cells.at(a).size()) % cells.at(a).size();

                    cells.at(a).at(b)->addNeighbour(cells.at(xNeighbour).at(yNeighbour));
                }
            }

        }
    }


    for (vector<Cell*> v : cells) {
        for (Cell* c : v) {
            c->checkNeighbour();
        }
    }

}

Grid* Grid::update() {
    Grid* newGrid;
    int count = 0;
    for (vector<Cell*> v : cells) {
        vector<Cell*> newV;
        newGrid->cells.push_back(newV);
        for (Cell* c : v) {
            newGrid->cells.at(count).push_back(c->evolution());
        }
        count += 1;
    }
    return newGrid;

}


void Grid::print() {
    for (vector<Cell*> v : cells){
        for (Cell* c : v) {
            if (dynamic_cast<Alive*>(c->getState())) {
                cout << "1";
            } else if (dynamic_cast<Dead*>(c->getState())) {
                cout << "0";
            }
        }
        cout << endl;
    }


}