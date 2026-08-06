#include <SFML/Graphics.hpp>
#include <vector>

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

std::vector<Platform> platforms;

platforms.emplace_back(0.f, 500.f, 3000.f, 100.f);
platforms.emplace_back(800.f, 400.f, 200.f, 100.f);
platforms.emplace_back(1200.f, 350.f, 200.f, 150.f);

std::vector<Spike> spikes;

spikes.emplace_back(600.f, 500.f);
spikes.emplace_back(1050.f, 500.f);
spikes.emplace_back(1100.f, 500.f);
spikes.emplace_back(1500.f, 500.f);

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

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space) {
                player.jump();
            }
        }

        player.update(deltaTime);

        sf::FloatRect currentBounds = player.getBounds();

        sf::FloatRect previousBounds = player.getPreviousBounds();

        for (const Platform& platform : platforms) {
            sf::FloatRect platformBounds = platform.getBounds();

            if (currentBounds.intersects(platformBounds)) {
                float previousBottom = previousBounds.top + previousBounds.height;

                float currentBottom = currentBounds.top + currentBounds.height;

                float platformTop =platformBounds.top;

                bool cameFromAbove =
                    previousBottom <= platformTop &&
                    currentBottom >= platformTop;

                if (cameFromAbove) {
                    player.landOn(platformTop);
                    // Refresh because landOn() changed the player's position.
                    currentBounds = player.getBounds();
                }
            }
        }

        for (const Spike& spike : spikes) {
            if (player.getBounds().intersects(
                    spike.getBounds())) {
                player.die();
                break;
            }
        }

        window.clear(sf::Color(25, 25, 40));

        for (const Platform& platform : platforms) {
            platform.draw(window);
        }

        for (const Spike& spike : spikes) {
            spike.draw(window);
        }
        player.draw(window);

        window.display();
    }

    return 0;
}