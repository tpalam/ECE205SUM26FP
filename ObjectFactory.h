#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>

#include "Obstacle.h"
#include "Spike.h"
#include "SawBlade.h"
#include "Platform.h"

class ObjectFactory {
public:
    static std::unique_ptr<Obstacle> createSpike(
        float x,
        float groundTop
    );

    static std::unique_ptr<Obstacle> createSawBlade(
        float x,
        float y,
        float radius,
        SawBladeStyle style
    );

    static Platform createPlatform(
        float x,
        float y,
        float width,
        float height
    );
};

#endif