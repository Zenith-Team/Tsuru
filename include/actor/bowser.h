#pragma once

#include "actor/boss.h"

#include "resarchive.h"

// TODO: verify, symbols

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

    ResArchive* resArchive;         // 1B78
    ResArchive* resArchive2;        // 1B7C
    u32 _1B80;                      // 1B80
    u32 _1B84;                      // 1B84
    s32 _1B88;                      // 1B88     //? unsure of signedness
    s32 _1B8C;                      // 1B8C
    s32 _1B90;                      // 1B90
    u32 _1B94;                      // 1B94
    u32 _1B98;                      // 1B98
    u32 _1B9C;                      // 1B9C
    u8 _1BA0;                       // 1BA0
    u8 unk1[3];                     // 1BA1     //? unknown values 1
    u32 _1BA4;                      // 1BA4
    u32 _1BA8;                      // 1BA8
    u32 _1BAC;                      // 1BAC
    u32 _1BB0;                      // 1BB0
    u8 _1BB4;                       // 1BB4
    u8 _1BB5;                       // 1BB5
    u8 _1BB6;                       // 1BB6
    u8 unk2;                        // 1BB7     //? unknown values 2
    Vec3 _1BB8;                     // 1BB8     //? inited to position
    u32 _1BC4;                      // 1BC4
    u8 _1BC8[564];                  // 1BC8     //? is class
    void* _1DFC;                    // 1DFC
    void* _1E00;                    // 1E00
    void* _1E04;                    // 1E04
    void* _1E08;                    // 1E08
    void* _1E0C;                    // 1E0C
    f32 _1E10;                      // 1E10
    f32 _1E14;                      // 1E14
    Vec3 _1E18;                     // 1E18     //? 99% sure this is Vec3 because its a float* and it does new(0xC) and theres exactly that much space here
    f32 _1E24;                      // 1E24    
    u8 unk3[4];                     // 1E28     //? unknown values 3
    u32 _1E2C;                      // 1E2C    
    Bowser* _1E30;                  // 1E30    
    void* _1E34;                    // 1E34    
    void* _1E38;                    // 1E38
    void* _1E3C;                    // 1E3C
    void* _1E40;                    // 1E40
    u32 _1E44;                      // 1E44
    s32 _1E48;                      // 1E48
    EffectWrapper effectWrapper;    // 1E4C
    u8 unk4[52];					// 1EB4     //? unknown values 4
    u32 _1EE8;                      // 1EE8
    u8 unk5[1744];                  // 1EEC     //? unknown values 5
    u32 _25BC;                      // 25BC
    u32 _25C0;                      // 25C0
    u8 unk6[4];                     // 25C4
};
