#include "Player.h"

Player::Player() {
    box.setSize(sf::Vector2f(50.f, 50.f));
    box.setPosition(50.f, 100.f);
    box.setFillColor(sf::Color::Cyan);

    horizontalSpeed = 200.f;
    verticalVelocity = 0.f;
    gravity = 1000.f;
    jumpVelocity = -600.f;

    onGround = false;
    alive = true;

    previousBounds = box.getGlobalBounds();
}

void Player::update(float deltaTime) {
    if (!alive) {
        return;
    }

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

sf::Vector2f Player::getPosition() const {
    return box.getPosition();
}

void Player::landOn(float platformTop) {
    box.setPosition(
        box.getPosition().x,
        platformTop - box.getSize().y
    );

    verticalVelocity = 0.f;
    onGround = true;
}

void Player::jump() {
    if (onGround && alive) {
        verticalVelocity = jumpVelocity;
        onGround = false;
    }
}

void Player::die() {
    alive = false;
    box.setFillColor(sf::Color::Red);
}

void Player::reset() {
    box.setPosition(50.f, 100.f);
    box.setFillColor(sf::Color::Cyan);

    verticalVelocity = 0.f;

    onGround = false;
    alive = true;

    previousBounds = box.getGlobalBounds();
}

bool Player::isAlive() const {
    return alive;
}