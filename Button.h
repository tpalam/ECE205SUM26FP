#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape box;
    sf::Text text;

public:
    Button(
        const sf::Font& font,
        const std::string& label,
        sf::Vector2f position,
        sf::Vector2f size
    );

    bool contains(sf::Vector2f point) const;
    void setHovered(bool hovered);
    void draw(sf::RenderWindow& window) const;
};

#endif
