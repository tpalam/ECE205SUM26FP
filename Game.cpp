#include "Game.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {
constexpr float WINDOW_WIDTH = 1000.f;
constexpr float WINDOW_HEIGHT = 600.f;
constexpr float GRID_SIZE = 50.f;
constexpr float GROUND_TOP = 500.f;
constexpr float MIN_LEVEL_LENGTH = 3000.f;
}

Game::Game()
    : window(sf::VideoMode(1000, 600), "Geometry Dash"),
      camera(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT)),
      editorCamera(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT)),
      finishLine(MIN_LEVEL_LENGTH, GROUND_TOP),
      state(GameState::MainMenu),
      currentTool(EditorTool::Platform) {
    window.setFramerateLimit(60);

    ResourceManager& resources = ResourceManager::getInstance();
    resources.loadResources();
    const sf::Font& font = resources.getFont();

    progressBackground.setSize(sf::Vector2f(700.f, 14.f));
    progressBackground.setPosition(150.f, 25.f);
    progressBackground.setFillColor(sf::Color(70, 70, 90));

    progressBar.setSize(sf::Vector2f(0.f, 14.f));
    progressBar.setPosition(150.f, 25.f);
    progressBar.setFillColor(sf::Color::Cyan);

    statusText.setFont(font);
    statusText.setCharacterSize(40);
    statusText.setFillColor(sf::Color::White);

    coordinateText.setFont(font);
    coordinateText.setCharacterSize(20);
    coordinateText.setFillColor(sf::Color::White);
    coordinateText.setPosition(800.f, 20.f);

    screenTitle.setFont(font);
    screenTitle.setCharacterSize(54);
    screenTitle.setFillColor(sf::Color::White);

    editorInstructions.setFont(font);
    editorInstructions.setCharacterSize(17);
    editorInstructions.setFillColor(sf::Color::White);
    editorInstructions.setPosition(20.f, 12.f);
    editorInstructions.setString(
        "1 Platform  2 Spike  3 Spiked Saw  4 Gear Saw  "
        "5 Speed  6 Slow\nLeft click: place   Right click: delete   "
        "Arrows: scroll   S: save   Esc: menu"
    );

    editorStatus.setFont(font);
    editorStatus.setCharacterSize(20);
    editorStatus.setFillColor(sf::Color::Cyan);
    editorStatus.setPosition(20.f, 555.f);

    mainMenuButtons.emplace_back(
        font, "PLAY", sf::Vector2f(350.f, 215.f), sf::Vector2f(300.f, 70.f)
    );
    mainMenuButtons.emplace_back(
        font, "LEVEL EDITOR", sf::Vector2f(350.f, 315.f), sf::Vector2f(300.f, 70.f)
    );
    mainMenuButtons.emplace_back(
        font, "QUIT", sf::Vector2f(350.f, 415.f), sf::Vector2f(300.f, 70.f)
    );

    levelSelectButtons.emplace_back(
        font, "LEVEL 1", sf::Vector2f(325.f, 200.f), sf::Vector2f(350.f, 70.f)
    );
    levelSelectButtons.emplace_back(
        font, "CUSTOM LEVEL", sf::Vector2f(325.f, 300.f), sf::Vector2f(350.f, 70.f)
    );
    levelSelectButtons.emplace_back(
        font, "BACK", sf::Vector2f(325.f, 420.f), sf::Vector2f(350.f, 60.f)
    );

    editorCamera.setCenter(500.f, 300.f);
    updateEditorToolText();
}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
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
            continue;
        }

        if (state == GameState::MainMenu) {
            processMainMenuEvent(event);
        }
        else if (state == GameState::LevelSelect) {
            processLevelSelectEvent(event);
        }
        else if (state == GameState::LevelEditor) {
            processEditorEvent(event);
        }
        else {
            processGameplayEvent(event);
        }
    }
}

void Game::processMainMenuEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed ||
        event.mouseButton.button != sf::Mouse::Left) {
        return;
    }

    sf::Vector2f mouse(
        static_cast<float>(event.mouseButton.x),
        static_cast<float>(event.mouseButton.y)
    );

    if (mainMenuButtons[0].contains(mouse)) {
        state = GameState::LevelSelect;
    }
    else if (mainMenuButtons[1].contains(mouse)) {
        state = GameState::LevelEditor;
        editorCamera.setCenter(500.f, 300.f);
        editorStatus.setString("Ready to build");
    }
    else if (mainMenuButtons[2].contains(mouse)) {
        window.close();
    }
}

