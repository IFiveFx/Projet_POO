#if !defined(DEF_CALCULS)
#define DEF_CALCULS

#include "Game.hpp"
#include "CellState.hpp"

class Calculs
{
public:
    virtual ~Calculs() = default;
    virtual CellState* use(int aliveNeighbour) = 0;
};


#endif // DEF_CALCULS
