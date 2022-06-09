#pragma once

#include "game/actor/stage/envterrain.h"

class Water : public EnvTerrain {
    SEAD_RTTI_OVERRIDE(Water, EnvTerrain);

public:
    // TODO

    static Actor* build(const ActorBuildInfo* info);
};
