#pragma once

#include "tsuru/atlys/actor.h"
#include "sead/camera.h"
#include "sead/projection.h"

namespace Atlys {

class Camera : public Atlys::Actor {
    SEAD_RTTI_OVERRIDE_IMPL(Camera, Atlys::Actor)

public:
    Camera(const ActorBuildInfo* buildInfo);
    virtual ~Camera() { }

    static ::Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    sead::LookAtCamera camera;
    sead::PerspectiveProjection projection;
    Mtx34 modelMtx, scaleMtx;
};

}
