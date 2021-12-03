#pragma once

#include "game/actor/actor.h"

namespace Atlys {

class Actor : public ::Actor {
    SEAD_RTTI_OVERRIDE_IMPL(Actor, ::Actor)

public:
    Actor(const ActorBuildInfo* buildInfo)
        : ::Actor(buildInfo)
        , position(0.0f)
        , rotation(0.0f)
    { }

    sead::Vec3f position;
    sead::Vec3f rotation;
};

}
