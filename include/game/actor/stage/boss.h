#pragma once

#include <game/actor/stage/enemy.h>
#include <game/playerlooktarget.h>
#include <game/actor/stage/stageactor.h>

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
    virtual void vf59C(); // deleted
    virtual bool isNextDamageKill(); // deleted
    virtual void vf5AC(); // deleted
    virtual bool isDamageHit();
    virtual void processHits(u32 amount);
    virtual u32 vf5C4() = 0;
    virtual u32 vf5CC() = 0;
    virtual u32 vf5D4() = 0;
    virtual u32 vf5DC() = 0;
    virtual u32 vf5E4() = 0;
    virtual u32 vf5EC() = 0;
    virtual u32 vf5F4() = 0;
    virtual u32 vf5FC() = 0;
    virtual void playDamageAnim();
    virtual void vf60C();
    virtual void vf614();
    virtual u32 vf61C();
    virtual void vf624();
    virtual u32 vf62C();
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
    virtual void vf7C4();
    virtual u32 vf7CC();
    virtual void initHitboxCollider();
    virtual void initModels();
    virtual void updateModel();
    virtual void initHitsToDeath();
    virtual void initHitsToDamage();
    virtual u32 init();

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

/*
    __ct__4BossFPC14ActorBuildInfo = 0xEBEB968;
    __dt__4BossFv = 0xEBEE2E0;
    beforeExecute__4BossFv = 0xEBEBD0C;
    afterExecute__4BossFUi = 0xEBEBDDC;
    onDelete__4BossFv = 0xEBEDC2C;
    setPlayerId__4BossFSc = 0xEBED9C0;
    removeActiveColliders__4BossFv = 0xEBEDDF0;
    addActiveColliders__4BossFv = 0xEBEDE7C;
    getCollisionMgr__4BossFv = 0xEBED9F8;
    vfAC__4BossFv = 0xEBED9C8;
    vfB4__4BossFv = 0xEBED9CC;
    vfBC__4BossFv = 0xEBED9D4;
    vfC4__4BossFv = 0xEBED9D8;
    vfCC__4BossFv = 0xEBED9DC;
    vf10C__4BossFUc = 0xEBED9E0;
    vf11C__4BossFv = 0xEBED9E8;
    vf124__4BossFf = 0xEBED9EC;
    vf12C__4BossFv = 0xEBED9F0;
    vf154__4BossFv = 0xEBECE40;
    move__4BossFR4Vec2 = 0xEBEDA00;
    setYSpeed__4BossFf = 0xEBEDA14;
    vf16C__4BossFv = 0xEBEDA1C;
    vf174__4BossFv = 0xEBEDA24;
    getRect__4BossFR4Rect = 0xEBEE254;
    vf18C__4BossFv = 0xEBEDAA8;
    freeze__4BossFv = 0xEBECEAC;
    vf1BC__4BossFv = 0xEBECF64;
    vf1C4__4BossFv = 0xEBEE2D0;
    collisionPlayer__4BossFP14ActiveColliderT1 = 0xEBEBFDC;
    collisionYoshi__4BossFP14ActiveColliderT1 = 0xEBEC2B4;
    collisionStar__4BossFP14ActiveColliderT1 = 0xEBEDCC8;
    collisionSlide__4BossFP14ActiveColliderT1 = 0xEBEDCD0;
    collisionPropellerDrill__4BossFP14ActiveColliderT1 = 0xEBEC5D0;
    vf244__4BossFP14ActiveColliderT1 = 0xEBEDCD8;
    collisionGroundPound__4BossFP14ActiveColliderT1 = 0xEBEC3AC;
    collisionPenguinSlide__4BossFP14ActiveColliderT1 = 0xEBEC5E0;
    collisionThrowableObject__4BossFP14ActiveColliderT1 = 0xEBEC8E0;
    collisionFireball__4BossFP14ActiveColliderT1 = 0xEBEC6D4;
    collisionIceball__4BossFP14ActiveColliderT1 = 0xEBECBCC;
    isOnGround__4BossFv = 0xEBECE00;
    vf2F4__4BossFv = 0xEBEDD38;
    beginState_DieFumi__4BossFv = 0xEBEDC9C;
    executeState_DieFumi__4BossFv = 0xEBEDCA0;
    endState_DieFumi__4BossFv = 0xEBEDCA4;
    beginState_BossState1__4BossFv = 0xEBEBECC;
    executeState_BossState1__4BossFv = 0xEBEBEDC;
    endState_BossState1__4BossFv = 0xEBEBEEC;
    beginState_BossState2__4BossFv = 0xEBEBEFC;
    executeState_BossState2__4BossFv = 0xEBEBF0C;
    endState_BossState2__4BossFv = 0xEBEBF1C;
    beginState_BossState3__4BossFv = 0xEBEBF2C;
    executeState_BossState3__4BossFv = 0xEBEBF3C;
    endState_BossState3__4BossFv = 0xEBEBF4C;
    beginState_BossState4__4BossFv = 0xEBEBF5C;
    executeState_BossState4__4BossFv = 0xEBEBF6C;
    endState_BossState4__4BossFv = 0xEBEBF7C;
    beginState_BossState5__4BossFv = 0xEBEBF8C;
    executeState_BossState5__4BossFv = 0xEBEBF9C;
    endState_BossState5__4BossFv = 0xEBEBFAC;
    startCutscene__4BossFv = 0xEBEDCA8;
    endCutscene__4BossFv = 0xEBEDCB4;
    vf56C__4BossFv = 0xEBEDCC0;
    vf574__4BossFv = 0xEBEBFBC;
    vf57C__4BossFv = 0xEBEDCC4;
    vf584__4BossFv = __deleted_virtual_called;
    vf58C__4BossFv = 0xEBEDD3C;
    vf594__4BossFv = 0xEBEDD4C;
    vf59C__4BossFv = __deleted_virtual_called;
    isNextDamageKill__4BossFv = __deleted_virtual_called;
    vf5AC__4BossFv = __deleted_virtual_called;
    isDamageHit__4BossFv = 0xEBEDD90;
    processHits__4BossFUi = 0xEBEDD98;
    playDamageAnim__4BossFv = 0xEBEDDBC;
    vf60C__4BossFv = 0xEBEDDC0;
    vf614__4BossFv = 0xEBEDDC4;
    vf61C__4BossFv = 0xEBEDDC8;
    vf624__4BossFv = __deleted_virtual_called;
    vf62C__4BossFv = 0xEBEDDD0;
    vf634__4BossFUi = 0xEBEDDD8;
    vf63C__4BossFUi = 0xEBEDDE4;
    vf644__4BossFv = 0xEBED120;
    onStomp__4BossFP5Actor = 0xEBED214;
    onStompDamage__4BossFP5Actor = 0xEBEDF28;
    onStompKill__4BossFP5Actor = 0xEBEDF2C;
    vf664__4BossFv = 0xEBEDF44;
    changeState_BossState1__4BossFv = 0xEBEDF48;
    onGroundPoundDamage__4BossFv = 0xEBEDF60;
    onGroundPoundKill__4BossFv = 0xEBEDF70;
    vf684__4BossFv = __deleted_virtual_called;
    vf68C__4BossFv = __deleted_virtual_called;
    vf694__4BossFv = __deleted_virtual_called;
    vf69C__4BossFv = __deleted_virtual_called;
    onStompDamageEx__4BossFv = 0xEBEDF80;
    onStompKillEx__4BossFv = 0xEBEDF84;
    onStompDamage2__4BossFv = 0xEBEDF9C;
    onStompKill2__4BossFv = 0xEBEDFA0;
    vf6C4__4BossFv = __deleted_virtual_called;
    vf6CC__4BossFv = __deleted_virtual_called;
    vf6D4__4BossFv = 0xEBEDFB8;
    onDamage__4BossFv = 0xEBEDFC0;
    onKill__4BossFv = 0xEBEDFC4;
    immuneToGroundPound__4BossFv = 0xEBEDFD4;
    vf6F4__4BossFv = 0xEBEDFDC;
    vf6FC__4BossFv = 0xEBEDFE4;
    immuneToFire__4BossFv = 0xEBEDFEC;
    vf70C__4BossFv = __deleted_virtual_called;
    vf714__4BossFv = __deleted_virtual_called;
    vf71C__4BossFv = __deleted_virtual_called;
    spawnDamageKillEffect__4BossFv = 0xEBEDFF4;
    spawnDamageNormalEffect__4BossFv = 0xEBEDFF8;
    vf734__4BossFv = 0xEBEDFFC;
    vf73C__4BossFv = __deleted_virtual_called;
    vf744__4BossFv = 0xEBEE000;
    playStompSound__4BossFv = 0xEBEE004;
    playStompKillSound__4BossFv = 0xEBEE01C;
    vf75C__4BossFv = __deleted_virtual_called;
    playStarKillSound__4BossFv = 0xEBEE034;
    vf76C__4BossFv = __deleted_virtual_called;
    playDamageKillSound__4BossFv = 0xEBEE04C;
    playFireDamageSound__4BossFv = 0xEBEE064;
    playDamageKillFSound__4BossFv = 0xEBEE0D8;
    playFireDamageSound2__4BossFv = 0xEBEE130;
    playFireKillSound__4BossFv = 0xEBEE1A4;
    playStarDamageSound__4BossFv = 0xEBEE1FC;
    playDamageKillFSound2__4BossFv = 0xEBEE214;
    playLoseSound__4BossFv = 0xEBEE22C;
    vf7B4__4BossFv = __deleted_virtual_called;
    vf7BC__4BossFv = __deleted_virtual_called;
    vf7C4__4BossFv = 0xEBEE230;
    vf7CC__4BossFv = 0xEBED3BC;
    initHitboxCollider__4BossFv = 0xEBED3F4;
    initModels__4BossFv = 0xEBEE2B8;
    initHitsToDeath__4BossFv = 0xEBEE2C0;
    initHitsToDamage__4BossFv = 0xEBEE2C4;
    init__4BossFv = 0xEBEE2C8;
*/
