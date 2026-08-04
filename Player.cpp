#include "Player.h"

Player::Player() {
    box.setSize(sf::Vector2f(50.f, 50.f));
    box.setPosition(50.f, 100.f);
    box.setFillColor(sf::Color::Cyan);

    horizontalSpeed = 200.f;
    verticalVelocity = 0.f;
    gravity = 1000.f;

    previousBounds = box.getGlobalBounds();
}

void Player::update(float deltaTime) {
    previousBounds = box.getGlobalBounds();

    verticalVelocity += gravity * deltaTime;

    box.move(
        horizontalSpeed * deltaTime,
        verticalVelocity * deltaTime
    );
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(box);
}

sf::FloatRect Player::getBounds() const {
    return box.getGlobalBounds();
}

sf::FloatRect Player::getPreviousBounds() const {
    return previousBounds;
}

void Player::landOn(float platformTop) {
    box.setPosition(
        box.getPosition().x,
        platformTop - box.getSize().y
    );

    verticalVelocity = 0.f;
}
void Player::setColor(const sf::Color& color) {
    box.setFillColor(color);
}