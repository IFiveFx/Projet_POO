#if !defined(DEF_CALCULSALIVE)
#define DEF_CALCULSALIVE

#include "calculs.hpp"

class CalculsAlive : public Calculs
{
public:
    CalculsAlive();
    ~CalculsAlive();
    CellState* use(Cell* c) override;
};


#endif // DEF_CALCULSALIVE
