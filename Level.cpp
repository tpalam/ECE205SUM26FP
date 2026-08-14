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
    obstacles.clear();
    powerUps.clear();

    // Load platforms.
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

    // Load spikes.
    for (const auto& spikeData : data["spikes"]) {
        float x =
            spikeData["x"];

        float groundTop =
            spikeData["groundTop"];

        obstacles.push_back(
            ObjectFactory::createSpike(
                x,
                groundTop
            )
        );
    }
    //powerup load
    for (const auto& powerUpData : data["powerUps"]) {
        std::string type =
            powerUpData["type"];
    
        float x =
            powerUpData["x"];
    
        float groundTop =
            powerUpData["groundTop"];
    
        if (type == "SPEED") {
            powerUps.push_back(
                ObjectFactory::createSpeedBoost(
                    x,
                    groundTop
                )
            );
        }
    
        else if (type == "SLOW") {
            powerUps.push_back(
                ObjectFactory::createSlowDown(
                    x,
                    groundTop
                )
            );
        }
    }
    // Load saw blades.
    for (const auto& sawData : data["saws"]) {
        float x =
            sawData["x"];

        float y =
            sawData["y"];

        float radius =
            sawData["radius"];

        std::string styleString =
            sawData["style"];

        SawBladeStyle style;

        if (styleString == "GEAR") {
            style = SawBladeStyle::Gear;
        }
        else {
            style = SawBladeStyle::Spiked;
        }

        obstacles.push_back(
            ObjectFactory::createSawBlade(
                x,
                y,
                radius,
                style
            )
        );
    }

    // Load finish line data.
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

const std::vector<std::unique_ptr<Obstacle>>&
Level::getObstacles() const {
    return obstacles;
}

float Level::getFinishX() const {
    return finishX;
}

float Level::getFinishGroundTop() const {
    return finishGroundTop;
}

const std::vector<std::unique_ptr<PowerUp>>&
Level::getPowerUps() const {
    return powerUps;
}


