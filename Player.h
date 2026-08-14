#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape box;

    float normalSpeed;
    float horizontalSpeed;
    float verticalVelocity;
    float gravity;
    float jumpVelocity;
    float rotationSpeed;

    bool onGround;
    bool alive;

    sf::FloatRect previousBounds;

public:
    Player();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    sf::FloatRect getPreviousBounds() const;
    sf::Vector2f getPosition() const;

    void landOn(float platformTop);

    bool jump();
    void die();
    void reset();

    void setHorizontalSpeed(float speed);
    void resetHorizontalSpeed();

    bool isAlive() const;
};

#endif
