#include "ResourceManager.h"

#include <iostream>

ResourceManager::ResourceManager() {
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;

    return instance;
}

bool ResourceManager::loadResources() {
    bool success = true;

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Failed to load font.\n";
        success = false;
    }

    if (!jumpBuffer.loadFromFile("assets/jump.wav")) {
        std::cout << "Failed to load jump sound.\n";
        success = false;
    }

    if (!deathBuffer.loadFromFile("assets/death.wav")) {
        std::cout << "Failed to load death sound.\n";
        success = false;
    }

    jumpSound.setBuffer(jumpBuffer);
    deathSound.setBuffer(deathBuffer);

    if (!music.openFromFile("assets/music.ogg")) {
        std::cout << "Failed to load music.\n";
        success = false;
    }
    else {
        music.setLoop(true);
    }

    return success;
}

sf::Font& ResourceManager::getFont() {
    return font;
}

sf::Sound& ResourceManager::getJumpSound() {
    return jumpSound;
}

sf::Sound& ResourceManager::getDeathSound() {
    return deathSound;
}

sf::Music& ResourceManager::getMusic() {
    return music;
}
