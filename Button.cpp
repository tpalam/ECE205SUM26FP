#include "Button.h"

Button::Button(
    const sf::Font& font,
    const std::string& label,
    sf::Vector2f position,
    sf::Vector2f size
) {
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(sf::Color(45, 105, 190));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(3.f);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );
    text.setPosition(
        position.x + size.x / 2.f,
        position.y + size.y / 2.f
    );
}

bool Button::contains(sf::Vector2f point) const {
    return box.getGlobalBounds().contains(point);
}

void Button::setHovered(bool hovered) {
    box.setFillColor(
        hovered
            ? sf::Color(70, 155, 245)
            : sf::Color(45, 105, 190)
    );
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(text);
}
