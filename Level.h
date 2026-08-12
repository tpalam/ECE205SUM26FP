#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Platform.h"
#include "Spike.h"

class Level {
private:
    std::vector<Platform> platforms;
    std::vector<Spike> spikes;

    float finishX;
    float finishGroundTop;

public:
    Level();

    bool loadFromFile(const std::string& filename);

    const std::vector<Platform>& getPlatforms() const;
    const std::vector<Spike>& getSpikes() const;

    float getFinishX() const;
    float getFinishGroundTop() const;
};

#endif