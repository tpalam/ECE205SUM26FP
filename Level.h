#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include <vector>

#include "Platform.h"
#include "Obstacle.h"
#include "PowerUp.h"

class Level {
private:
    std::vector<Platform> platforms;

    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<PowerUp>> powerUps;
    float finishX;
    float finishGroundTop;

public:
    Level();

    bool loadFromFile(
        const std::string& filename
    );

    const std::vector<Platform>&
    getPlatforms() const;

    const std::vector<std::unique_ptr<Obstacle>>&
    getObstacles() const;

    float getFinishX() const;

    float getFinishGroundTop() const;
    const std::vector<std::unique_ptr<PowerUp>>&
        getPowerUps() const;
};

#endif