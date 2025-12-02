#if !defined(DEF_CALCULSDEAD)
#define DEF_CALCULSDEAD

#include "calculs.hpp"

class CalculsDead : public Calculs
{
public:
    CalculsDead() = default;
    ~CalculsDead() = default;
    CellState* use(Cell* c) override;
};


#endif // DEF_CALCULSDEAD
