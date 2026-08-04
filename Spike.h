#ifndef SPIKE_H
#define SPIKE_H

#include <SFML/Graphics.hpp>

class Spike {
private:
    sf::ConvexShape shape;

public:
    Spike(float x, float platformTop);

    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
};

#endif