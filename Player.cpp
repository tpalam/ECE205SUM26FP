#include "Player.h"

Player::Player() {
    box.setSize(sf::Vector2f(50.f, 50.f));
    box.setPosition(50.f, 275.f);
    box.setFillColor(sf::Color::Cyan);

    speed = 200.f;
}

void Player::update(float deltaTime) {
    box.move(speed * deltaTime, 0.f);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(box);
}