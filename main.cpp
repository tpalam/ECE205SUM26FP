#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Spike.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(1000, 600),
        "Geometry Dash"
    );

    window.setFramerateLimit(60);

    Player player;

    Platform ground(0.f, 500.f, 1000.f, 100.f);

    Spike spike(600.f, ground.getTop());

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::R) {
                player.reset();
            }
        }

        player.update(deltaTime);

        sf::FloatRect currentBounds =
            player.getBounds();

        sf::FloatRect previousBounds =
            player.getPreviousBounds();

        sf::FloatRect platformBounds =
            ground.getBounds();

        if (currentBounds.intersects(platformBounds)) {
            float previousBottom =
                previousBounds.top + previousBounds.height;

            float currentBottom =
                currentBounds.top + currentBounds.height;

            float platformTop =
                platformBounds.top;

            bool cameFromAbove =
                previousBottom <= platformTop &&
                currentBottom >= platformTop;

            if (cameFromAbove) {
                player.landOn(platformTop);
            }
        }

        sf::FloatRect spikeBounds =
            spike.getBounds();

        if (player.getBounds().intersects(spikeBounds)) {
            player.die();
        }

        window.clear(sf::Color(25, 25, 40));

        ground.draw(window);
        spike.draw(window);
        player.draw(window);

        window.display();
    }

    return 0;
}