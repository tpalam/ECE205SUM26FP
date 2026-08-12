#include "Game.h"

#include <iostream>

Game::Game()
    : window(
          sf::VideoMode(1000, 600),
          "Geometry Dash"
      ),
      camera(
          sf::FloatRect(0.f, 0.f, 1000.f, 600.f)
      ),
      finishLine(
          2700.f,
          500.f
      ),
      state(
          GameState::Start
      ) {

    window.setFramerateLimit(60);
    
    // Load the level from JSON.
    if (!level.loadFromFile("level.json")) {
        std::cout << "Failed to load level.\n";
    }

    // Move the finish line to the location stored in level.json.
    finishLine = FinishLine(
        level.getFinishX(),
        level.getFinishGroundTop()
    );

    // Set up progress bar background.
    progressBackground.setSize(
        sf::Vector2f(700.f, 14.f)
    );

    progressBackground.setPosition( 150.f, 25.f);

    progressBackground.setFillColor(
        sf::Color(70, 70, 90)
    );

    // Set up actual progress bar.
    progressBar.setSize(
        sf::Vector2f(0.f, 14.f)
    );

    progressBar.setPosition(
        150.f,
        25.f
    );

    progressBar.setFillColor(
        sf::Color::Cyan
    );

    // Load font.
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Failed to load font.\n";
    }

    // Set up status text.
    statusText.setFont(font);

    statusText.setCharacterSize(40);

    statusText.setFillColor(
        sf::Color::White
    );


    statusText.setString(
        "PRESS SPACE TO START"
    );

    centerStatusText();

    if (!jumpBuffer.loadFromFile("assets/jump.wav")) {
        std::cout << "Failed to load jump sound.\n";
    }
    
    if (!deathBuffer.loadFromFile("assets/death.wav")) {
        std::cout << "Failed to load death sound.\n";
    }
    
    jumpSound.setBuffer(jumpBuffer);
    deathSound.setBuffer(deathBuffer);
    
    if (!music.openFromFile("assets/music.ogg")) {
        std::cout << "Failed to load music.\n";
    }
    else {
        music.setLoop(true);
    }
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

            state = GameState::Playing;
            music.play();

            camera.setCenter(
                500.f,
                300.f
            );

            progressBar.setSize(
                sf::Vector2f(
                    0.f,
                    14.f
                )
            );

            progressBar.setFillColor(
                sf::Color::Cyan
            );
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space) {
        
            if (state == GameState::Start) {
        
                state = GameState::Playing;
        
                clock.restart();
        
                music.play();
            }
        
            else if (state == GameState::Playing) {
        
                if (player.jump()) {
                    jumpSound.play();
                }
            }
        }
        }
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::P) {
        
            if (state == GameState::Playing) {
                state = GameState::Paused;
        
                statusText.setString(
                    "PAUSED - PRESS P TO RESUME"
                );
                centerStatusText();
                music.pause();
            }
        
            else if (state == GameState::Paused) {
                state = GameState::Playing;
                clock.restart();
                music.play();
            }
        }
    }

void Game::update(float deltaTime) {
    if (state == GameState::Playing) {

        player.update(deltaTime);

        handlePlatformCollisions();

        handleSpikeCollisions();

        handleFinishCollision();

        updateCamera();

        updateProgressBar();
    }
}

void Game::handlePlatformCollisions() {
    sf::FloatRect currentBounds =
        player.getBounds();

    sf::FloatRect previousBounds =
        player.getPreviousBounds();

    const std::vector<Platform>& platforms =
        level.getPlatforms();

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

                player.landOn(
                    platformTop
                );

                currentBounds =
                    player.getBounds();
            }
        }
    }
}

void Game::handleSpikeCollisions() {
    const std::vector<Spike>& spikes =
        level.getSpikes();

    for (const Spike& spike : spikes) {

        if (player.getBounds().intersects(
                spike.getBounds())) {

            player.die();
            deathSound.play();

            state =
                GameState::Dead;

            statusText.setString(
                "YOU DIED - PRESS R"
            );
            centerStatusText();
            break;
        }
    }
}

void Game::handleFinishCollision() {
    if (player.getBounds().intersects(
            finishLine.getBounds())) {

        state =
            GameState::Complete;

        progressBar.setSize(
            sf::Vector2f(
                700.f,
                14.f
            )
        );

        progressBar.setFillColor(
            sf::Color::Green
        );

        statusText.setString(
            "LEVEL COMPLETE - PRESS R"
        );
        centerStatusText();
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

void Game::updateProgressBar() {
    float playerX =
        player.getPosition().x;

    float finishX =
        level.getFinishX();

    float progress =
        playerX / finishX;

    if (progress < 0.f) {
        progress = 0.f;
    }

    if (progress > 1.f) {
        progress = 1.f;
    }

    progressBar.setSize(
        sf::Vector2f(
            700.f * progress,
            14.f
        )
    );
}

void Game::centerStatusText() {
    sf::FloatRect bounds =
        statusText.getLocalBounds();

    statusText.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    statusText.setPosition(
        500.f,
        300.f
    );
}

void Game::render() {
    window.clear(
        sf::Color(25, 25, 40)
    );

    // Draw parallax background first.
    background.draw(
        window,
        camera
    );

    // Switch back to the normal game camera.
    window.setView(camera);

    const std::vector<Platform>& platforms =
        level.getPlatforms();

    for (const Platform& platform : platforms) {
        platform.draw(window);
    }

    const std::vector<Spike>& spikes =
        level.getSpikes();

    for (const Spike& spike : spikes) {
        spike.draw(window);
    }

    finishLine.draw(window);

    player.draw(window);

    // Switch to fixed screen coordinates for UI.
    window.setView(
        window.getDefaultView()
    );

    window.draw(
        progressBackground
    );

    window.draw(
        progressBar
    );

    if (state == GameState::Start ||
        state == GameState::Paused ||
        state == GameState::Dead ||
        state == GameState::Complete) {
    
        window.draw(statusText);
    }

    window.display();
}


