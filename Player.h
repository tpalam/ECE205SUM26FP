#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape box;

    float horizontalSpeed;
    float verticalVelocity;
    float gravity;
    float groundY;

public:
    Player();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
};

#endif