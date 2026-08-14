#ifndef SLOWDOWN_H
#define SLOWDOWN_H

#include <SFML/Graphics.hpp>

#include "PowerUp.h"
#include "Player.h"

class SlowDown : public PowerUp {
private:
    sf::ConvexShape shape;

public:
    SlowDown(
        float x,
        float groundTop
    );

    void apply(Player& player) override;

    void draw(
        sf::RenderWindow& window
    ) const override;

    sf::FloatRect getBounds() const override;
};

#endif