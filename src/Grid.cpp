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
    string textfile = f->read();
    vector<Cell*> v; 
    cells.push_back(v);
    int count = 0;
    for (char c : textfile) {
        if (c == char(10)) {
            vector<Cell*> v; 
            cells.push_back(v);
            count += 1;
        } else if (c == '0') {
            Cell* tempcell;
            CellState* s;
            s = new Dead;
            tempcell = new Cell(s);
            if (count < (int)cells.size()) {
                cells.at(count).push_back(tempcell);
            }
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

    #pragma omp parallel for
    for (vector<Cell*>& row : cells) {
        while (row.size() < (size_t)columns) {
            CellState* s = new Dead;
            Cell* tempcell = new Cell(s);
            row.push_back(tempcell);
        }

        if (row.size() > (size_t)columns) {
            row.resize(columns);
        }
    }
    
}


void Grid::getNeighbors() {
    #pragma omp parallel for
    for (int r = 0; r < (int)cells.size(); ++r) {
        for (Cell* c : cells[r]) {
            c->clearNeighbours();
        }
    }

    #pragma omp parallel for
    for (int a = 0; a < lines; a++) {
        for (int b = 0; b < columns; b++) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if(i == 0 && j == 0) continue;
                    int rowNeighbour = (a + i + lines) % lines;
                    int colNeighbour = (b + j + columns) % columns;
                    cells.at(a).at(b)->addNeighbour(cells.at(rowNeighbour).at(colNeighbour));
                }
            }
        }
    }
    #pragma omp parallel for
    for (int r = 0; r < (int)cells.size(); ++r) {
        for (Cell* c : cells[r]) {
            c->checkNeighbour();
        }
    }

    createHash();

}



void Grid::update() {
    Grid* newGrid = new Grid(lines,columns);
    newGrid->cells = vector<vector<Cell*>>(lines,vector<Cell*>());
    #pragma omp parallel for
    for (int v = 0; v < (int)cells.size(); v++) {
        vector<Cell*> newV;
        newGrid->cells.at(v) = newV;
        for (Cell* c : cells.at(v)) {
            newGrid->cells.at(v).push_back(c->evolution());
        }
    }
    this->cells = newGrid->getCells();
    delete newGrid;

}


void Grid::print() {
    for (vector<Cell*> v : cells){
        for (Cell* c : v) {
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
    if (lines <= 0 || columns <= 0) {
        h = hs(string());
        return;
    }

    const int total = lines * columns;
    vector<char> buf(total, '0');

    #pragma omp parallel for
    for (int v = 0; v < lines; v++) {
        for (int c = 0; c < columns; c++) {
            char code = '0';
            Cell* cell = cells.at(v).at(c);
            if (dynamic_cast<Alive*>(cell->getState())) {
                code = '1';
            } else if (dynamic_cast<Dead*>(cell->getState())) {
                code = '0';
            } else if (dynamic_cast<Immortal*>(cell->getState())) {
                code = '2';
            } else if (dynamic_cast<Damned*>(cell->getState())) {
                code = '3';
            }
            buf[v * columns + c] = code;
        }
    }

    string s(buf.begin(), buf.end());
    h = hs(s);

}

size_t Grid::getHash() {
    return h;
}