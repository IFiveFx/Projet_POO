#if !defined(DEF_GAMERULES)
#define DEF_GAMERULES



class GameRules
{
private:
    int OverPop;
    int UnderPop;
public:
    GameRules(int OverPop, int UnderPop);
    ~GameRules();
    void setOverPop(int overPop);
    void setUnderPop(int UnderPop);
    int getOverPop();
    int getUnderPop();
};


#endif // DEF_GAMERULES
