#pragma once

#include "actor/multistateactor.h"
#include "enemyfreezemgr.h"

class Enemy : public MultiStateActor {  // size: 0x1880
    SEAD_RTTI_OVERRIDE(Enemy, MultiStateActor)

public:
    Enemy(const ActorBuildInfo* buildInfo);
    virtual ~Enemy();

    u32 beforeExecute() override;
    void damageFromUnder() override;
    void vf14C(StageActor*) override;
    bool vf154() override;
    void doStateChange(StateBase* state) override;

    // TODO

    virtual void vf18C();
    virtual void damagePlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual bool vf19C();
    virtual void freeze();                                                                       // creates ice actors
    virtual void vf1AC();                                                                        // called on freeze
    virtual void vf1B4();                                                                        // called on freeze break
    virtual void vf1BC();                                                                        // called on freeze break, decides next state
    virtual void vf1C4();
    virtual void vf1CC();

    virtual bool vf1D4(HitboxCollider* hcSelf, HitboxCollider* hcOther);                         // pre collision enemy 2
    virtual bool vf1DC(HitboxCollider* hcSelf, HitboxCollider* hcOther);                         // pre collision player
    virtual bool vf1E4(bool& unk, HitboxCollider* hcSelf, HitboxCollider* hcOther);              // pre collision enemy
    virtual void vf1EC(HitboxCollider* hcSelf, HitboxCollider* hcOther);                         // pre collision yoshi related
    virtual bool vf1F4(HitboxCollider* hcSelf, HitboxCollider* hcOther);                         // pre collision yoshi
    virtual bool vf1FC(HitboxCollider* hcSelf, HitboxCollider* hcOther);                         // pre collision unk
    virtual bool vf204(HitboxCollider* hcSelf, HitboxCollider* hcOther);                         // pre collision actor

    virtual void collisionEnemy(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void vf224(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    virtual bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther);                // 3
    virtual bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther);               // 5
    virtual bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther);      // 13
    virtual bool vf244(HitboxCollider* hcSelf, HitboxCollider* hcOther);                        // 8
    virtual bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther);         // 7
    virtual bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);    // 7
    virtual bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther);        // 10
    virtual bool collisionPipeCannon(HitboxCollider* hcSelf, HitboxCollider* hcOther);          // 17
    virtual bool vf26C(HitboxCollider* hcSelf, HitboxCollider* hcOther);                        // 25
    virtual bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther);     // 9
    virtual bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther);            // 1 14
    virtual bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther);             // 2 21
    virtual bool collisionHammer(HitboxCollider* hcSelf, HitboxCollider* hcOther);              // 19
    virtual bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);       // 20
    virtual bool vf29C(HitboxCollider* hcSelf, HitboxCollider* hcOther);                        // 24
    virtual bool vf2A4(HitboxCollider* hcSelf, HitboxCollider* hcOther);                        // 26
    virtual bool vf2AC(HitboxCollider* hcSelf, HitboxCollider* hcOther);                        // 3
    virtual bool vf2B4(HitboxCollider* hcSelf, HitboxCollider* hcOther);                        // 27

    virtual void vf2BC();
    virtual void vf2C4();
    virtual void vf2CC();
    virtual bool isOnGround();
    virtual void vf2DC();
    virtual void vf2E4();
    virtual void vf2EC();
    virtual void vf2F4();
    virtual void vf2FC();
    virtual void vf304();
    virtual void vf30C();
    virtual void vf314();
    virtual void vf31C();
    virtual void vf324();
    virtual void vf32C();
    virtual void vf334();
    virtual void vf33C();
    virtual void vf344();
    virtual void vf34C();
    virtual void vf354();
    virtual void vf35C();
    virtual void vf364();
    virtual void vf36C();
    virtual void vf374();

    DECLARE_STATE_VIRTUAL(Enemy, DieFumi)  // 37C 384 38C
    DECLARE_STATE_VIRTUAL(Enemy, DieFall)  // 394 39C 3A4

    virtual void vf3AC();
    virtual void vf3B4();
    virtual void vf3BC();
    virtual void vf3C4();
    virtual void vf3CC();
    virtual void vf3D4();
    virtual void vf3DC();
    virtual void vf3E4();
    virtual void vf3EC();
    virtual void vf3F4();
    virtual void vf3FC();
    virtual void vf404();
    virtual void vf40C();
    virtual void vf414();
    virtual void vf41C();
    virtual void vf424();
    virtual void vf42C();
    virtual void vf434();
    virtual void vf43C();
    virtual void vf444();
    virtual void vf44C();
    virtual void vf454();
    virtual void vf45C();
    virtual void vf464();
    virtual void vf46C();
    virtual void vf474();
    virtual void vf47C();
    virtual void vf484();
    virtual void vf48C();
    virtual void vf494();
    virtual void vf49C();
    virtual void vf4A4();
    virtual void vf4AC();
    virtual void vf4B4();
    virtual void vf4BC();
    virtual void vf4C4();

    DECLARE_STATE_VIRTUAL(Enemy, Ice)  // 4CC 4D4 4DC 

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    u32 processCollision(HitboxCollider* hcSelf, HitboxCollider* hcOther, u32 unk);

    void killPlayerJump(StageActor* player, const Vec2& speed, StateBase* state);
    void killPlayerSpin(StageActor* player);
    void killYoshiStomp(StageActor* player);

    u32 _17C8;
    u32 _17CC;
    f32 _17D0;
    f32 _17D4;
    u32 _17D8;
    u32 _17DC;
    u8  _17E0;
    u8  _17E1;
    u8  _17E2;
    u8  _17E3;
    u16 _17E4[0x4];
    u32 _17EC;
    EnemyFreezeMgr freezeMgr;   // 17F0
    u8  _1840[0x1860-0x1840];   // 1840  //? BabyYoshiBubbleData pretty sure
    Enemy* self;                // 1860
    void* _1864;
    u8  _1868;
    u8  _1869;
    u8  _186A;
    u8  _186B;
    u16 _186C;
    u16 _186E;
    u32 _1870;
    u8  _1874;
    u8  _1875;
    u8  _1876;
    u8  _1877;
    u32 _1878;
    u8  _187C;
    u8  _187D;
    u8  _187E;
    u8  _187F;
};
