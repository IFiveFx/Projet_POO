#include "Window.hpp"
#include "Alive.hpp"
#include <Damned.hpp>
#include <Dead.hpp>
#include <Immortal.hpp>
#include <iostream>
using namespace std;



Window::Window(Grid* grid,int CellSize) : grid(grid) {
    // if (CellSize <= 0){this->CellSize = 10;return;}
    // this->CellSize = CellSize;
    if (grid->getColums() > grid->getLines()) {
        this->CellSize = (1920 / grid->getColums())*2;
    } else {
        this->CellSize = (1080 / grid->getLines())*2;
    }


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
void Window::renderWindow(int iteration) const {
    //cout << "oui31\n";
    int x, y;

    string it = " iteration : ";
    it += to_string(iteration);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text(it, font, 50);

    sfWindow->clear(sf::Color::Red);
    sf::RectangleShape cell(sf::Vector2f(CellSize - 1.0f, CellSize - 1.0f));
    // grid->getCells() stores rows (lines) as the outer vector and columns as inner.
    // Iterate by lines (y) then columns (x) and access cells[y][x].
    text.setPosition(0,0);
    text.setFillColor(sf::Color::White);
    sfWindow->draw(text);
    for (y = 0; y < grid->getLines(); ++y) {
        for (x = 0; x < grid->getColums(); ++x) {
            // safety: ensure indices exist before accessing with at()
            if (grid->getCells().size() <= (size_t)y || grid->getCells().at(y).size() <= (size_t)x) continue;
            if (dynamic_cast<Alive*>(grid->getCells().at(y).at(x)->getState()) ) {
                cell.setPosition(x * CellSize, (y * CellSize)+70);
                cell.setFillColor(sf::Color::White);
                sfWindow->draw(cell);
            } else if (dynamic_cast<Dead*>(grid->getCells().at(y).at(x)->getState()) ) {
                cell.setPosition(x * CellSize, (y * CellSize)+70);
                cell.setFillColor(sf::Color::Black);
                sfWindow->draw(cell);
            } else if (dynamic_cast<Immortal*>(grid->getCells().at(y).at(x)->getState()) ) {
                cell.setPosition(x * CellSize, (y * CellSize)+70);
                cell.setFillColor(sf::Color::Green);
                sfWindow->draw(cell);
            } else if (dynamic_cast<Damned*>(grid->getCells().at(y).at(x)->getState()) ) {
                cell.setPosition(x * CellSize, (y * CellSize)+70);
                cell.setFillColor(sf::Color::Blue);
                sfWindow->draw(cell);
            }
        }
    }
    sfWindow->display();
}

sf::RenderWindow* Window::getSfWindow() const {
    return sfWindow;
}