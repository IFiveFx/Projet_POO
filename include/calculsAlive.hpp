#if !defined(DEF_CALCULSALIVE)
#define DEF_CALCULSALIVE

#include "calculs.hpp"

class CalculsAlive : public Calculs
{
public:
    CalculsAlive() = default;
    ~CalculsAlive() = default;
    CellState* use(Cell* c) override;
};


#endif // DEF_CALCULSALIVE
