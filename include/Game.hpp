#if !defined(DEF_GAME)
#define DEF_GAME

#include "Grid.hpp"
#include "file.hpp"
#include <unordered_map>
using namespace std;

class GameRules;

class Game
{
private:
    GameRules* rules;
    int iteration;
    unordered_map<size_t, int> hashes;
public:
    Game(int OverPop, int UnderPop, int iteration = 0);
    ~Game();
    bool run();
    void setRules(GameRules* rules);
    GameRules* getRules();
    string setFile();
    string setFileName(string path);
};


#endif // DEF_GAME
