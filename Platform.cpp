#include "Platform.h"

Platform::Platform(float x, float y, float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(100, 100, 100));
}

void Platform::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

float Platform::getTop() const {
    return shape.getPosition().y;
}