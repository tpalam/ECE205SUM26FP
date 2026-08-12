#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Platform.h"
#include "Spike.h"

class ObjectFactory {
public:
    static Platform createPlatform(
        float x,
        float y,
        float width,
        float height
    );

    static Spike createSpike(
        float x,
        float groundTop
    );
};

#endif