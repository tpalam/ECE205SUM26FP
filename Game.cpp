#include "Game.h"

Game::Game()
    : window(
          sf::VideoMode(1000, 600),
          "Geometry Dash"
      ),
      camera(
          sf::FloatRect(0.f, 0.f, 1000.f, 600.f)
      ) {

    window.setFramerateLimit(60);

    platforms.emplace_back(
        0.f,
        500.f,
        3000.f,
        100.f
    );

    platforms.emplace_back(
        800.f,
        400.f,
        200.f,
        100.f
    );

    platforms.emplace_back(
        1200.f,
        350.f,
        200.f,
        150.f
    );

    spikes.emplace_back(
        600.f,
        500.f
    );

    spikes.emplace_back(
        1050.f,
        500.f
    );

    spikes.emplace_back(
        1100.f,
        500.f
    );

    spikes.emplace_back(
        1500.f,
        500.f
    );
}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime =
            clock.restart().asSeconds();

        processEvents();

        update(deltaTime);

        render();
    }
}

void Game::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::R) {

            player.reset();
            camera.setCenter(500.f, 300.f);
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space) {

            player.jump();
        }
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);

    handlePlatformCollisions();
    handleSpikeCollisions();
    updateCamera();
}

void Game::handlePlatformCollisions() {
    sf::FloatRect currentBounds =
        player.getBounds();

    sf::FloatRect previousBounds =
        player.getPreviousBounds();

    for (const Platform& platform : platforms) {
        sf::FloatRect platformBounds =
            platform.getBounds();

        if (currentBounds.intersects(platformBounds)) {
            float previousBottom =
                previousBounds.top +
                previousBounds.height;

            float currentBottom =
                currentBounds.top +
                currentBounds.height;

            float platformTop =
                platformBounds.top;

            bool cameFromAbove =
                previousBottom <= platformTop &&
                currentBottom >= platformTop;

            if (cameFromAbove) {
                player.landOn(platformTop);

                currentBounds =
                    player.getBounds();
            }
        }
    }
}

void Game::handleSpikeCollisions() {
    for (const Spike& spike : spikes) {
        if (player.getBounds().intersects(
                spike.getBounds())) {

            player.die();
            break;
        }
    }
}

void Game::updateCamera() {
    float cameraX =
        player.getPosition().x + 300.f;

    if (cameraX < 500.f) {
        cameraX = 500.f;
    }

    camera.setCenter(
        cameraX,
        300.f
    );
}

void Game::render() {
    window.clear(
        sf::Color(25, 25, 40)
    );

    window.setView(camera);

    for (const Platform& platform : platforms) {
        platform.draw(window);
    }

    for (const Spike& spike : spikes) {
        spike.draw(window);
    }

    player.draw(window);

    window.display();
}