#pragma once

#include "game/actor/stage/envterrain.h"

class Quicksand : public EnvTerrain {
    SEAD_RTTI_OVERRIDE_DECL(Quicksand, EnvTerrain);

public:
    Quicksand(const ActorBuildInfo* buildInfo);

    // TODO
};
