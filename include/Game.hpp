#if !defined(DEF_GAME)
#define DEF_GAME

#include "Grid.hpp"
#include "file.hpp"

class Game
{
private:
    int iteration;
public:
    Game(int OverPop, int UnderPop, int iteration = 0);
    ~Game() = default;
    bool run();
    void setOverPop(int OverPop);
    void setUnderPop(int UnderPop);
    int getOverPop() const;
    int getUnderPop() const;
};


#endif // DEF_GAME
