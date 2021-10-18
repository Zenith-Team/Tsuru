#pragma once

#include <game/enemyfreezemgr.h>
#include <game/actor/stage/multistateactor.h>

class Enemy : public MultiStateActor { // Size: 0x1880
    SEAD_RTTI_OVERRIDE(Enemy, MultiStateActor)

public:
    struct DeathInfo {
        Vec2f speed;
        f32 maxYSpeed;
        f32 gavity;
        StateBase* state;
        union {
            u32 _14;
            s8 _14_2;
        };
        bool noRespawn;
    };

public:
    Enemy(const ActorBuildInfo* buildInfo);
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
    // Damages colliding player
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual void damagePlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual bool vf19C();
    // Creates ice actors
    virtual void freeze();
    // Called on freeze
    virtual void vf1AC();
    // Called on freeze break
    virtual void vf1B4();
    // Called on freeze break, decides next state
    virtual void vf1BC();
    virtual void vf1C4();
    virtual void vf1CC();
    // Pre collision enemy 2
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf1D4(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // Pre collision player
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf1DC(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // Pre collision enemy
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf1E4(bool& unk, HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // Pre collision yoshi related
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual void vf1EC(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // Pre collision yoshi
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf1F4(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // Pre collision unk
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf1FC(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // Pre collision actor
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf204(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual void collisionEnemy(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual void vf224(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf244(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionPipeCannon(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf26C(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionHammer(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf29C(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool collisionGlowBabyYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf2AC(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    virtual bool vf2B4(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    virtual void vf2BC();
    virtual void vf2C4();
    virtual void vf2CC();
    virtual bool isOnGround();
    virtual void playFireHitSound();
    virtual void vf2E4();
    virtual void bouncePlayerWhenJumpedOn();
    virtual void addScoreWhenHit();
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

    // Default HitboxCollider collison callback
    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    // @param hcSelf Pointer to self HitboxCollider
    // @param hcOther Pointer to colliding actor's HitboxCollider
    // @param u32 Unknown
    u32 processCollision(HitboxCollider* hcSelf, HitboxCollider* hcOther, u32);

    // Bounces the colliding player when hit
    // @param player Colliding player
    // @param speed Speed to apply to player for bounce
    // @param state Pointer to state to switch to after bouncing player
    void killPlayerJump(StageActor* player, const Vec2f& speed, StateBase* state);
    // @param player Colliding player
    void killPlayerSpin(StageActor* player);
    // @param player Colliding player
    void killYoshiStomp(StageActor* player);

    DeathInfo deathInfo;            // _17C8
    u16 _17E4[0x4];                 // _17E4
    u32 _17EC;                      // _17EC
    EnemyFreezeMgr freezeMgr;       // _17F0
    u8 babyYoshiBubbleData[0x20];   // _1840
    Enemy* self;                    // _1860
    void* _1864;                    // _1864
    u8  _1868;                      // _1868
    u8  _1869;                      // _1869
    u8  _186A;                      // _186A
    u8  _186B;                      // _186B
    u16 _186C;                      // _186C
    u16 _186E;                      // _186E
    u32 _1870;                      // _1870
    u8  _1874;                      // _1874
    u8  _1875;                      // _1875
    u8  _1876;                      // _1876
    u8  _1877;                      // _1877
    u32 _1878;                      // _1878
    u8  _187C;                      // _187C
    u8  _187D;                      // _187D
    u8  _187E;                      // _187E
    u8  _187F;                      // _187F
};