void Game::processLevelSelectEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        state = GameState::MainMenu;
        return;
    }

    if (event.type != sf::Event::MouseButtonPressed ||
        event.mouseButton.button != sf::Mouse::Left) {
        return;
    }

    sf::Vector2f mouse(
        static_cast<float>(event.mouseButton.x),
        static_cast<float>(event.mouseButton.y)
    );

    if (levelSelectButtons[0].contains(mouse)) {
        loadLevel("level.json");
    }
    else if (levelSelectButtons[1].contains(mouse)) {
        if (!loadLevel("custom_level.json")) {
            statusText.setString("NO CUSTOM LEVEL - CREATE ONE FIRST");
            centerStatusText();
        }
    }
    else if (levelSelectButtons[2].contains(mouse)) {
        state = GameState::MainMenu;
    }
}

void Game::processEditorEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            currentTool = EditorTool::Platform;
        }
        else if (event.key.code == sf::Keyboard::Num2) {
            currentTool = EditorTool::Spike;
        }
        else if (event.key.code == sf::Keyboard::Num3) {
            currentTool = EditorTool::SpikedSaw;
        }
        else if (event.key.code == sf::Keyboard::Num4) {
            currentTool = EditorTool::GearSaw;
        }
        else if (event.key.code == sf::Keyboard::Num5) {
            currentTool = EditorTool::SpeedBoost;
        }
        else if (event.key.code == sf::Keyboard::Num6) {
            currentTool = EditorTool::SlowDown;
        }
        else if (event.key.code == sf::Keyboard::Left) {
            editorCamera.move(-200.f, 0.f);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            editorCamera.move(200.f, 0.f);
        }
        else if (event.key.code == sf::Keyboard::Up) {
            editorCamera.move(0.f, -100.f);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            editorCamera.move(0.f, 100.f);
        }
        else if (event.key.code == sf::Keyboard::S) {
            if (saveCustomLevel()) {
                editorStatus.setString("Saved custom_level.json - open it from PLAY");
            }
            else {
                editorStatus.setString("Could not save custom level");
            }
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            state = GameState::MainMenu;
            return;
        }

        updateEditorToolText();
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.y > 90) {
        sf::Vector2i pixel(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f worldPosition =
            window.mapPixelToCoords(pixel, editorCamera);

        if (event.mouseButton.button == sf::Mouse::Left) {
            placeEditorObject(worldPosition);
        }
        else if (event.mouseButton.button == sf::Mouse::Right) {
            deleteEditorObject(worldPosition);
        }
    }
}

void Game::processGameplayEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return;
    }

    ResourceManager& resources = ResourceManager::getInstance();

    if (event.key.code == sf::Keyboard::Escape) {
        resources.getMusic().stop();
        state = GameState::LevelSelect;
    }
    else if (event.key.code == sf::Keyboard::R &&
             (state == GameState::Dead || state == GameState::Complete)) {
        resetAttempt();
        state = GameState::Playing;
        resources.getMusic().play();
    }
    else if (event.key.code == sf::Keyboard::Space &&
             state == GameState::Playing && player.jump()) {
        resources.getJumpSound().play();
    }
    else if (event.key.code == sf::Keyboard::P) {
        if (state == GameState::Playing) {
            state = GameState::Paused;
            statusText.setString("PAUSED - P TO RESUME - ESC FOR LEVELS");
            centerStatusText();
            resources.getMusic().pause();
        }
        else if (state == GameState::Paused) {
            state = GameState::Playing;
            clock.restart();
            resources.getMusic().play();
        }
    }
}

void Game::update(float deltaTime) {
    updateButtonHover();

    if (state != GameState::Playing) {
        return;
    }

    player.update(deltaTime);

    for (const auto& obstacle : level.getObstacles()) {
        obstacle->update(deltaTime);
    }

    handlePlatformCollisions();
    handleObstacleCollisions();

    if (state != GameState::Playing) {
        return;
    }

    handlePowerUpCollisions();
    handleFinishCollision();
    updateCamera();
    updateProgressBar();

    sf::Vector2f position = player.getPosition();
    coordinateText.setString(
        "X: " + std::to_string(static_cast<int>(position.x)) +
        "  Y: " + std::to_string(static_cast<int>(position.y))
    );
}

