#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform {
private:
    sf::RectangleShape shape;

public:
    Platform(
        float x,
        float y,
        float width,
        float height
    );

    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;

    float getTop() const;
};

#endif