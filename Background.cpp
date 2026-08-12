#include "Background.h"

Background::Background() {
    for (int i = 0; i < 30; i++) {
        sf::RectangleShape stripe;

        stripe.setSize(
            sf::Vector2f(60.f, 600.f)
        );

        stripe.setPosition(
            static_cast<float>(i) * 300.f,
            0.f
        );

        stripe.setFillColor(
            sf::Color(35, 35, 65)
        );

        stripes.push_back(stripe);
    }
}

void Background::draw(
    sf::RenderWindow& window,
    const sf::View& camera
) {
    sf::View backgroundView =
        window.getDefaultView();

    float cameraX =
        camera.getCenter().x;

    float parallaxX =
        cameraX * 0.3f;

    backgroundView.setCenter(
        parallaxX + 500.f,
        300.f
    );

    window.setView(
        backgroundView
    );

    for (const sf::RectangleShape& stripe : stripes) {
        window.draw(stripe);
    }
}