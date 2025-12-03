#include "Window.hpp"
#include "Alive.hpp"
#include <iostream>
using namespace std;



Window::Window(Grid* grid,int CellSize) : grid(grid) {
    if (CellSize <= 0){this->CellSize = 10;return;}
    this->CellSize = CellSize;
}
Window::~Window() {
    delete sfWindow;
}
void Window::setCellSize(int CellSize) {
    if (CellSize <= 0){this->CellSize = 10;return;}
    this->CellSize = CellSize;
}
int Window::getCellSize() const {
    return CellSize;
}
void Window::initWindow() {
    sf::RenderWindow* out;
    out = new sf::RenderWindow (sf::VideoMode(CellSize * grid->getColums(),CellSize * grid->getLines()), "Game of life");
    this->sfWindow = out;
}
void Window::renderWindow() const {
    //cout << "oui31\n";
    int x, y;

    sfWindow->clear(sf::Color::Red);
    sf::RectangleShape cell(sf::Vector2f(CellSize - 1.0f, CellSize - 1.0f));
    for (x = 0; x < grid->getColums(); ++x) {
        for (y = 0; y < grid->getLines(); ++y) {
            if (dynamic_cast<Alive*>(grid->getCells().at(x).at(y)->getState()) ) {
                cell.setPosition(x * CellSize, y * CellSize);
                cell.setFillColor(sf::Color::White);
                sfWindow->draw(cell);
            } else {
                cell.setPosition(x * CellSize, y * CellSize);
                cell.setFillColor(sf::Color::Black);
                sfWindow->draw(cell);
            }
        }
    }
    sfWindow->display();
}

sf::RenderWindow* Window::getSfWindow() const {
    return sfWindow;
}