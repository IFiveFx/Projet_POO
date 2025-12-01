#if !defined(DEF_CALCULSDEAD)
#define DEF_CALCULSDEAD

#include "calculs.hpp"

class CalculsDead : public Calculs
{
public:
    CalculsDead();
    ~CalculsDead();
    CellState* use() override;
};


#endif // DEF_CALCULSDEAD
