#pragma once

#include "game/collision/solid/colliderbase.h"
#include "container/seadBuffer.h"

class PolygonCollider : public ColliderBase {
    SEAD_RTTI_OVERRIDE_DECL(PolygonCollider, ColliderBase);

public:
    struct Info {
        sead::Vector2f offset;          // 0
        f32 _8;                         // 8
        f32 _C;                         // C
        sead::Vector2f topLeft;         // 10
        sead::Vector2f bottomRight;     // 18
        u32 rotation;                   // 20
    };

public:
    PolygonCollider();
    PolygonCollider(s32 numPoints, sead::Vector2f* points, Node* nodes1, Node* nodes2);
    virtual ~PolygonCollider();

    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, sead::Vector2f*, sead::Vector2f*, u8) override;
    bool vf4C(Node2*, sead::Vector2f*, sead::Vector2f*, s32 sensorID, PhysicsMgr* physicsMgr) override;
    bool vf54(u8*, sead::Vector2f*) override;
    bool vf5C(u32*) override; // deleted
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(sead::Vector2f*, f32) override;

    virtual void vf84();

    void init(StageActor* owner, const Info& info);
    void setRect(sead::Vector2f* topLeft, sead::Vector2f* bottomRight);

    sead::Buffer<sead::Vector2f> points;
    sead::Buffer<Node>  nodes1;
    sead::Buffer<Node>  nodes2;
};
