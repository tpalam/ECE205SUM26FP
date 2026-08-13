#include "SawBlade.h"

#include <cmath>

namespace {
    const float PI = 3.14159265f;
}

SawBlade::SawBlade(
    float x,
    float y,
    float radius,
    SawBladeStyle style
) {
    this->style = style;

    rotationSpeed = 220.f;

    if (style == SawBladeStyle::Spiked) {
        createSpikedBlade(radius);
    }
    else {
        createGearBlade(radius);
    }

    // Position all parts at the same center.
    outerBlade.setPosition(x, y);

    innerCircle.setPosition(x, y);
    middleCircle.setPosition(x, y);
    centerCircle.setPosition(x, y);
}

void SawBlade::createSpikedBlade(float radius) {
    const int teeth = 18;

    const int pointCount =
        teeth * 2;

    outerBlade.setPointCount(
        pointCount
    );

    float innerRadius =
        radius * 0.72f;

    for (int i = 0; i < pointCount; i++) {
        float angle =
            static_cast<float>(i) *
            PI /
            static_cast<float>(teeth);

        float currentRadius;

        if (i % 2 == 0) {
            currentRadius = radius;
        }
        else {
            currentRadius = innerRadius;
        }

        float x =
            radius +
            std::cos(angle) *
            currentRadius;

        float y =
            radius +
            std::sin(angle) *
            currentRadius;

        outerBlade.setPoint(
            i,
            sf::Vector2f(x, y)
        );
    }

    outerBlade.setOrigin(
        radius,
        radius
    );

    outerBlade.setFillColor(
        sf::Color::Black
    );

    // Dark inner circle.
    innerCircle.setRadius(
        radius * 0.65f
    );

    innerCircle.setOrigin(
        innerCircle.getRadius(),
        innerCircle.getRadius()
    );

    innerCircle.setFillColor(
        sf::Color(5, 15, 30)
    );

    // Blue glow.
    middleCircle.setRadius(
        radius * 0.42f
    );

    middleCircle.setOrigin(
        middleCircle.getRadius(),
        middleCircle.getRadius()
    );

    middleCircle.setFillColor(
        sf::Color(0, 70, 150)
    );

    // Bright blue center.
    centerCircle.setRadius(
        radius * 0.20f
    );

    centerCircle.setOrigin(
        centerCircle.getRadius(),
        centerCircle.getRadius()
    );

    centerCircle.setFillColor(
        sf::Color(0, 120, 255)
    );
}

void SawBlade::createGearBlade(float radius) {
    const int teeth = 12;

    const int pointsPerTooth = 4;

    const int pointCount =
        teeth * pointsPerTooth;

    outerBlade.setPointCount(
        pointCount
    );

    float rootRadius =
        radius * 0.78f;

    float toothRadius =
        radius;

    for (int tooth = 0; tooth < teeth; tooth++) {
        float baseAngle =
            static_cast<float>(tooth) *
            2.f *
            PI /
            static_cast<float>(teeth);

        float toothAngle =
            2.f *
            PI /
            static_cast<float>(teeth);

        float angles[4] = {
            baseAngle,
            baseAngle + toothAngle * 0.25f,
            baseAngle + toothAngle * 0.75f,
            baseAngle + toothAngle
        };

        float radii[4] = {
            rootRadius,
            toothRadius,
            toothRadius,
            rootRadius
        };

        for (int j = 0; j < 4; j++) {
            int index =
                tooth * 4 + j;

            float x =
                radius +
                std::cos(angles[j]) *
                radii[j];

            float y =
                radius +
                std::sin(angles[j]) *
                radii[j];

            outerBlade.setPoint(
                index,
                sf::Vector2f(x, y)
            );
        }
    }

    outerBlade.setOrigin(
        radius,
        radius
    );

    outerBlade.setFillColor(
        sf::Color::Black
    );

    // White border like the reference image.
    outerBlade.setOutlineThickness(
        4.f
    );

    outerBlade.setOutlineColor(
        sf::Color::White
    );

    // Outer blue ring.
    innerCircle.setRadius(
        radius * 0.60f
    );

    innerCircle.setOrigin(
        innerCircle.getRadius(),
        innerCircle.getRadius()
    );

    innerCircle.setFillColor(
        sf::Color(40, 110, 200)
    );

    // Darker blue middle.
    middleCircle.setRadius(
        radius * 0.43f
    );

    middleCircle.setOrigin(
        middleCircle.getRadius(),
        middleCircle.getRadius()
    );

    middleCircle.setFillColor(
        sf::Color(0, 55, 130)
    );

    // Light center.
    centerCircle.setRadius(
        radius * 0.20f
    );

    centerCircle.setOrigin(
        centerCircle.getRadius(),
        centerCircle.getRadius()
    );

    centerCircle.setFillColor(
        sf::Color(100, 160, 220)
    );
}

void SawBlade::update(float deltaTime) {
    float rotation =
        rotationSpeed * deltaTime;

    outerBlade.rotate(rotation);
}

void SawBlade::draw(
    sf::RenderWindow& window
) const {
    window.draw(outerBlade);

    window.draw(innerCircle);

    window.draw(middleCircle);

    window.draw(centerCircle);
}

sf::FloatRect SawBlade::getBounds() const {
    return outerBlade.getGlobalBounds();
}