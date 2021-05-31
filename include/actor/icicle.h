#pragma once

#include "enemy.h"

// TODO: methods, members, verify

class Icicle : public Enemy {  // size: 0x
    SEAD_RTTI_OVERRIDE(Icicle, Enemy);

public:
    Icicle(const ActorBuildInfo* buildInfo);
    virtual ~Icicle();

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    //? Some functions here

    void vf10C() override;
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
    
    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    
    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    //? Two unknown extra functions here
    
    // TODO: Class members here
};
