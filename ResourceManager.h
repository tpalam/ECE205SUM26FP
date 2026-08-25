#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager {
private:
    sf::Font font;

    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer deathBuffer;

    sf::Sound jumpSound;
    sf::Sound deathSound;

    sf::Music music;

    ResourceManager();

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& getInstance();

    bool loadResources();

    sf::Font& getFont();
    sf::Sound& getJumpSound();
    sf::Sound& getDeathSound();
    sf::Music& getMusic();
};

#endif
