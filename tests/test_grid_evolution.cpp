#include <catch2/catch_all.hpp>
#include "Grid.hpp"
#include "Alive.hpp"
#include "Dead.hpp"
#include "GameRules.hpp"
#include "Cell.hpp"

// helper: build grid from int pattern
static Grid buildGrid(const std::vector<std::vector<int>>& pattern) {
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

// compare two grids by hash (createHash must be called to update hash)
static bool gridsEqual(Grid& a, Grid& b) {
    a.createHash();
    b.createHash();
    return a.getHash() == b.getHash();
}

TEST_CASE("Grid evolves to expected state after N iterations", "[grid][evolution]") {
    // Blinker example: vertical -> horizontal after 1 step
    std::vector<std::vector<int>> initial = {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0}
    };

    std::vector<std::vector<int>> after1 = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    Grid g = buildGrid(initial);
    Grid expected = buildGrid(after1);

    // Conway-like rules: survive with 2..3 neighbors, birth on 3 neighbors
    GameRules* rules = new GameRules(2, 3); // OverPop=3, UnderPop=2
    Cell::setRules(rules);

    // perform 1 iteration: must call getNeighbors() before each update
    g.getNeighbors();
    g.update();

    REQUIRE(gridsEqual(g, expected));

    delete rules;
}
