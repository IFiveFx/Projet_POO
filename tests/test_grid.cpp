#include <catch2/catch_all.hpp>
#include "Grid.hpp"
#include "Alive.hpp"
#include "Dead.hpp"


static Grid buildGridFromVec(const std::vector<std::vector<int>>& pattern) {
    int lines = (int)pattern.size();
    int cols = lines > 0 ? (int)pattern[0].size() : 0;
    Grid g(lines, cols);

    std::vector<std::vector<Cell*>> cells;
    cells.resize(lines);
    for (int r = 0; r < lines; ++r) {
        for (int c = 0; c < cols; ++c) {
            CellState* s = pattern[r][c] == 1 ? static_cast<CellState*>(new Alive) : static_cast<CellState*>(new Dead);
            cells[r].push_back(new Cell(s));
        }
    }
    g.setCells(cells);
    g.createHash();
    return g;
}

TEST_CASE("Grid basic dimensions and access", "[grid]") {
    Grid g(3,4);
    REQUIRE(g.getLines() == 3);
    REQUIRE(g.getColums() == 4);
}

TEST_CASE("Grid neighbor linking and count for blinker", "[grid][neighbors]") {
    std::vector<std::vector<int>> pattern = {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0}
    };
    Grid g = buildGridFromVec(pattern);
    g.getNeighbors();

    auto cells = g.getCells();
    Cell* center = cells[2][2];
    REQUIRE(center->getAliveNeighbors() == 2);
}
