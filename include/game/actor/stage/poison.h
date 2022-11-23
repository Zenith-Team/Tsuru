#pragma once

#include "game/actor/stage/envterrain.h"

class Poison : public EnvTerrain {
    SEAD_RTTI_OVERRIDE(Poison, EnvTerrain);

public:
    Poison(const ActorBuildInfo* buildInfo);

    // TODO
};
