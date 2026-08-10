#ifndef FINISHLINE_H
#define FINISHLINE_H

#include <SFML/Graphics.hpp>

class FinishLine {
private:
    sf::RectangleShape shape;

public:
    FinishLine(float x, float groundTop);

    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
};

#endif