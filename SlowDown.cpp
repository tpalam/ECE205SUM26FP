#include "SlowDown.h"

SlowDown::SlowDown(
    float x,
    float groundTop
) {
    const float width = 70.f;
    const float height = 70.f;

    shape.setPointCount(6);

    shape.setPoint(
        0,
        sf::Vector2f(width, 0.f)
    );

    shape.setPoint(
        1,
        sf::Vector2f(width * 0.45f, 0.f)
    );

    shape.setPoint(
        2,
        sf::Vector2f(0.f, height / 2.f)
    );

    shape.setPoint(
        3,
        sf::Vector2f(width * 0.45f, height)
    );

    shape.setPoint(
        4,
        sf::Vector2f(width, height)
    );

    shape.setPoint(
        5,
        sf::Vector2f(width * 0.55f, height / 2.f)
    );

    shape.setPosition(
        x,
        groundTop - height
    );

    shape.setFillColor(
        sf::Color(255, 190, 30)
    );

    shape.setOutlineThickness(4.f);

    shape.setOutlineColor(
        sf::Color::White
    );
}

void SlowDown::apply(Player& player) {
    player.resetHorizontalSpeed();
}

void SlowDown::draw(
    sf::RenderWindow& window
) const {
    if (active) {
        window.draw(shape);
    }
}

sf::FloatRect SlowDown::getBounds() const {
    return shape.getGlobalBounds();
}