void Game::updateButtonHover() {
    sf::Vector2i pixel = sf::Mouse::getPosition(window);
    sf::Vector2f mouse(static_cast<float>(pixel.x), static_cast<float>(pixel.y));

    std::vector<Button>* buttons = nullptr;
    if (state == GameState::MainMenu) {
        buttons = &mainMenuButtons;
    }
    else if (state == GameState::LevelSelect) {
        buttons = &levelSelectButtons;
    }

    if (buttons != nullptr) {
        for (Button& button : *buttons) {
            button.setHovered(button.contains(mouse));
        }
    }
}

bool Game::loadLevel(const std::string& filename) {
    if (!level.loadFromFile(filename)) {
        return false;
    }

    finishLine = FinishLine(level.getFinishX(), level.getFinishGroundTop());
    resetAttempt();
    state = GameState::Playing;
    clock.restart();
    ResourceManager::getInstance().getMusic().play();
    return true;
}

void Game::resetAttempt() {
    player.reset();

    for (const auto& powerUp : level.getPowerUps()) {
        powerUp->reset();
    }

    camera.setCenter(500.f, 300.f);
    progressBar.setSize(sf::Vector2f(0.f, 14.f));
    progressBar.setFillColor(sf::Color::Cyan);
}

void Game::handlePlatformCollisions() {
    sf::FloatRect currentBounds = player.getBounds();
    sf::FloatRect previousBounds = player.getPreviousBounds();

    for (const Platform& platform : level.getPlatforms()) {
        sf::FloatRect platformBounds = platform.getBounds();

        if (!currentBounds.intersects(platformBounds)) {
            continue;
        }

        float previousBottom = previousBounds.top + previousBounds.height;
        float currentBottom = currentBounds.top + currentBounds.height;
        float platformTop = platformBounds.top;

        if (previousBottom <= platformTop && currentBottom >= platformTop) {
            player.landOn(platformTop);
            currentBounds = player.getBounds();
        }
    }
}

void Game::handleObstacleCollisions() {
    for (const auto& obstacle : level.getObstacles()) {
        if (player.getBounds().intersects(obstacle->getBounds())) {
            player.die();
            ResourceManager::getInstance().getDeathSound().play();
            ResourceManager::getInstance().getMusic().pause();
            state = GameState::Dead;
            statusText.setString("YOU DIED - R TO RETRY - ESC FOR LEVELS");
            centerStatusText();
            return;
        }
    }
}

void Game::handlePowerUpCollisions() {
    for (const auto& powerUp : level.getPowerUps()) {
        if (!powerUp->isActive()) {
            continue;
        }

        if (player.getBounds().intersects(powerUp->getBounds())) {
            powerUp->apply(player);
            powerUp->deactivate();
        }
    }
}

void Game::handleFinishCollision() {
    if (!player.getBounds().intersects(finishLine.getBounds())) {
        return;
    }

    state = GameState::Complete;
    ResourceManager::getInstance().getMusic().pause();
    progressBar.setSize(sf::Vector2f(700.f, 14.f));
    progressBar.setFillColor(sf::Color::Green);
    statusText.setString("LEVEL COMPLETE - R TO REPLAY - ESC FOR LEVELS");
    centerStatusText();
}

void Game::updateCamera() {
    float cameraX = std::max(500.f, player.getPosition().x + 300.f);
    camera.setCenter(cameraX, 300.f);
}

void Game::updateProgressBar() {
    float finishX = level.getFinishX();
    float progress = finishX > 0.f ? player.getPosition().x / finishX : 0.f;
    progress = std::max(0.f, std::min(1.f, progress));
    progressBar.setSize(sf::Vector2f(700.f * progress, 14.f));
}

void Game::placeEditorObject(sf::Vector2f worldPosition) {
    float x = std::round(worldPosition.x / GRID_SIZE) * GRID_SIZE;
    float y = std::round(worldPosition.y / GRID_SIZE) * GRID_SIZE;
    x = std::max(0.f, x);

    EditorObject object;
    object.x = x;
    object.y = y;

    if (currentTool == EditorTool::Platform) {
        object.type = "PLATFORM";
        object.width = 150.f;
        object.height = 50.f;
    }
    else if (currentTool == EditorTool::Spike) {
        object.type = "SPIKE";
    }
    else if (currentTool == EditorTool::SpikedSaw) {
        object.type = "SAW";
        object.radius = 40.f;
        object.style = "SPIKED";
    }
    else if (currentTool == EditorTool::GearSaw) {
        object.type = "SAW";
        object.radius = 40.f;
        object.style = "GEAR";
    }
    else if (currentTool == EditorTool::SpeedBoost) {
        object.type = "POWERUP";
        object.style = "SPEED";
    }
    else {
        object.type = "POWERUP";
        object.style = "SLOW";
    }

    editorObjects.push_back(object);
    editorStatus.setString(
        "Placed object at X " + std::to_string(static_cast<int>(x)) +
        " Y " + std::to_string(static_cast<int>(y))
    );
}

