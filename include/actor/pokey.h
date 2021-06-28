#pragma once

#include "actor/enemy.h"

// TODO: members

class Pokey : public Enemy {  // size: 0x1970
    SEAD_RTTI_OVERRIDE(Pokey, Enemy)

public:
    Pokey(const ActorBuildInfo* buildInfo);
    virtual ~Pokey();

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    void setPlayerId(s8 id) override;
    void removeHitboxColliders() override;
    void addHitboxColliders() override;
    CollisionMgr* getCollisionMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;
    void killAtGoal() override;

    void damageFromUnder() override;
    void vf10C(u8 unk) override;

    void vf11C() override;
    void vf124(f32) override;
    u32 vf12C() override;

    bool vf154() override;
    void move(Vec2& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;

    void vf18C() override;

    void vf1C4() override;
    void vf1CC() override;

    void vf1EC(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool vf1F4(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void collisionEnemy(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool vf29C(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool vf2AC(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void vf2BC() override;

    bool isOnGround() override;

    void vf304() override;

    u8 unk1[240];   // I don't feel like documenting this right now
};
