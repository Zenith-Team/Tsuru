#pragma once

#include "game/actor/stage/envterrain.h"

class Quicksand : public EnvTerrain {
    SEAD_RTTI_OVERRIDE(Quicksand, EnvTerrain);

public:
    // TODO

    static Actor* build(const ActorBuildInfo* info);
};
