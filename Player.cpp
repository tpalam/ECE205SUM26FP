#include "Player.h"

Player::Player() {
    box.setSize(sf::Vector2f(50.f, 50.f));

    box.setOrigin(
        box.getSize().x / 2.f,
        box.getSize().y / 2.f
    );

    box.setPosition(75.f, 125.f);

    box.setFillColor(sf::Color::Cyan);

    horizontalSpeed = 200.f;
    verticalVelocity = 0.f;
    gravity = 1200.f;
    jumpVelocity = -650.f;
    rotationSpeed = 90.f;

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

    if (!onGround) {
        box.rotate(rotationSpeed * deltaTime);
    }
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
        platformTop - box.getSize().y / 2.f
    );

    verticalVelocity = 0.f;
    onGround = true;

    box.setRotation(0.f);
}

bool Player::jump() {
    if (onGround && alive) {
        verticalVelocity = jumpVelocity;
        onGround = false;

        return true;
    }

    return false;
}

void Player::die() {
    alive = false;
    box.setFillColor(sf::Color::Red);
}

void Player::reset() {
    box.setPosition(75.f, 125.f);
    box.setRotation(0.f);
    box.setFillColor(sf::Color::Cyan);

    verticalVelocity = 0.f;

    onGround = false;
    alive = true;

    previousBounds = box.getGlobalBounds();
}

bool Player::isAlive() const {
    return alive;
}