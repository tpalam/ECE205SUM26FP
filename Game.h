#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Level.h"
#include "FinishLine.h"
#include "Background.h"

enum class GameState {
    Start,
    Playing,
    Paused,
    Dead,
    Complete
};

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;
    sf::Clock clock;

    Player player;
    Level level;
    FinishLine finishLine;

    GameState state;

    Background background;

    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer deathBuffer;

    sf::Sound jumpSound;
    sf::Sound deathSound;

    sf::Music music;

    sf::RectangleShape progressBackground;
    sf::RectangleShape progressBar;

    sf::Font font;
    sf::Text statusText;
        sf::Text coordinateText;

    void processEvents();
    void update(float deltaTime);

    void handlePlatformCollisions();
    void handleObstacleCollisions();
    void handleFinishCollision();

    void updateCamera();
    void updateProgressBar();
    void render();
    void centerStatusText();

    void handlePowerUpCollisions();

public:
    Game();

    void run();
};

#endif
