#pragma once

#include "game/actor/actor.h"

class CourseSelectActorBase : public Actor {
    SEAD_RTTI_OVERRIDE(CourseSelectActor, Actor)

public:
    CourseSelectActorBase(const ActorBuildInfo* buildInfo);
    virtual ~CourseSelectActorBase();

    u32 beforeExecute() override;
    u32 beforeDraw() override;

    Vec3f position;     // Inited to buildInfo->position
    Vec3f position2;    // Inited to buildInfo->position
    Vec3f _68;          // Inited to 0.0, 0.0, 0.0
    Vec3f _74;          // Inited to 0.0, 0.0, 0.0
    Vec3f scale;        // Inited to 1.0, 1.0, 1.0
    Vec3f _8C;
    Vec3f _98;
    Vec3f _A4;
    u32 _B0;            // Inited to 0
    u32 rotation;       // Inited to buildInfo->rotation
    u32 _B8;            // Inited to 0
    u32 _BC;            // Inited to 0
    u32 rotation2;      // Inited to buildInfo->rotation
    u32 _C4;            // Inited to 0
    f32 _C8;            // Inited to 0.0
    f32 _CC;            // Inited to -7.0
    f32 _D0;            // Inited to -40.0
    f32 _D4;            // Inited to 0.0
    bool _D8;           // Inited to false
};
