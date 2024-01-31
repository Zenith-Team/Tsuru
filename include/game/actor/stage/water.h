#pragma once

#include "game/actor/stage/envterrain.h"

class Water : public EnvTerrain {
    SEAD_RTTI_OVERRIDE_DECL(Water, EnvTerrain);

public:
    Water(const ActorBuildInfo* buildInfo);

    // TODO
};
