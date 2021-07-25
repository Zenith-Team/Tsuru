#pragma once

#include "game/enemyfreezemgr.h"
#include "game/actor/multistateactor.h"

class Enemy : public MultiStateActor { // size: 0x1880
    SEAD_RTTI_OVERRIDE(Enemy, MultiStateActor)

public:
    Enemy(const ActorBuildInfo* pBuildInfo);
    virtual ~Enemy();

    u32 beforeExecute() override;

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;
    void vf10C(u8 unk) override;

    void vf11C() override;
    void vf124(f32) override;
    u32 vf12C() override;

    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;
    void doStateChange(StateBase* state) override;

    virtual void vf18C();
    virtual void damagePlayer(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf19C();
    virtual void freeze();                                                                       // creates ice actors
    virtual void vf1AC();                                                                        // called on freeze
    virtual void vf1B4();                                                                        // called on freeze break
    virtual void vf1BC();                                                                        // called on freeze break, decides next state
    virtual void vf1C4();
    virtual void vf1CC();
    virtual bool vf1D4(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);                       // pre collision enemy 2
    virtual bool vf1DC(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);                       // pre collision player
    virtual bool vf1E4(bool& unk, HitboxCollider* pHCSelf, HitboxCollider* pHCOther);            // pre collision enemy
    virtual void vf1EC(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);                       // pre collision yoshi related
    virtual bool vf1F4(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);                       // pre collision yoshi
    virtual bool vf1FC(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);                       // pre collision unk
    virtual bool vf204(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);                       // pre collision actor
    virtual void collisionEnemy(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual void collisionPlayer(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual void collisionYoshi(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual void vf224(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionStar(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionSlide(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionPropellerDrill(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf244(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionGroundPound(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionGroundPoundYoshi(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionPenguinSlide(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionPipeCannon(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf26C(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionThrowableObject(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionFireball(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);            
    virtual bool collisionIceball(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);             
    virtual bool collisionHammer(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool collisionFireballYoshi(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf29C(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf2A4(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf2AC(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
    virtual bool vf2B4(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);
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
    DECLARE_STATE_VIRTUAL(Enemy, DieFumi);
    DECLARE_STATE_VIRTUAL(Enemy, DieFall);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState3);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState4);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState5);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState6);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState7);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState8);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState9);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState10);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState11);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState12);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState13);
    DECLARE_STATE_VIRTUAL(Enemy, EnemyState14);
    DECLARE_STATE_VIRTUAL(Enemy, Ice);

    static void collisionCallback(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);

    u32 processCollision(HitboxCollider* pHCSelf, HitboxCollider* pHCOther, u32 unk);

    void killPlayerJump(StageActor* pPlayer, const Vec2f& rSpeed, StateBase* pState);
    void killPlayerSpin(StageActor* pPlayer);
    void killYoshiStomp(StageActor* pPlayer);

    u32 _17C8;                  // _17C8
    u32 _17CC;                  // _17CC
    f32 _17D0;                  // _17D0
    f32 _17D4;                  // _17D4
    u32 _17D8;                  // _17D8
    u32 _17DC;                  // _17DC
    u8  _17E0;                  // _17E0
    u8  _17E1;                  // _17E1
    u8  _17E2;                  // _17E2
    u8  _17E3;                  // _17E3
    u16 _17E4[0x4];             // _17E4
    u32 _17EC;                  // _17EC
    EnemyFreezeMgr mFreezeMgr;  // _17F0
    u8  _1840[0x1860-0x1840];   // _1840  //? Possibly BabyYoshiBubbleData
    Enemy* mSelf;               // _1860
    void* _1864;                // _1864
    u8  _1868;                  // _1868
    u8  _1869;                  // _1869
    u8  _186A;                  // _186A
    u8  _186B;                  // _186B
    u16 _186C;                  // _186C
    u16 _186E;                  // _186E
    u32 _1870;                  // _1870
    u8  _1874;                  // _1874
    u8  _1875;                  // _1875
    u8  _1876;                  // _1876
    u8  _1877;                  // _1877
    u32 _1878;                  // _1878
    u8  _187C;                  // _187C
    u8  _187D;                  // _187D
    u8  _187E;                  // _187E
    u8  _187F;                  // _187F
};
