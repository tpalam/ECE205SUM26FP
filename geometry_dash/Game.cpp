#include "Game.h"
#include <algorithm>

Game::Game()
    : window(sf::VideoMode(1000, 600), "SFML Geometry Dash Clone"),
      camera(sf::FloatRect(0.f, 0.f, 1000.f, 600.f)),
      levelComplete(false),
      groundY(500.f),
      levelLength(5200.f) {

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    ground.setSize(sf::Vector2f(levelLength, 100.f));
    ground.setPosition(0.f, groundY);
    ground.setFillColor(sf::Color(45, 45, 70));
    ground.setOutlineColor(sf::Color(130, 130, 200));
    ground.setOutlineThickness(3.f);

    buildLevel();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();

        float deltaTime = frameClock.restart().asSeconds();
        deltaTime = std::min(deltaTime, 0.033f);

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
            event.key.code == sf::Keyboard::Escape) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::R) {
            resetLevel();
        }

        player.handleEvent(event);
    }
}

void Game::update(float deltaTime) {
    if (!levelComplete) {
        player.update(deltaTime);
        handleCollisions();
    }

    updateCamera();
}

void Game::render() {
    window.clear(sf::Color(18, 18, 38));
    window.setView(camera);

    // Simple background stripes to show movement.
    for (int i = 0; i < 30; ++i) {
        sf::RectangleShape stripe(sf::Vector2f(50.f, 600.f));
        stripe.setPosition(static_cast<float>(i) * 300.f, 0.f);
        stripe.setFillColor(sf::Color(25, 25, 50));
        window.draw(stripe);
    }

    window.draw(ground);

    for (const Obstacle& obstacle : obstacles) {
        obstacle.draw(window);
    }

    player.draw(window);

    // UI drawn using the default view; no font asset is required.
    window.setView(window.getDefaultView());

    sf::RectangleShape progressBackground(sf::Vector2f(700.f, 14.f));
    progressBackground.setPosition(150.f, 24.f);
    progressBackground.setFillColor(sf::Color(60, 60, 80));

    float progress = player.getPosition().x / levelLength;
    progress = std::max(0.f, std::min(progress, 1.f));

    sf::RectangleShape progressBar(sf::Vector2f(700.f * progress, 14.f));
    progressBar.setPosition(150.f, 24.f);
    progressBar.setFillColor(levelComplete ? sf::Color(70, 255, 120)
                                           : sf::Color(40, 220, 255));

    window.draw(progressBackground);
    window.draw(progressBar);

    window.display();
}

void Game::resetLevel() {
    player.reset();
    levelComplete = false;
    frameClock.restart();

    camera.setCenter(500.f, 300.f);
}

void Game::buildLevel() {
    obstacles.clear();

    obstacles.push_back(Obstacle::createSpike(700.f, groundY));
    obstacles.push_back(Obstacle::createSpike(980.f, groundY));
    obstacles.push_back(Obstacle::createSpike(1030.f, groundY));

    obstacles.push_back(Obstacle::createPlatform(1300.f, 420.f, 240.f, 80.f));
    obstacles.push_back(Obstacle::createSpike(1600.f, groundY));
    obstacles.push_back(Obstacle::createSpike(1650.f, groundY));

    obstacles.push_back(Obstacle::createPlatform(1900.f, 380.f, 200.f, 120.f));
    obstacles.push_back(Obstacle::createSpike(2180.f, groundY));

    obstacles.push_back(Obstacle::createPlatform(2400.f, 440.f, 160.f, 60.f));
    obstacles.push_back(Obstacle::createPlatform(2700.f, 390.f, 180.f, 110.f));
    obstacles.push_back(Obstacle::createPlatform(3030.f, 340.f, 200.f, 160.f));

    obstacles.push_back(Obstacle::createSpike(3340.f, groundY));
    obstacles.push_back(Obstacle::createSpike(3390.f, groundY));
    obstacles.push_back(Obstacle::createSpike(3440.f, groundY));

    obstacles.push_back(Obstacle::createPlatform(3750.f, 410.f, 260.f, 90.f));
    obstacles.push_back(Obstacle::createSpike(4110.f, groundY));
    obstacles.push_back(Obstacle::createSpike(4370.f, groundY));
    obstacles.push_back(Obstacle::createSpike(4420.f, groundY));

    obstacles.push_back(Obstacle::createFinish(4900.f, groundY));
}

void Game::handleCollisions() {
    if (!player.isAlive()) {
        return;
    }

    sf::FloatRect current = player.getBounds();
    sf::FloatRect previous = player.getPreviousBounds();

    const float currentBottom = current.top + current.height;
    const float previousBottom = previous.top + previous.height;

    bool landed = false;

    // Ground collision.
    if (currentBottom >= groundY && previousBottom <= groundY + 15.f) {
        player.landOn(groundY);
        landed = true;
        current = player.getBounds();
    }

    for (const Obstacle& obstacle : obstacles) {
        sf::FloatRect obstacleBounds = obstacle.getBounds();

        if (!current.intersects(obstacleBounds)) {
            continue;
        }

        if (obstacle.getType() == ObstacleType::Spike) {
            player.die();
            return;
        }

        if (obstacle.getType() == ObstacleType::Finish) {
            levelComplete = true;
            return;
        }

        const float platformTop = obstacleBounds.top;
        const bool cameFromAbove = previousBottom <= platformTop + 8.f;

        if (cameFromAbove) {
            player.landOn(platformTop);
            landed = true;
            current = player.getBounds();
        } else {
            player.die();
            return;
        }
    }

    if (!landed && current.top > 700.f) {
        player.die();
    }
}

void Game::updateCamera() {
    float desiredX = player.getPosition().x + 300.f;
    desiredX = std::max(500.f, std::min(desiredX, levelLength - 500.f));

    camera.setCenter(desiredX, 300.f);
}
