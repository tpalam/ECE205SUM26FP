#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape box;

    float horizontalSpeed;
    float verticalVelocity;
    float gravity;
    bool alive;

    sf::FloatRect previousBounds;

public:
    Player();
    void die();
    void reset();
    bool isAlive() const;
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    sf::FloatRect getPreviousBounds() const;

    void landOn(float platformTop);
    void setColor(const sf::Color& color);
};

#endif