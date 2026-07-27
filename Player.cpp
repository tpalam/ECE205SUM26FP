#include "Player.h"

Player::Player() {
    box.setSize(sf::Vector2f(50.f, 50.f));
    box.setPosition(50.f, 100.f);
    box.setFillColor(sf::Color::Cyan);

    horizontalSpeed = 200.f;

    verticalVelocity = 0.f;
    gravity = 1000.f;

    groundY = 500.f;
}

void Player::update(float deltaTime) {
    verticalVelocity += gravity * deltaTime;

    box.move(
        horizontalSpeed * deltaTime,
        verticalVelocity * deltaTime
    );

    float playerBottom = box.getPosition().y + box.getSize().y;

    if (playerBottom >= groundY) {
        box.setPosition(
            box.getPosition().x,
            groundY - box.getSize().y
        );

        verticalVelocity = 0.f;
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(box);
}