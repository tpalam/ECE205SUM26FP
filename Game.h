#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Background.h"
#include "Button.h"
#include "FinishLine.h"
#include "Level.h"
#include "Player.h"
#include "ResourceManager.h"

enum class GameState {
    MainMenu,
    LevelSelect,
    LevelEditor,
    Playing,
    Paused,
    Dead,
    Complete
};

enum class EditorTool {
    Platform,
    Spike,
    SpikedSaw,
    GearSaw,
    SpeedBoost,
    SlowDown
};

struct EditorObject {
    std::string type;
    float x = 0.f;
    float y = 0.f;
    float width = 0.f;
    float height = 0.f;
    float radius = 0.f;
    std::string style;
};

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;
    sf::View editorCamera;
    sf::Clock clock;

    Player player;
    Level level;
    FinishLine finishLine;
    GameState state;
    Background background;

    sf::RectangleShape progressBackground;
    sf::RectangleShape progressBar;
    sf::Text statusText;
    sf::Text coordinateText;
    sf::Text screenTitle;
    sf::Text editorInstructions;
    sf::Text editorStatus;

    std::vector<Button> mainMenuButtons;
    std::vector<Button> levelSelectButtons;

    EditorTool currentTool;
    std::vector<EditorObject> editorObjects;

    void processEvents();
    void processMainMenuEvent(const sf::Event& event);
    void processLevelSelectEvent(const sf::Event& event);
    void processEditorEvent(const sf::Event& event);
    void processGameplayEvent(const sf::Event& event);
    void update(float deltaTime);
    void updateButtonHover();

    bool loadLevel(const std::string& filename);
    void resetAttempt();

    void handlePlatformCollisions();
    void handleObstacleCollisions();
    void handlePowerUpCollisions();
    void handleFinishCollision();
    void updateCamera();
    void updateProgressBar();

    void placeEditorObject(sf::Vector2f worldPosition);
    void deleteEditorObject(sf::Vector2f worldPosition);
    bool saveCustomLevel();
    void updateEditorToolText();

    void render();
    void renderMainMenu();
    void renderLevelSelect();
    void renderEditor();
    void renderGameplay();
    void drawEditorObject(const EditorObject& object);
    void centerText(sf::Text& text, float x, float y);
    void centerStatusText();

public:
    Game();
    void run();
};

#endif
