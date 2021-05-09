#pragma once

#include "actor/enemy.h"

#include "effect.h"

class BrosBase : public Enemy {  // size: 0x3090
    SEAD_RTTI_OVERRIDE(BrosBase, Enemy)

public:
    BrosBase(const ActorBuildInfo* buildInfo);
    virtual ~BrosBase();

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
    void damagePlayer(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    void freeze() override;
    void vf1AC() override;

    void vf1BC() override;
    void vf1C4() override;

    void collisionPlayer(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    void collisionYoshi(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    bool collisionStar(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    bool collisionPropellerDrill(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    bool collisionGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    bool collisionIceball(ActiveCollider* acSelf, ActiveCollider* acOther) override;
    bool collisionHammer(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    bool vf2A4(ActiveCollider* acSelf, ActiveCollider* acOther) override;

    DECLARE_STATE_OVERRIDE(BrosBase, DieFumi)
    DECLARE_STATE_OVERRIDE(BrosBase, DieFall)

    DECLARE_STATE_VIRTUAL(BrosBase, Move)
    DECLARE_STATE_VIRTUAL(BrosBase, Attack)
    DECLARE_STATE_VIRTUAL(BrosBase, JumpSt)
    DECLARE_STATE_VIRTUAL(BrosBase, JumpMd)
    DECLARE_STATE_VIRTUAL(BrosBase, JumpEd)
    DECLARE_STATE_VIRTUAL(BrosBase, AirAttack)
    DECLARE_STATE_VIRTUAL(BrosBase, Down)

    virtual void vf58C();                   // deleted
    virtual f32 getProjectileCreateFrame();
    virtual f32 getProjectileThrowFrame();
    virtual void setWalkingSpeed();
    virtual void vf5AC();                   // deleted
    virtual s32 getTextureId();
    virtual void setWalkingTimer();
    virtual void vf5C4();                   // deleted
    virtual void vf5CC();
    virtual void vf5D4();
    virtual void createProjectile();
    virtual void throwProjectile();
    virtual void setHopTimer();
    virtual void setHopSpeed();
    virtual void doAirAttack();
    virtual u32 vf604();
    virtual u32 vf60C();
    virtual void doAttack();
    virtual void setThrowAnimation();
    virtual void vf624();
    virtual void vf62C();
    virtual void vf634();
    virtual void vf63C();                   // deleted
    virtual void vf644();                   // deleted
    virtual void vf64C();
    virtual void vf654();
    virtual bool vf65C();
    virtual void vf664();
    virtual void vf66C();

    u32 _1880;                          // 1880     //? model maybe
    u32 _unk1[60];                      // 1884     // unknown values 1
    u32 _1974;                          // 1974
    u32 _1978;                          // 1978
    u32 _197C;                          // 197C
    u32 _1980;                          // 1980
    u32 _1984;                          // 1984
    u32 _1988;                          // 1988
    u32 _198C;                          // 198C
    u32 _1990;                          // 1990
    f32 _1994;                          // 1994
    f32 _1998;                          // 1998
    u32 _199C;                          // 199C
    u32 _19A0;                          // 19A0
    f32 _19A4;                          // 19A4
    f32 _19A8;                          // 19A8
    f32 _19AC;                          // 19AC
    u8 _19B0;                           // 19B0
    u8 _unk2[3];                        // 19B1    // unknown values 2
    u32 _19B4;                          // 19B4
    u32 _19B8;                          // 19B8
    EffectWrapper effectWrapper;        // 19BC
    u8 _1A24[36];                       // 1A24    //* is class
    u32 _1A48;                          // 1A48
    u32 _unk3;                          // 1A4C    // unknown values 3
    u8 _1A50[5344];                     // 1A50    //* is class
    u32 _2F30;                          // 2F30
    u32 _2F34;                          // 2F34
    u8 _2F38;                           // 2F38
    u8 _2F39;                           // 2F39
    u16 _unk4;                          // 2F3A    // unknown values 4
    ActiveCollider activeCollider;      // 2F3C
    void* _3064;                        // 3064
    Vec3 _3068;                         // 3068
    f32 _3074;                          // 3074
    u32 _unk5;                          // 3078    // unknown values 5
    u32 _307C;                          // 307C
    u32 _3080;                          // 3080
    void* _3084;                        // 3084
    u8 _3088;                           // 3088
    u8 _3089;                           // 3089
    u16 _unk6[3];                       // 308A    // unknown values 6
};
