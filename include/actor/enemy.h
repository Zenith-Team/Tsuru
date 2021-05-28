#pragma once

#include "multistateactor.h"
#include "enemyfreezemgr.h"

class Enemy : public MultiStateActor {  // size: 0x1880
    SEAD_RTTI_OVERRIDE(Enemy, MultiStateActor)

public:
    Enemy(const ActorBuildInfo* buildInfo);
    virtual ~Enemy();

    u32 beforeExecute() override;
    void damageFromUnder() override;
    void vf14C(Actor*) override;
    bool vf154() override;
    void doStateChange(StateBase* state) override;

    // TODO

    virtual void vf18C();
    virtual void damagePlayer(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual bool vf19C();
    virtual void freeze();                                                                       // creates ice actors
    virtual void vf1AC();                                                                        // called on freeze
    virtual void vf1B4();                                                                        // called on freeze break
    virtual void vf1BC();                                                                        // called on freeze break, decides next state
    virtual void vf1C4();
    virtual void vf1CC();

    virtual bool vf1D4(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision enemy 2
    virtual bool vf1DC(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision player
    virtual bool vf1E4(bool& unk, ActiveCollider* acSelf, ActiveCollider* acOther);              // pre collision enemy
    virtual void vf1EC(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision yoshi related
    virtual bool vf1F4(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision yoshi
    virtual bool vf1FC(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision unk
    virtual bool vf204(ActiveCollider* acSelf, ActiveCollider* acOther);                         // pre collision actor

    virtual void collisionEnemy(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual void collisionPlayer(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual void collisionYoshi(ActiveCollider* acSelf, ActiveCollider* acOther);
    virtual void vf224(ActiveCollider* acSelf, ActiveCollider* acOther);

    virtual bool collisionStar(ActiveCollider* acSelf, ActiveCollider* acOther);                // 3
    virtual bool collisionSlide(ActiveCollider* acSelf, ActiveCollider* acOther);               // 5
    virtual bool collisionPropellerDrill(ActiveCollider* acSelf, ActiveCollider* acOther);      // 13
    virtual bool vf244(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 8
    virtual bool collisionGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther);         // 7
    virtual bool collisionGroundPoundYoshi(ActiveCollider* acSelf, ActiveCollider* acOther);    // 7
    virtual bool collisionPenguinSlide(ActiveCollider* acSelf, ActiveCollider* acOther);        // 10
    virtual bool collisionPipeCannon(ActiveCollider* acSelf, ActiveCollider* acOther);          // 17
    virtual bool vf26C(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 25
    virtual bool collisionThrowableObject(ActiveCollider* acSelf, ActiveCollider* acOther);     // 9
    virtual bool collisionFireball(ActiveCollider* acSelf, ActiveCollider* acOther);            // 1 14
    virtual bool collisionIceball(ActiveCollider* acSelf, ActiveCollider* acOther);             // 2 21
    virtual bool collisionHammer(ActiveCollider* acSelf, ActiveCollider* acOther);              // 19
    virtual bool collisionFireballYoshi(ActiveCollider* acSelf, ActiveCollider* acOther);       // 20
    virtual bool vf29C(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 24
    virtual bool vf2A4(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 26
    virtual bool vf2AC(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 3
    virtual bool vf2B4(ActiveCollider* acSelf, ActiveCollider* acOther);                        // 27

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

    static void collisionCallback(ActiveCollider* acSelf, ActiveCollider* acOther);

    u32 processCollision(ActiveCollider* acSelf, ActiveCollider* acOther, u32 unk);

    void killPlayerJump(Actor* player, const Vec2& speed, StateBase* state);
    void killPlayerSpin(Actor* player);
    void killYoshiStomp(Actor* player);

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
