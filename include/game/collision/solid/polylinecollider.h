#pragma once

#include "game/collision/solid/colliderbase.h"
#include "container/seadBuffer.h"

class PolylineCollider : public ColliderBase { // Size: 0x178
    SEAD_RTTI_OVERRIDE_DECL(PolylineCollider, ColliderBase);

public:
    struct Info {
        sead::Vector2f offset;
        f32 _8;
        f32 _C;
        sead::Vector2f* points;
        u32 rotation;
    };

public:
    PolylineCollider();
    PolylineCollider(s32 numPoints, sead::Vector2f* points, Node* nodes1, Node* nodes2);
    virtual ~PolylineCollider();

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

    void init(StageActor* owner, const Info& info, s32 numPoints, sead::Heap* heap = nullptr);

    sead::Buffer<sead::Vector2f> points;
    sead::Buffer<Node> nodes1;
    sead::Buffer<Node> nodes2;
    f32 _170;
    u8  _174[0x4];
};
