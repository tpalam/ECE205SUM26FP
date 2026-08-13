#ifndef SAWBLADE_H
#define SAWBLADE_H

#include <SFML/Graphics.hpp>
#include "Obstacle.h"

enum class SawBladeStyle {
    Spiked,
    Gear
};

class SawBlade : public Obstacle {
private:
    sf::ConvexShape outerBlade;

    sf::CircleShape innerCircle;
    sf::CircleShape middleCircle;
    sf::CircleShape centerCircle;

    float rotationSpeed;

    SawBladeStyle style;

    void createSpikedBlade(float radius);
    void createGearBlade(float radius);

public:
    SawBlade(
        float x,
        float y,
        float radius,
        SawBladeStyle style
    );

    void update(float deltaTime) override;

    void draw(
        sf::RenderWindow& window
    ) const override;

    sf::FloatRect getBounds() const override;
};

#endif