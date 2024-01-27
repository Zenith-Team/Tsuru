#pragma once

#include "game/actor/actor.h"

namespace crt {

    // Base class for all actors present in the worldmap
    class MapActor : public Actor {
        SEAD_RTTI_OVERRIDE_IMPL(MapActor, Actor);

    public:
        MapActor(const ActorBuildInfo* buildInfo)
            : Actor(buildInfo)
            , position(0.0f, 0.0f, 0.0f)
            , rotation(0, 0, 0)
            , scale(1.0f, 1.0f, 1.0f)
        { }

        u32 onCreate() override { return 1; }
        u32 onExecute() override { return 1; }
        u32 onDraw() override { return 1; }

        Vec3f position;
        Vec3u rotation;
        Vec3f scale;
    };

}
