#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

class Player;

class PowerUp {
protected:
    bool active = true;

public:
    virtual void apply(Player& player) = 0;

    virtual void draw(
        sf::RenderWindow& window
    ) const = 0;

    virtual sf::FloatRect getBounds() const = 0;

    bool isActive() const {
        return active;
    }

    void deactivate() {
        active = false;
    }

    void reset() {
        active = true;
    }

    virtual ~PowerUp() = default;
};

#endif
