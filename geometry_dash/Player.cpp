#include "Player.h"

Player::Player()
    : velocity(0.f, 0.f),
      startPosition(120.f, 430.f),
      moveSpeed(260.f),
      jumpSpeed(590.f),
      gravity(1650.f),
      onGround(false),
      alive(true) {

    shape.setSize(sf::Vector2f(42.f, 42.f));
    shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
    shape.setPosition(startPosition);
    shape.setFillColor(sf::Color(40, 220, 255));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(3.f);

    previousBounds = shape.getGlobalBounds();
}

void Player::handleEvent(const sf::Event& event) {
    if (!alive) {
        return;
    }

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Space &&
        onGround) {
        velocity.y = -jumpSpeed;
        onGround = false;
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        onGround) {
        velocity.y = -jumpSpeed;
        onGround = false;
    }
}

void Player::update(float deltaTime) {
    previousBounds = shape.getGlobalBounds();

    if (!alive) {
        return;
    }

    velocity.x = moveSpeed;
    velocity.y += gravity * deltaTime;

    shape.move(velocity * deltaTime);

    if (!onGround) {
        shape.rotate(300.f * deltaTime);
    }

    onGround = false;
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Player::landOn(float surfaceY) {
    sf::Vector2f position = shape.getPosition();
    position.y = surfaceY - shape.getSize().y / 2.f;
    shape.setPosition(position);

    velocity.y = 0.f;
    onGround = true;

    float rotation = shape.getRotation();
    float snapped = static_cast<float>(static_cast<int>((rotation + 45.f) / 90.f) * 90);
    shape.setRotation(snapped);
}

void Player::die() {
    alive = false;
    velocity = sf::Vector2f(0.f, 0.f);
    shape.setFillColor(sf::Color(255, 70, 70));
}

void Player::reset() {
    shape.setPosition(startPosition);
    shape.setRotation(0.f);
    shape.setFillColor(sf::Color(40, 220, 255));

    velocity = sf::Vector2f(0.f, 0.f);
    previousBounds = shape.getGlobalBounds();
    onGround = false;
    alive = true;
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

sf::FloatRect Player::getPreviousBounds() const {
    return previousBounds;
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

bool Player::isAlive() const {
    return alive;
}

bool Player::isOnGround() const {
    return onGround;
}
