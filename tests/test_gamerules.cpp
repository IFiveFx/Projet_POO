#include <catch2/catch_all.hpp>
#include "GameRules.hpp"

TEST_CASE("GameRules getters and setters", "[gamerules]") {
    GameRules g(2, 3);
    // The header declares GameRules(int OverPop, int UnderPop);
    // Implementation has reversed params; this test will help detect that.
    REQUIRE(g.getOverPop() == 3);
    REQUIRE(g.getUnderPop() == 2);

    g.setOverPop(5);
    g.setUnderPop(1);
    REQUIRE(g.getOverPop() == 5);
    REQUIRE(g.getUnderPop() == 1);

    // negative inputs should be normalized to positive
    g.setOverPop(-4);
    g.setUnderPop(-2);
    REQUIRE(g.getOverPop() == 4);
    REQUIRE(g.getUnderPop() == 2);
}
