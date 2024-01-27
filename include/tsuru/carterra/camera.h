#pragma once

#include "tsuru/carterra/mapactor.h"
#include "sead/camera.h"
#include "sead/projection.h"
#include "game/graphics/model/modelnw.h"

namespace crt {

    class Camera : public MapActor {
        SEAD_RTTI_OVERRIDE_IMPL(Camera, MapActor);
    
    public:
        Camera(const ActorBuildInfo* buildInfo);
        virtual ~Camera() { }

        u32 onExecute() override;

        sead::LookAtCamera camera;
        sead::PerspectiveProjection projection;

        Vec3f targetPos, targetAt;
    };

}
