#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

class Background {
private:
    std::vector<sf::RectangleShape> stripes;

public:
    Background();

    void draw(
        sf::RenderWindow& window,
        const sf::View& camera
    );
};

#endif