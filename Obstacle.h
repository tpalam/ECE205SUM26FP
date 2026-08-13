#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    virtual void update(float deltaTime) = 0;

    virtual void draw(
        sf::RenderWindow& window
    ) const = 0;

    virtual sf::FloatRect getBounds() const = 0;

    virtual ~Obstacle() = default;
};

#endif