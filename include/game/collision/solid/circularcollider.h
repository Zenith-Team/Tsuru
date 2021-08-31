#pragma once

#include <game/collision/solid/colliderbase.h>

class CircularCollider : public ColliderBase {
    SEAD_RTTI_OVERRIDE(CircularCollider, ColliderBase)

public:
    struct Info {
        Vec2f mDistToCenter;
        Vec2f _8;
        Vec2f _10;
        f32 mRadius;
        u32 mRotation;
    };

public:
    CircularCollider();
    virtual ~CircularCollider();

    bool vf24(u32*, u32) override;
    u32 vf2C(u32*) override;
    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, Vec2f*, Vec2f*, u8) override;
    bool vf4C(Node2*, Vec2f*, Vec2f*, s32 sensorID, PhysicsMgr* physicsMgr) override;
    bool vf54(u8*, Vec2f*) override;
    bool vf5C(u32*) override;
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(Vec2f*, f32) override;

    void init(StageActor* owner, const Info& info);

    Vec2f _158;
    Vec2f _160;
    Vec2f _168;
    f32 mRadius;
    u8 _174[0x190-0x174];
};
