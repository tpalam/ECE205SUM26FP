#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(
    float x,
    float groundTop
) {
    const float width = 70.f;
    const float height = 70.f;

    shape.setPointCount(6);

    shape.setPoint(
        0,
        sf::Vector2f(0.f, 0.f)
    );

    shape.setPoint(
        1,
        sf::Vector2f(width * 0.55f, 0.f)
    );

    shape.setPoint(
        2,
        sf::Vector2f(width, height / 2.f)
    );

    shape.setPoint(
        3,
        sf::Vector2f(width * 0.55f, height)
    );

    shape.setPoint(
        4,
        sf::Vector2f(0.f, height)
    );

    shape.setPoint(
        5,
        sf::Vector2f(width * 0.45f, height / 2.f)
    );

    shape.setPosition(
        x,
        groundTop - height
    );

    shape.setFillColor(
        sf::Color(40, 230, 40)
    );

    shape.setOutlineThickness(4.f);

    shape.setOutlineColor(
        sf::Color::White
    );

    boostedSpeed = 350.f;
}

void SpeedBoost::apply(Player& player) {
    player.setHorizontalSpeed(
        boostedSpeed
    );
}

void SpeedBoost::draw(
    sf::RenderWindow& window
) const {
    if (active) {
        window.draw(shape);
    }
}

sf::FloatRect SpeedBoost::getBounds() const {
    return shape.getGlobalBounds();
}
