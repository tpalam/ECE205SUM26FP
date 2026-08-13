#ifndef SPIKE_H
#define SPIKE_H

#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Spike : public Obstacle {
private:
    sf::ConvexShape shape;

public:
    Spike(
        float x,
        float platformTop
    );

    void update(float deltaTime) override;

    void draw(
        sf::RenderWindow& window
    ) const override;

    sf::FloatRect getBounds() const override;
};

#endif