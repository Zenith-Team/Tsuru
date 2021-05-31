#pragma once

#include "actor/boss.h"

// TODO: members, verify, symbols

class Bowser : public Boss {  // size: 0x25c8
    SEAD_RTTI_OVERRIDE(Bowser, Boss)

public:
    Bowser(const ActorBuildInfo* buildInfo);
    virtual ~Bowser();

    void afterCreate(u32) override;

    u32 beforeExecute() override;
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

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool vf244(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void vf2C4() override;

    void vf2F4() override;

    DECLARE_STATE_OVERRIDE(Bowser, DieFall);

    DECLARE_STATE_OVERRIDE(Bowser, BossState1);

    void demoStart() override;
    void demoEnd() override;
    void vf56C() override;

    void vf57C() override;

    u8 vf58C() override;
    void vf594() override;

    bool isDamageHit() override;
    void processHits(u32 amount) override;
    u32 getFireDamage() override;
    u32 getStompDamage() override;
    u32 getGroundPoundDamage() override;

    u32 getStompDamage2() override;
    u32 getStompDamageEx() override;
    void playDamageAnim() override;
    void timerEnd() override;
    void beforeUpdate() override;
    u32 fireTime() override;

    u32 stompTime() override;
    void vf634(PhysicsActor*) override;
    void vf63C(PhysicsActor*) override;

    void onStompDamage(PhysicsActor* other) override;
    void onStompKill(PhysicsActor* killer) override;
    void vf664() override;
    void changeState_State1() override;
    void onGroundPoundDamage() override;
    void onGroundPoundKill() override;

    void onStompDamageEx() override;
    void onStompKillEx() override;
    void onStompDamage2() override;
    void onStompKill2() override;

    u32 vf6D4() override;
    void onDamage() override;
    void onKill() override;
    bool immuneToGroundPound() override;
    u32 vf6F4();
    u32 vf6FC() override;
    bool immuneToFire() override;

    EffectWrapper* spawnDamageKillEffect() override;
    EffectWrapper* spawnDamageNormalEffect() override;
    EffectWrapper* spawnDamageEffect() override;

    u32 vf744() override;
    void playStompSound() override;
    void playStompKillSound() override;

    void playStarKillSound() override;

    void playDamageKillSound() override;
    void playFireDamageSound() override;
    void playDamageKillFSound() override;
    void playFireDamageSound2() override;
    void playFireKillSound() override;
    void playStarDamageSound() override;
    void playDamageKillFSound2() override;
    void playLoseSound() override;

    void vf7C4() override;
    u32 vf7CC() override;
    void initHitboxCollider() override;
    void initModels() override;
    void updateModel() override;
    void initHitsToDeath() override;
    void initHitsToDamage() override;
    u32 init();

    // TODO: class members here
};
