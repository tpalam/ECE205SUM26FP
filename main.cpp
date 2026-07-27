#include <SFML/Graphics.hpp>
#include "Player.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(1000, 600),
        "Geometry Dash"
    );

    window.setFramerateLimit(60);

    Player player;

    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(1000.f, 100.f));
    ground.setPosition(0.f, 500.f);
    ground.setFillColor(sf::Color(100, 100, 100));

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player.update(deltaTime);

        window.clear(sf::Color(25, 25, 40));

        window.draw(ground);
        player.draw(window);

        window.display();
    }

    return 0;
}