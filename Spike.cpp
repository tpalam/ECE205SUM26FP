#include "Spike.h"

Spike::Spike(float x, float platformTop) {
    const float width = 50.f;
    const float height = 50.f;

    shape.setPointCount(3);

    shape.setPoint(
        0,
        sf::Vector2f(0.f, height)
    );

    shape.setPoint(
        1,
        sf::Vector2f(width / 2.f, 0.f)
    );

    shape.setPoint(
        2,
        sf::Vector2f(width, height)
    );

    shape.setPosition(
        x,
        platformTop - height
    );

    shape.setFillColor(
        sf::Color::Red
    );
}

void Spike::draw(
    sf::RenderWindow& window
) const {
    window.draw(shape);
}

sf::FloatRect Spike::getBounds() const {
    return shape.getGlobalBounds();
}

void Spike::update(float) {
    // Spike is stationary.
}