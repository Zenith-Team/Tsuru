#pragma once

#include "game/actor/baseactor.h"

class CourseSelectActorBase : public BaseActor {
    SEAD_RTTI_OVERRIDE(CourseSelectActorBase, BaseActor)

public:
    CourseSelectActorBase(const ActorBuildInfo* buildInfo);
    virtual ~CourseSelectActorBase();

    u32 beforeExecute() override;
    u32 beforeDraw() override;

    Vec3f mPosition;
    Vec3f mPosition2;
    Vec3f _68;
    Vec3f _74;
    Vec3f mScale;
    Vec3f _8C;
    Vec3f _98;
    Vec3f _A4;
    u32 _B0;
    u32 mRotation;
    u32 _B8;
    u32 _BC;
    u32 mRotation2;
    u32 _C4;
    f32 _C8;
    f32 _CC;
    f32 _D0;
    f32 _D4;
    bool _D8;
};
