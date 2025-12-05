#include <catch2/catch_all.hpp>
#include "Cell.hpp"
#include "Alive.hpp"
#include "Dead.hpp"
#include <Immortal.hpp>

TEST_CASE("Cell neighbor management", "[cell]") {
    Alive* astate = new Alive();
    Dead* dstate = new Dead();

    Cell c1(astate);
    Cell c2(dstate);

    REQUIRE(c1.getNeighbors().empty());
    c1.addNeighbour(&c2);
    REQUIRE(c1.getNeighbors().size() == 1);
    c1.clearNeighbours();
    REQUIRE(c1.getNeighbors().empty());
}

TEST_CASE("Cell checkNeighbour counts alive and immortal", "[cell][count]") {
    Alive* astate = new Alive();
    Dead* dstate = new Dead();
    Immortal* istate = new Immortal();

    Cell c1(dstate);
    Cell neighbor1(astate);
    Cell neighbor2(istate);

    c1.addNeighbour(&neighbor1);
    c1.addNeighbour(&neighbor2);

    c1.checkNeighbour();
    REQUIRE(c1.getAliveNeighbors() == 2);
}
