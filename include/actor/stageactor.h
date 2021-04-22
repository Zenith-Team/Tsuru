#pragma once

#include "actor.h"
#include "collisionmgr.h"

class StageActor : public Actor {  // size: 0x17A0
    SEAD_RTTI_OVERRIDE(StageActor, Actor)

public:
    StageActor(const ActorBuildInfo* buildInfo);
    virtual ~StageActor();

    void afterCreate(u32) override;
    u32 beforeExecute() override;
    void afterExecute(u32) override;
    u32 onDelete() override;

    void setPlayerId(s8 id) override;

    CollisionMgr* getCollisionMgr() override {
        return &collisionMgr;
    }

    virtual void vf10C(u8 unk) {
        _179A = unk;
    }

    virtual u8 vf114() deleted;                 // deleted

    virtual void vf11C() { }            // nullsub

    virtual void vf124(f32) { }

    virtual u32 vf12C() {
        return 0;
    }

    virtual void vf134() deleted;       // deleted
    virtual u32 vf13C();                // returns 0
    virtual void vf144(bool);           // nullsub
    virtual void vf14C(Actor*);         // nullsub

    virtual bool vf154() {
        return false;
    }

    virtual void move(Vec2& dest) {
        position.x = dest.x;
        position.y = dest.y;
    }

    virtual void setYSpeed(f32 ySpeed) {
        speed.y = ySpeed;
    }

    virtual u32 vf16C() {
        return 1;
    }

    virtual u32 vf174() {
        return 0;
    }

    virtual void getRect(Rect& rect) {
        f32 XPos1 = position.x - 16.0f;
        f32 XPos2 = position.x + 16.0f;
        f32 YPos1 = position.y;
        f32 YPos2 = position.y + 32.0f;

        if (XPos1 > XPos2) {
            rect.right = XPos1;
            rect.left = XPos2;
        }

        else {
            rect.right = XPos2;
            rect.left = XPos1;
        }

        if (YPos1 > YPos2) {
            rect.top = YPos1;
            rect.bottom = YPos2;
        }

        else {
            rect.top = YPos2;
            rect.bottom = YPos1;
        }
    }

    void handleGravity();
    void handleSpeed();

    inline bool checkForSuitableGround(f32 xOffset, f32 yOffset) {
        TileCheck::Param checkParam = { 0 };
        checkParam._2 = layer;
        checkParam._3 = collisionMask;

        TileCheck tileCheck(checkParam);

        Vec2 a(position.x, position.y);
        Vec2 b(position.x + xOffset, position.y + yOffset);

        return tileCheck.check(nullptr, a, b, 8);
    }

    u32 _27C;                           // 27C
    ActorCollisionMgr collisionMgr;     // 280
    f32 _1760;                          // 1760 Inited to 0
    f32 _1764;                          // 1764 Inited to 0
    Vec3* _1768;                        // 1768 Inited to &position
    u8 _176C;                           // 176C Inited to 0
    u32 _1770;                          // 1770 Inited to 0
    f32 _1774;                          // 1774 Inited to 1.0
    Vec2 _1778;                         // 1778 Inited to 0
    Vec2 _1780;                         // 1780 Inited to 0
    f32 maxYSpeed;                      // 1788 Inited to 1.5
    f32 minYSpeed;                      // 178C Inited to -1.5
    f32 _1790;                          // 1790 Inited to -0.0625
    u8 _1794;                           // 1794 Inited to 0
    u8 _1795;                           // 1795 Inited to 0
    u8 _1796;                           // 1796 Inited to 0
    u8 _1797;                           // 1797 Inited to 0
    u8 _1798;                           // 1798 Inited to 0
    u8 _1799;                           // 1799 Inited to 0
    u8 _179A;                           // 179A Inited to 0
    u8 _179B;                           // 179B Inited to 0
    u32 _179C;                          // 179C Inited to 0
};
