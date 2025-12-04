#if !defined(DEF_CALCULS)
#define DEF_CALCULS

#include "CellState.hpp"
#include "Cell.hpp"

class Cell;

class Calculs
{
public:
    virtual ~Calculs() = default;
    virtual CellState* use(Cell* c) = 0;
};


#endif // DEF_CALCULS