void Game::deleteEditorObject(sf::Vector2f worldPosition) {
    if (editorObjects.empty()) {
        editorStatus.setString("Nothing to delete");
        return;
    }

    auto closest = std::min_element(
        editorObjects.begin(), editorObjects.end(),
        [worldPosition](const EditorObject& a, const EditorObject& b) {
            float aDistance = std::hypot(a.x - worldPosition.x, a.y - worldPosition.y);
            float bDistance = std::hypot(b.x - worldPosition.x, b.y - worldPosition.y);
            return aDistance < bDistance;
        }
    );

    if (std::hypot(closest->x - worldPosition.x, closest->y - worldPosition.y) <= 100.f) {
        editorObjects.erase(closest);
        editorStatus.setString("Deleted nearest object");
    }
    else {
        editorStatus.setString("No object close enough to delete");
    }
}

bool Game::saveCustomLevel() {
    json data;
    data["platforms"] = json::array();
    data["spikes"] = json::array();
    data["saws"] = json::array();
    data["powerUps"] = json::array();

    float farthestX = MIN_LEVEL_LENGTH - 500.f;

    for (const EditorObject& object : editorObjects) {
        farthestX = std::max(farthestX, object.x);

        if (object.type == "PLATFORM") {
            data["platforms"].push_back({
                {"x", object.x}, {"y", object.y},
                {"width", object.width}, {"height", object.height}
            });
        }
        else if (object.type == "SPIKE") {
            data["spikes"].push_back({
                {"x", object.x}, {"groundTop", object.y}
            });
        }
        else if (object.type == "SAW") {
            data["saws"].push_back({
                {"x", object.x}, {"y", object.y},
                {"radius", object.radius}, {"style", object.style}
            });
        }
        else if (object.type == "POWERUP") {
            data["powerUps"].push_back({
                {"type", object.style}, {"x", object.x},
                {"groundTop", object.y}
            });
        }
    }

    float finishX = std::max(MIN_LEVEL_LENGTH, farthestX + 500.f);

    data["platforms"].insert(
        data["platforms"].begin(),
        {{"x", 0.f}, {"y", GROUND_TOP}, {"width", finishX}, {"height", 100.f}}
    );
    data["finish"] = {{"x", finishX}, {"groundTop", GROUND_TOP}};

    std::ofstream file("custom_level.json");
    if (!file.is_open()) {
        return false;
    }

    file << data.dump(4);
    return file.good();
}

void Game::updateEditorToolText() {
    std::string toolName;

    switch (currentTool) {
        case EditorTool::Platform: toolName = "Platform"; break;
        case EditorTool::Spike: toolName = "Spike"; break;
        case EditorTool::SpikedSaw: toolName = "Spiked Saw"; break;
        case EditorTool::GearSaw: toolName = "Gear Saw"; break;
        case EditorTool::SpeedBoost: toolName = "Speed Boost"; break;
        case EditorTool::SlowDown: toolName = "Slow Down"; break;
    }

    editorStatus.setString("Selected: " + toolName);
}

void Game::render() {
    window.clear(sf::Color(25, 25, 40));

    if (state == GameState::MainMenu) {
        renderMainMenu();
    }
    else if (state == GameState::LevelSelect) {
        renderLevelSelect();
    }
    else if (state == GameState::LevelEditor) {
        renderEditor();
    }
    else {
        renderGameplay();
    }

    window.display();
}

void Game::renderMainMenu() {
    window.setView(window.getDefaultView());
    screenTitle.setString("GEOMETRY DASH");
    centerText(screenTitle, 500.f, 115.f);
    window.draw(screenTitle);

    for (const Button& button : mainMenuButtons) {
        button.draw(window);
    }
}

void Game::renderLevelSelect() {
    window.setView(window.getDefaultView());
    screenTitle.setString("SELECT A LEVEL");
    centerText(screenTitle, 500.f, 110.f);
    window.draw(screenTitle);

    for (const Button& button : levelSelectButtons) {
        button.draw(window);
    }

    if (statusText.getString() == "NO CUSTOM LEVEL - CREATE ONE FIRST") {
        window.draw(statusText);
    }
}

