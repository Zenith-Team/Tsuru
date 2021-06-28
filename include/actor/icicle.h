#pragma once

#include "enemy.h"

#include "model.h"

class Icicle : public Enemy {  // size: 0x19b8
    SEAD_RTTI_OVERRIDE(Icicle, Enemy);

public:
    Icicle(const ActorBuildInfo* buildInfo);
    virtual ~Icicle();

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

    virtual void vf4E4();
    virtual void vf4EC();
    
    ModelWrapper* model;                // 1880
    u32 size;                           // 1884
    HitboxCollider* hitboxCollider;     // 1888
    void* _19B0;                        // 19B0
    u8 unk1[4];                         // 19B4  //? unknown values 1
};
