#ifndef GRID_HPP
#define GRID_HPP
#include <vector>
#include <Cell.hpp>
#include <file.hpp>
using namespace std;

class Cell;


class Grid {
    private:
    int lines;
    int columns;
    vector<vector<Cell*>> cells;
    public:
    Grid(int l, int c);
    Grid* update();
    void init(File* f);
    void print();
    
};




#endif