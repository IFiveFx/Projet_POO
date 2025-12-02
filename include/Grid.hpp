#if !defined(DEF_GRID)
#define DEF_GRID

#include "Cell.hpp"
#include <vector>
using namespace std;

class Grid
{
private:
    int ligne;
    int colonne;
    vector<Cell*> cells;
public:
    Grid(int ligne, int colonne);
    ~Grid() = default;
    int getLigne();
    int getColonne;
    void update();
    void init();
    void print();
};


#endif // DEF_GRID
