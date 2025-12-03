#include <Grid.hpp>
#include <string>
#include <Dead.hpp>
#include <Alive.hpp>
#include <Immortal.hpp>
#include <Damned.hpp>
#include <iostream>
using namespace std;

Grid::Grid(int l, int c) : lines(l), columns(c){}

void Grid::init(File* f) {
    //cout << "oui19\n";
    string textfile = f->read();
    //cout << "oui20\n";
    vector<Cell*> v; 
    cells.push_back(v);
    int count = 0;
    for (char c : textfile) {
        //cout << "oui21\n";
        if (c == char(10)) {
            vector<Cell*> v; 
            cells.push_back(v);
            count += 1;
        } else if (c == '0') {
            Cell* tempcell;
            CellState* s;
            s = new Dead;
            tempcell = new Cell(s);
            //cout << "oui23\n";
            if (count < (int)cells.size()) {
                cells.at(count).push_back(tempcell);
            }
            //cout << "oui24\n";
        } else if (c == '1' ) {
            Cell* tempcell;
            CellState* s;
            s = new Alive;
            tempcell = new Cell(s);
            if (count < (int)cells.size()) {
                cells.at(count).push_back(tempcell);
            }
        } else if (c == '2' ) {
            Cell* tempcell;
            CellState* s;
            s = new Immortal;
            tempcell = new Cell(s);
            if (count < (int)cells.size()) {
                cells.at(count).push_back(tempcell);
            }
        } else if (c == '3' ) {
            Cell* tempcell;
            CellState* s;
            s = new Damned;
            tempcell = new Cell(s);
            if (count < (int)cells.size()) {
                cells.at(count).push_back(tempcell);
            }
        }
    }
    
    if (!cells.empty() && cells.back().empty()) {
        cells.pop_back();
    }

    lines = cells.size();
    columns = cells[0].size();
    
    for (vector<Cell*> row : cells) {
        while (row.size() < (size_t)columns) {
            CellState* s = new Dead;
            Cell* tempcell = new Cell(s);
            row.push_back(tempcell);
        }

        if (row.size() > (size_t)columns) {
            row.resize(columns);
        }
    }
    
    getNeighbors();
}


void Grid::getNeighbors() {
    for (int a = 0; a < lines; a++) {
        for (int b = 0; b < columns; b++) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if(i == 0 && j == 0) continue;
                    int rowNeighbour = (a + i + lines) % lines;
                    int colNeighbour = (b + j + columns) % columns;
                    cells.at(rowNeighbour).at(colNeighbour)->getNeighbors();
                    cells.at(a).at(b)->addNeighbour(cells.at(rowNeighbour).at(colNeighbour));
                }
            }
        }
    }


    for (vector<Cell*> v : cells) {
        for (Cell* c : v) {
            c->checkNeighbour();
        }
    }

    createHash();

}

void Grid::update() {
    //cout << "oui6\n";
    Grid* newGrid = new Grid(lines,columns);
    int count = 0;
    //cout << "oui1\n";   
    for (vector<Cell*> v : cells) {
        //cout << "oui2\n";
        vector<Cell*> newV;
        //cout << "oui3\n";
        newGrid->cells.push_back(newV);
        //cout << "oui4\n";   
        for (Cell* c : v) {
            //cout << "oui5\n";
            newGrid->cells.at(count).push_back(c->evolution());
        }
        count += 1;
    }
    this->cells = newGrid->getCells();
    delete newGrid;

}


void Grid::print() {
    //cout << "oui10\n";
    for (vector<Cell*> v : cells){
        //cout << "oui8\n";
        for (Cell* c : v) {
            //cout << "oui9\n";
            if (dynamic_cast<Alive*>(c->getState())) {
                cout << "1";
            } else if (dynamic_cast<Dead*>(c->getState())) {
                cout << "0";
            } else if (dynamic_cast<Immortal*>(c->getState())) {
                cout << "2";
            } else if (dynamic_cast<Damned*>(c->getState())) {
                cout << "3";
            }
        }
        cout << endl;
    }
    cout << "--------------------------------------\n";

}

int Grid::getColums() const {
    return columns;
}
int Grid::getLines() const {
    return lines;
}
vector<vector<Cell*>> Grid::getCells() const {
    return cells;
}
void Grid::setCells(vector<vector<Cell*>> cells) {
    this->cells = cells;
} 

void Grid::createHash() {
    hash<string> hs;
    string s = "";
    for (vector<Cell*> v : cells){
        //cout << "oui8\n";
        for (Cell* c : v) {
            //cout << "oui9\n";
            if (dynamic_cast<Alive*>(c->getState())) {
                s += "1";
            } else if (dynamic_cast<Dead*>(c->getState())) {
                s += "0";
            } else if (dynamic_cast<Immortal*>(c->getState())) {
                s += "2";
            } else if (dynamic_cast<Damned*>(c->getState())) {
                s += "3";
            }
        }
    }
    h = hs(s);

}

size_t Grid::getHash() {
    return h;
}