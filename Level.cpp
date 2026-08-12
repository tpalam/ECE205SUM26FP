#include "Level.h"
#include "ObjectFactory.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Level::Level() {
    finishX = 0.f;
    finishGroundTop = 500.f;
}

bool Level::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Could not open level file: "
                  << filename << "\n";

        return false;
    }

    json data;

    file >> data;

    platforms.clear();
    spikes.clear();

    for (const auto& platformData : data["platforms"]) {
        float x =
            platformData["x"];

        float y =
            platformData["y"];

        float width =
            platformData["width"];

        float height =
            platformData["height"];

        platforms.push_back(
            ObjectFactory::createPlatform(
                x,             
                y,
                width,
                height
            )
            );
    }

    for (const auto& spikeData : data["spikes"]) {
        float x =
            spikeData["x"];

        float groundTop =
            spikeData["groundTop"];

        spikes.push_back(
            ObjectFactory::createSpike(
                x,                    
                groundTop
            )
        );
    }

    finishX =
        data["finish"]["x"];

    finishGroundTop =
        data["finish"]["groundTop"];

    file.close();

    return true;
}

const std::vector<Platform>&
Level::getPlatforms() const {
    return platforms;
}

const std::vector<Spike>&
Level::getSpikes() const {
    return spikes;
}

float Level::getFinishX() const {
    return finishX;
}

float Level::getFinishGroundTop() const {
    return finishGroundTop;
}