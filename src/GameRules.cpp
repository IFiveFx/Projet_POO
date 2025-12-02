#include "GameRules.hpp"

GameRules::GameRules(int OverPop, int UnderPop) : OverPop(OverPop),UnderPop(UnderPop) {}
GameRules::~GameRules() {}
void GameRules::setOverPop(int OverPop) {
    if (OverPop < 0)
    {
        this->OverPop = -OverPop;
        return;
    }
    this->OverPop = OverPop;
    
}
void GameRules::setUnderPop(int UnderPop) {
    if (UnderPop < 0)
    {
        this->UnderPop = -UnderPop;
        return;
    }
    this->UnderPop = UnderPop;
    
}
int GameRules::getOverPop() {
    return this->OverPop;
}
int GameRules::getUnderPop() {
    return this->UnderPop;
}