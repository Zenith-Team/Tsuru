#pragma once

#include "game/collision/solid/colliderbase.h"

class ShapedCollider : public ColliderBase {
    SEAD_RTTI_OVERRIDE(ShapedCollider, ColliderBase)

public:
    struct Info {
        Vec2f mDistToCenter;    // _0
        f32 _8;                 // _8
        f32 _C;                 // _C
        Vec2f mTopLeft;         // _10
        Vec2f mBottomRight;     // _18
        u32 mRotation;          // _20
    };

public:
    ShapedCollider();
    ShapedCollider(s32 numPoints, Vec2f* points, Node* nodes1, Node* nodes2);
    virtual ~ShapedCollider();

    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, Vec2f*, Vec2f*, u8) override;
    bool vf4C(Node2*, Vec2f*, Vec2f*, s32 sensorID, PhysicsMgr* physicsMgr) override;
    bool vf54(u8*, Vec2f*) override;
    bool vf5C(u32*) override; // deleted
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(Vec2f*, f32) override;

    virtual void vf84();

    void init(StageActor* owner, const Info& info);
    void setRect(Vec2f* topLeft, Vec2f* bottomRight);

    sead::Buffer<Vec2f> mPoints;
    sead::Buffer<Node> mNodes1;
    sead::Buffer<Node> mNodes2;
};
