#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Platform.h"
#include "Spike.h"
#include "FinishLine.h"

enum class GameState {
    Playing,
    Dead,
    Complete
};

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;
    sf::Clock clock;

    Player player;

    std::vector<Platform> platforms;
    std::vector<Spike> spikes;

    FinishLine finishLine;

    GameState state;

    void processEvents();
    void update(float deltaTime);

    void handlePlatformCollisions();
    void handleSpikeCollisions();
    void handleFinishCollision();

    void updateCamera();
    void render();

public:
    Game();

    void run();
};

#endif