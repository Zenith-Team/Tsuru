#pragma once

#include "game/collision/solid/colliderbase.h"
#include "sead/buffer.h"

class SolidOnTopCollider : public ColliderBase { // Size: 0x178
    SEAD_RTTI_OVERRIDE(SolidOnTopCollider, ColliderBase)

public:
    struct Info {
        Vec2f distToCenter;
        f32 _8;
        f32 _C;
        Vec2f* points;
        u32 rotation;
    };

public:
    SolidOnTopCollider();
    SolidOnTopCollider(s32 numPoints, Vec2f* points, Node* nodes1, Node* nodes2);
    virtual ~SolidOnTopCollider();

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
    void init(StageActor* owner, const Info& info, s32 numPoints, sead::Heap* heap = nullptr);

    sead::Buffer<Vec2f> points;
    sead::Buffer<Node> nodes1;
    sead::Buffer<Node> nodes2;
    f32 _170;
    u8  _174[0x4];
};
