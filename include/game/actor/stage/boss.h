#pragma once

#include "game/actor/stage/enemy.h"
#include "game/playerlooktarget.h"
#include "game/actor/stage/stageactor.h"

class Boss : public Enemy { // Size: 0x1B78
    SEAD_RTTI_OVERRIDE(Boss, Enemy)

public:
    Boss(const ActorBuildInfo* buildInfo);
    virtual ~Boss();

    u32 onCreate() override;

    u32 beforeExecute() override;

    void afterExecute(u32) override;

    u32 onDelete() override;

    void setPlayerID(s8 id) override;
    void removeHitboxColliders() override;
    void addHitboxColliders() override;
    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void vf10C(u8 unk) override;

    void vf11C() override;
    void vf124(f32 unk) override;
    u32 vf12C() override;

    bool vf154() override;
    void move(Vec2f& dest) override;
    void setYSpeed(f32 ySpeed) override;
    u32 vf16C() override;
    u32 vf174() override;
    void getRect(Rect& rect) override;

    void vf18C() override;

    void freeze() override;

    void vf1BC() override;
    void vf1C4() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool vf244(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    bool isOnGround() override;

    void addScoreWhenHit() override;

    DECLARE_STATE_OVERRIDE(Boss, DieFumi);

    DECLARE_STATE_VIRTUAL(Boss, BossState1);
    DECLARE_STATE_VIRTUAL(Boss, BossState2);
    DECLARE_STATE_VIRTUAL(Boss, BossState3);
    DECLARE_STATE_VIRTUAL(Boss, BossState4);
    DECLARE_STATE_VIRTUAL(Boss, BossState5);

    virtual void startCutscene();
    virtual void endCutscene();
    virtual void vf56C();
    virtual void vf574();
    virtual void vf57C();
    virtual void vf584(); // deleted
    virtual bool vf58C();
    virtual void vf594();
    virtual u32 vf59C(); // deleted
    virtual bool isNextDamageKill(); // deleted
    virtual void vf5AC(); // deleted
    virtual bool isDamageHit();
    virtual void processHits(u32 amount);
    virtual u32 fireDamageAmount() = 0;
    virtual u32 stompDamageAmount() = 0;
    virtual u32 groundPoundDamageAmount() = 0;
    virtual u32 vf5DC() = 0;
    virtual u32 vf5E4() = 0;
    virtual u32 vf5EC() = 0;
    virtual u32 stompDamageAmount2() = 0;
    virtual u32 stompDamageAmountEx() = 0;
    virtual void playDamageAnim();
    virtual void timerEnd();
    virtual void beforeUpdate();
    virtual u32 fireTime();
    virtual void vf624();
    virtual u32 stompTime();
    virtual void vf634(u32);
    virtual void vf63C(u32);
    virtual void vf644();
    virtual void onStomp(StageActor* collidingPlayer);
    virtual void onStompDamage(StageActor* collidingPlayer);
    virtual void onStompKill(StageActor* collidingPlayer);
    virtual void vf664();
    virtual void changeState_BossState1();
    virtual void onGroundPoundDamage();
    virtual void onGroundPoundKill();
    virtual void vf684(); // deleted
    virtual void vf68C(); // deleted
    virtual void vf694(); // deleted
    virtual void vf69C(); // deleted
    virtual void onStompDamageEx();
    virtual void onStompKillEx();
    virtual void onStompDamage2();
    virtual void onStompKill2();
    virtual void vf6C4(); // deleted
    virtual void vf6CC(); // deleted
    virtual u32 vf6D4();
    virtual void onDamage();
    virtual void onKill();
    virtual void immuneToGroundPound();
    virtual u32 vf6F4();
    virtual u32 vf6FC();
    virtual void immuneToFire();
    virtual void vf70C(); // deleted
    virtual void vf714(); // deleted
    virtual void vf71C(); // deleted
    virtual void spawnDamageKillEffect();
    virtual void spawnDamageNormalEffect();
    virtual void vf734();
    virtual void vf73C(); // deleted
    virtual void vf744();
    virtual void playStompSound();
    virtual void playStompKillSound();
    virtual void vf75C(); // deleted
    virtual void playStarKillSound();
    virtual void vf76C(); // deleted
    virtual void playDamageKillSound();
    virtual void playFireDamageSound();
    virtual void playDamageKillFSound();
    virtual void playFireDamageSound2();
    virtual void playFireKillSound();
    virtual void playStarDamageSound();
    virtual void playDamageKillFSound2();
    virtual void playLoseSound();
    virtual void vf7B4(); // deleted
    virtual void vf7BC(); // deleted
    virtual void setLookTarget();
    virtual u32 vf7CC();
    virtual void initHitboxCollider();
    virtual void initModels();
    virtual void updateModel();
    virtual void initHitsToDeath();
    virtual void initHitsToDamage();
    virtual u32 init();

    // Just thunks to this->updateModel();
    void updateModelTrampoline();

    // All these are score related
    void FUN_202D0F8(u32, Vec3f*, u32);
    void FUN_202D030(StageActor*, Vec3f*, u32);
    void FUN_202D094(StageActor*, Vec3f*, u32);

    u32 hitsToDeath;        // Hits until boss dies
    u32 hitsToDamage;       // Fireball hits until boss takes damage
    u32 _1888;              // Some type of timer, related to stomp?
    bool isRumbling;
    bool isCutscene;
    u8 _188E[18];           // Unknown values
    u8 soundActor[0x11C];   // MovingSoundActor, but we don't have the pure overrides yet so we can't instanciate it
    u16 _19BC;
    u8 _19BE[2];            // Unknown values
    PlayerLookTarget lookTarget;
    Vec3f _19EC;
    f32 _19F8;
    u8 _19FC[4];            // Unknown values
    u32 _1A00;
    Boss* self;
    void* _1A08;
    HitboxCollider hitboxCollider;
    void* _1B34;
    Vec3f _1B38;
    Vec3f _1B44;
    Vec3f _1B50;
    Vec3f _1B5C;
    f32 _1B68;
    f32 _1B6C;
    u32 _1B70;
    u32 _1B74;
};

static_assert(sizeof(Boss) == 0x1B78, "Boss size mismatch");
