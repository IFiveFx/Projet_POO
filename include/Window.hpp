#if !defined(DEF_WINDOW)
#define DEF_WINDOW

#include "Grid.hpp"
#include <SFML/Graphics.hpp>

class Window
{
private:
    int CellSize;
    Grid* grid;
    sf::RenderWindow* sfWindow;
public:
    Window(Grid* grid,int CellSize = 10);
    ~Window();
    void setCellSize(int CellSize);
    int getCellSize() const;
    void renderWindow(int iteration) const;
    void initWindow();
    sf::RenderWindow* getSfWindow() const;
};

#endif // DEF_WINDOW
