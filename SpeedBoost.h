#ifndef SPEEDBOOST_H
#define SPEEDBOOST_H

#include <SFML/Graphics.hpp>

#include "PowerUp.h"
#include "Player.h"

class SpeedBoost : public PowerUp {
private:
    sf::ConvexShape shape;

    float boostedSpeed;

public:
    SpeedBoost(
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