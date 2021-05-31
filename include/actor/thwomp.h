#pragma once

#include "actor/enemy.h"

#include "effect.h"

class Thwomp : public Enemy {  // size: 0x1a70
    SEAD_RTTI_OVERRIDE(Thwomp, Enemy)

public:
    Thwomp(const ActorBuildInfo* buildInfo);
    virtual ~Thwomp();

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    void setPlayerId(s8 id) override;

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

    void move(Vec2& dest) override;
    void setYSpeed(f32 ySpeed) override;

    u32 vf16C() override;
    u32 vf174() override;

    void getRect(Rect& rect) override;

    void vf18C() override;

    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void vf2BC() override;

    DECLARE_STATE_OVERRIDE(Thwomp, DieFall)

    u32 _1880;                          // 1880
    u32 _1884;                          // 1884
    u32 _1888;                          // 1888
    u32 _188C;                          // 188C
    u32 _1890;                          // 1890
    u32 _1894;                          // 1894
    u32 _1898;                          // 1898
    u32 _189C;                          // 189C
    u32 unk1[2];                        // 18A0
    f32 _18A8;                          // 18A8
    f32 _18AC;                          // 18AC
    f32 _18B0;                          // 18B0
    EffectWrapper effectWrapper;        // 18B4
    HitboxCollider hitboxCollider;      // 191C
    void* _1A44;                        // 1A44
    f32 _1A48;                          // 1A48
    f32 _1A4C;                          // 1A4C
    f32 _1A50;                          // 1A50
    f32 _1A54;                          // 1A54
    f32 _1A58;                          // 1A58
    u32 unk2;                           // 1A5C
    u32 _1A60;                          // 1A60
    Thwomp* self;                       // 1A64
    void* _1A68;                        // 1A68
    u32 unk3;                           // 1A6C
};
