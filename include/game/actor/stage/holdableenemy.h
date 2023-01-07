#pragma once

#include "game/actor/stage/enemy.h"

class HoldableEnemy : public Enemy { // Size: 0x18B8
    SEAD_RTTI_OVERRIDE(HoldableEnemy, Enemy);

public:
    HoldableEnemy(const ActorBuildInfo* buildInfo);
    virtual ~HoldableEnemy();

    u32 beforeExecute() override;

    u32 onDelete() override;

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void vf10C(u8) override;

    void vf11C() override;
    void vf124(f32) override;
    u32 vf12C() override;

    void move(Vec2f& dest) override;
    void setYSpeed(f32) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;

    void vf18C() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    virtual void onNormalJumpHit(StageActor* collidingActor);
    virtual void onMiniJumpHit(StageActor* collidingActor);
    virtual void onSpinJumpHit(StageActor* collidingActor);
    virtual void onHit(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void vf504(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void vf50C(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void vf514(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void vf51C() = 0;
    virtual void changeToThrowState() = 0;
    DECLARE_STATE_VIRTUAL(HoldableEnemy, Grabbed);
    DECLARE_STATE_VIRTUAL(HoldableEnemy, Down);
    DECLARE_STATE_VIRTUAL(HoldableEnemy, HoldableEnemyState3);

    Direction::DirectionType getKickDirection(StageActor* collidingActor);
    bool processCollision(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    void FUN_022EB724(StageActor* collidingActor, bool playDownSound);
    bool FUN_22EB888(StageActor* collidingActor);

    Vec3f _1880;
    f32 _188C;
    f32 _1890;
    f32 _1894;
    f32 _1898;
    f32 _189C;
    u32 _18A0;
    u32 _18A4;
    u8 _18A8;
    u32 _18AC;
    u8 _18B0;
    u8 _18B1;
    u32 _18B4; // unknown values
};

static_assert(sizeof(HoldableEnemy) == 0x18B8, "HoldableEnemy size mismatch");
