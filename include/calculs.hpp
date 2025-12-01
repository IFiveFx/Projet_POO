#if !defined(DEF_CALCULS)
#define DEF_CALCULS

class CellState;

class Calculs
{
public:
    virtual ~Calculs() = default;
    virtual CellState* use() = 0;
};


#endif // DEF_CALCULS
