#pragma once

#include "game/collision/solid/colliderbase.h"

class CircularCollider : public ColliderBase { // Size: 0x190
    SEAD_RTTI_OVERRIDE_DECL(CircularCollider, ColliderBase);

public:
    struct Info {
        sead::Vector2f offset;
        sead::Vector2f _8;
        sead::Vector2f _10;
        f32 radius;
        u32 rotation;
    };

public:
    CircularCollider();
    virtual ~CircularCollider();

    bool vf24(u32*, u32) override;
    u32  vf2C(u32*) override;
    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, sead::Vector2f*, sead::Vector2f*, u8) override;
    bool vf4C(Node2*, sead::Vector2f*, sead::Vector2f*, s32 sensorID, PhysicsMgr* physicsMgr) override;
    bool vf54(u8*, sead::Vector2f*) override;
    bool vf5C(u32*) override;
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(sead::Vector2f*, f32) override;

    void init(StageActor* owner, const Info& info);

    sead::Vector2f _158;
    sead::Vector2f _160;
    sead::Vector2f _168;
    f32 radius;
    u8 _174[0x1C];
};