void Game::renderEditor() {
    window.setView(editorCamera);

    sf::Vector2f center = editorCamera.getCenter();
    float left = center.x - WINDOW_WIDTH / 2.f;
    float right = center.x + WINDOW_WIDTH / 2.f;
    float top = center.y - WINDOW_HEIGHT / 2.f;
    float bottom = center.y + WINDOW_HEIGHT / 2.f;

    sf::VertexArray grid(sf::Lines);
    float firstX = std::floor(left / GRID_SIZE) * GRID_SIZE;
    float firstY = std::floor(top / GRID_SIZE) * GRID_SIZE;

    for (float x = firstX; x <= right; x += GRID_SIZE) {
        grid.append(sf::Vertex(sf::Vector2f(x, top), sf::Color(55, 55, 80)));
        grid.append(sf::Vertex(sf::Vector2f(x, bottom), sf::Color(55, 55, 80)));
    }
    for (float y = firstY; y <= bottom; y += GRID_SIZE) {
        grid.append(sf::Vertex(sf::Vector2f(left, y), sf::Color(55, 55, 80)));
        grid.append(sf::Vertex(sf::Vector2f(right, y), sf::Color(55, 55, 80)));
    }
    window.draw(grid);

    sf::RectangleShape groundLine(sf::Vector2f(20000.f, 4.f));
    groundLine.setPosition(0.f, GROUND_TOP);
    groundLine.setFillColor(sf::Color(110, 110, 130));
    window.draw(groundLine);

    for (const EditorObject& object : editorObjects) {
        drawEditorObject(object);
    }

    window.setView(window.getDefaultView());
    sf::RectangleShape toolbar(sf::Vector2f(WINDOW_WIDTH, 90.f));
    toolbar.setFillColor(sf::Color(15, 20, 40, 245));
    window.draw(toolbar);
    window.draw(editorInstructions);
    window.draw(editorStatus);
}

void Game::drawEditorObject(const EditorObject& object) {
    if (object.type == "PLATFORM") {
        sf::RectangleShape shape(sf::Vector2f(object.width, object.height));
        shape.setPosition(object.x, object.y);
        shape.setFillColor(sf::Color(110, 110, 120));
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color::White);
        window.draw(shape);
    }
    else if (object.type == "SPIKE") {
        sf::ConvexShape shape(3);
        shape.setPoint(0, sf::Vector2f(0.f, 50.f));
        shape.setPoint(1, sf::Vector2f(25.f, 0.f));
        shape.setPoint(2, sf::Vector2f(50.f, 50.f));
        shape.setPosition(object.x, object.y - 50.f);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
    }
    else if (object.type == "SAW") {
        sf::CircleShape shape(object.radius, object.style == "GEAR" ? 12 : 18);
        shape.setOrigin(object.radius, object.radius);
        shape.setPosition(object.x, object.y);
        shape.setFillColor(sf::Color(40, 90, 180));
        shape.setOutlineThickness(4.f);
        shape.setOutlineColor(sf::Color::White);
        window.draw(shape);
    }
    else {
        sf::RectangleShape shape(sf::Vector2f(65.f, 65.f));
        shape.setPosition(object.x, object.y - 65.f);
        shape.setFillColor(
            object.style == "SPEED"
                ? sf::Color(40, 230, 40)
                : sf::Color(255, 190, 30)
        );
        shape.setOutlineThickness(3.f);
        shape.setOutlineColor(sf::Color::White);
        window.draw(shape);
    }
}

void Game::renderGameplay() {
    background.draw(window, camera);
    window.setView(camera);

    for (const Platform& platform : level.getPlatforms()) {
        platform.draw(window);
    }
    for (const auto& obstacle : level.getObstacles()) {
        obstacle->draw(window);
    }
    for (const auto& powerUp : level.getPowerUps()) {
        powerUp->draw(window);
    }

    finishLine.draw(window);
    player.draw(window);

    window.setView(window.getDefaultView());
    window.draw(progressBackground);
    window.draw(progressBar);
    window.draw(coordinateText);

    if (state == GameState::Paused ||
        state == GameState::Dead ||
        state == GameState::Complete) {
        window.draw(statusText);
    }
}

void Game::centerText(sf::Text& text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );
    text.setPosition(x, y);
}

void Game::centerStatusText() {
    centerText(statusText, 500.f, 300.f);
}
