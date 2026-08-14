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

std::unique_ptr<Obstacle>
ObjectFactory::createSpike(
    float x,
    float groundTop
) {
    return std::make_unique<Spike>(
        x,
        groundTop
    );
}

std::unique_ptr<Obstacle>
ObjectFactory::createSawBlade(
    float x,
    float y,
    float radius,
    SawBladeStyle style
) {
    return std::make_unique<SawBlade>(
        x,
        y,
        radius,
        style
    );
}
std::unique_ptr<PowerUp>
ObjectFactory::createSpeedBoost(
    float x,
    float groundTop
) {
    return std::make_unique<SpeedBoost>(
        x,
        groundTop
    );
}

std::unique_ptr<PowerUp>
ObjectFactory::createSlowDown(
    float x,
    float groundTop
) {
    return std::make_unique<SlowDown>(
        x,
        groundTop
    );
}