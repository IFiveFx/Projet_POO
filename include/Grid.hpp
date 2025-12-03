#ifndef GRID_HPP
#define GRID_HPP
#include <vector>
#include <Cell.hpp>
#include <file.hpp>
using namespace std;

class Cell;


class Grid {
    private:
        size_t h;
        int lines;
        int columns;
        vector<vector<Cell*>> cells;
    public:
        Grid(int l = 0, int c = 0);
        void update();
        void init(File* f);
        void print();
        void getNeighbors();
        int getLines() const;
        int getColums() const;
        vector<vector<Cell*>> getCells() const;
        void createHash();
        size_t getHash();
    
};




#endif