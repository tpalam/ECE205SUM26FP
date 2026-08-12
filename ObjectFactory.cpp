#include "ObjectFactory.h"

Platform ObjectFactory::createPlatform(
    float x,
    float y,
    float width,
    float height
) {
    return Platform(
        x,
        y,
        width,
        height
    );
}

Spike ObjectFactory::createSpike(
    float x,
    float groundTop
) {
    return Spike(
        x,
        groundTop
    );
}