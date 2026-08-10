#include "FinishLine.h"

FinishLine::FinishLine(float x, float groundTop) {
    const float width = 20.f;
    const float height = 150.f;

    shape.setSize(
        sf::Vector2f(width, height)
    );

    shape.setPosition(
        x,
        groundTop - height
    );

    shape.setFillColor(
        sf::Color::Green
    );
}

void FinishLine::draw(
    sf::RenderWindow& window
) const {
    window.draw(shape);
}

sf::FloatRect FinishLine::getBounds() const {
    return shape.getGlobalBounds();
}