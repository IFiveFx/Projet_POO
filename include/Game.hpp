#if !defined(DEF_GAME)
#define DEF_GAME

#include "Grid.hpp"
#include "file.hpp"

class GameRules;

class Game
{
private:
    GameRules* rules;
    int iteration;
public:
    Game(int OverPop, int UnderPop, int iteration = 0);
    ~Game() = default;
    bool run();
    void setRules(GameRules* rules);
    GameRules* getRules();
};


#endif // DEF_GAME
