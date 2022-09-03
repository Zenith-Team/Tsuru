#pragma once

#include "game/actor/stage/enemy.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/modelnw.h"
#include "game/effect/effect.h"
#include "game/effect/effectid.h"
#include "game/playermgr.h"
#include "game/direction.h"
#include "math/easing.h"
#include "sead/random.h"
#include "sead/mathcalccommon.h"
#include "game/actor/actormgr.h"
#include "log.h"

class Kamiya : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Kamiya, Enemy)

public:
    Kamiya(const ActorBuildInfo* buildInfo);
    virtual ~Kamiya() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    // Collision conditions
    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    void updateModel();
    void damage();

    ModelWrapper* model;
    Easing easerX;
    Easing easerY;
    Easing easerExtra;
    u16 health;
    Player* targetPlayer;

    //* Spawning
    u32 spawningTimer;
    f32 spawnRotationY;
    f32 spawnRotationZ;
    f32 targetScale;
    bool isFirstSpawn;
    bool leftSpinDone;
    bool rightSpinSet;

    //* Flying
    u16 flyTimer;

    //* Attacking
    u16 attackTimer;
    bool projectileSpawned;
    u8 attackCount;

    //* Fleeing
    u16 fleeTimer;
    u8 fleeResets;
    bool lefted;

    //* Teleporting
    Vec2f targetPosition;

    //* Snipe
    u16 snipeTimer;
    bool throwing;

    static const u32 possibleProjectiles[];

    static const HitboxCollider::Info hitboxInfo;

    DECLARE_STATE(Kamiya, Spawning);
    DECLARE_STATE(Kamiya, Flying);
    DECLARE_STATE(Kamiya, Attacking);
    DECLARE_STATE(Kamiya, Fleeing);
    DECLARE_STATE(Kamiya, Dying);
    DECLARE_STATE(Kamiya, Damage);
    DECLARE_STATE(Kamiya, Teleport);
    DECLARE_STATE(Kamiya, Snipe);
};

CREATE_STATE(Kamiya, Spawning);
CREATE_STATE(Kamiya, Flying);
CREATE_STATE(Kamiya, Attacking);
CREATE_STATE(Kamiya, Fleeing);
CREATE_STATE(Kamiya, Dying);
CREATE_STATE(Kamiya, Damage);
CREATE_STATE(Kamiya, Teleport);
CREATE_STATE(Kamiya, Snipe);

const Profile KamiyaProfile(&Kamiya::build, ProfileID::Kamiya, "Kamiya", nullptr, 0);
PROFILE_RESOURCES(ProfileID::Kamiya, Profile::LoadResourcesAt_Course, "kamiya");

const u32 Kamiya::possibleProjectiles[] = {
    ProfileID::KoopaTroopa,
    ProfileID::MiniGoomba,
    ProfileID::ParaGoomba,
};

const HitboxCollider::Info Kamiya::hitboxInfo = {
    Vec2f(0.0f, 8.0f),
    Vec2f(16.0f, 10.0f),
    HitboxCollider::HitboxShape_Rectangle,
    3, 0,
    0xFFFFFFFF, 0xFFFFFFFF,
    0,
    &Enemy::collisionCallback
};

Kamiya::Kamiya(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , easerX()
    , easerY()
    , easerExtra()
    , health(3)
    , targetPlayer(nullptr)
    , spawningTimer(120)
    , spawnRotationY(0.0f)
    , spawnRotationZ(0.0f)
    , leftSpinDone(false)
    , rightSpinSet(false)
    , flyTimer(0)
    , projectileSpawned(false)
    , attackTimer(0)
    , fleeTimer(0)
    , fleeResets(0)
    , lefted(false)
    , attackCount(0)
    , targetPosition(0.0f)
    , isFirstSpawn(true)
    , snipeTimer(0)
{ }

Actor* Kamiya::build(const ActorBuildInfo* buildInfo) {
    return new Kamiya(buildInfo);
}

u32 Kamiya::onCreate() {
    this->doStateChange(&Kamiya::StateID_Spawning);
    this->model = ModelWrapper::create("kamiya", "kamiya", 1);
    this->model->playSklAnim("fly_appear");
    this->model->loopSklAnims(false);
    this->updateModel();

    this->hitboxCollider.init(this, &Kamiya::hitboxInfo);

    this->deathInfo.state = &Kamiya::StateID_Dying;

    return 1;
}

u32 Kamiya::onExecute() {
    this->updateModel();
    this->states.execute();

    return 1;
}

u32 Kamiya::onDraw() {
    this->model->draw();

    return 1;
}

void Kamiya::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

void Kamiya::damage() {
    if (--this->health <= 0)
        this->doStateChange(&Kamiya::StateID_Dying);
    else
        this->doStateChange(&Kamiya::StateID_Damage);
}

/* Collision conditions */

void Kamiya::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther);

    if (hitType == 0 || this->states.currentState() == &Kamiya::StateID_Dying)
        this->damagePlayer(hcSelf, hcOther);
    else if ((hitType == 1 || hitType == 3) && this->states.currentState() != &Kamiya::StateID_Damage && this->states.currentState() != &Kamiya::StateID_Teleport && this->states.currentState() != &Kamiya::StateID_Spawning)
        this->damage();
}

void Kamiya::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {

}

bool Kamiya::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return false;
}

bool Kamiya::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool Kamiya::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionYoshi(hcSelf, hcOther);

    return true;
}

bool Kamiya::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return false;
}

bool Kamiya::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    ((Kamiya*)hcSelf->owner)->doStateChange(&Kamiya::StateID_Damage);

    return true;
}

bool Kamiya::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return false;
}

bool Kamiya::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    ((Kamiya*)hcSelf->owner)->doStateChange(&Kamiya::StateID_Damage);

    return true;
}

/** STATE: Spawning */

void Kamiya::beginState_Spawning() {
    this->scale = (0.0f);
    this->scale.z = 1.0f;
    this->rotation.y = fixDeg(15.0f);

    Vec3f pos(this->position); pos.z -= 2500.0f;
    Vec3u rotation(0);
    Vec3f scale(0.5f);
    Effect::spawn(RP_Bunbun_ScaleUp_0, &pos, &rotation, &scale);
    this->easerX.set(&Easing::circOut, 0.0f, 0.75f, 0.0375f);

    if (this->isFirstSpawn)
        this->isFirstSpawn = false;
    else
        this->addHitboxColliders();
}

void Kamiya::executeState_Spawning() {
    if (this->easerX.ease(this->targetScale) && this->model->sklAnims[0]->frameCtrl.isDone())
        this->doStateChange(&Kamiya::StateID_Flying);

    this->scale = (this->targetScale);
}

void Kamiya::endState_Spawning() {
    this->addHitboxColliders();
}

/** STATE: Flying */

void Kamiya::beginState_Flying() {
    this->flyTimer = 0;
    this->speed.x = 0.0f;
    this->model->playSklAnim("fly_wait");

    this->targetPlayer = PlayerMgr::instance()->getRandomPlayer();
}

void Kamiya::executeState_Flying() {
    // Stalk player

    f32 distance = this->targetPlayer->position.x - this->position.x;
    this->speed.x += distance / 1565.0f;

    this->direction = this->directionToPlayerH(this->position);

    if (this->targetPlayer->direction == Direction::Right)
        this->speed.x -= 0.045f;
    else
        this->speed.x += 0.045f;

    // Clamp speed
    if (this->speed.x > 1.0f) this->speed.x -= 0.03f;   if (this->speed.x > 3.0f) this->speed.x -= 0.3f;
    if (this->speed.x < -1.0f) this->speed.x += 0.03f;  if (this->speed.x < -3.0f) this->speed.x += 0.3f;

    this->position.x += this->speed.x;

    // Face player
    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], fixDeg(2.5f));

    this->flyTimer++;

    this->rotation.z = fixDeg(this->speed.x * 5.0f);

    if (this->flyTimer > 240 && abs(this->speed.x) < 0.25f) {
        switch (sead::randU32(3)) {
            case 0:  this->flyTimer = 120;                            break;
            case 1:  this->doStateChange(&Kamiya::StateID_Attacking); break;
            case 2:  this->doStateChange(&Kamiya::StateID_Snipe);     break;
            default:                                                  break;
        }

        return;
    }

    if (this->attackCount >= 4) {
        this->attackCount = 0;
        this->doStateChange(&Kamiya::StateID_Fleeing);
    }
}

void Kamiya::endState_Flying() { }

/** STATE: Attacking */

void Kamiya::beginState_Attacking() {
    this->model->playSklAnim("fly_throw_ed");
    this->model->loopSklAnims(false);
    this->projectileSpawned = false;
    this->attackTimer = 0;
    this->attackCount++;
}

void Kamiya::executeState_Attacking() {
    if (this->model->sklAnims[0]->frameCtrl.isDone() && !this->projectileSpawned) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.position = this->position;
        buildInfo.parentID = this->id;
        sead::randBool() ? buildInfo.profile = Profile::get(Kamiya::possibleProjectiles[sead::randU32(4)]) : buildInfo.profile = Profile::get(ProfileID::KamiyaMagic);
        ActorMgr::instance()->create(buildInfo, 0);

        this->projectileSpawned = true;
        this->model->playSklAnim("fly_throw_ed_wait");
    } else {
        if (this->attackTimer++ >= 60)
            this->doStateChange(&Kamiya::StateID_Flying);
    }
}

void Kamiya::endState_Attacking() {
    this->model->loopSklAnims(true);
}

/** STATE: Fleeing */

void Kamiya::beginState_Fleeing() {
    this->fleeTimer = 0;
    this->direction = Direction::opposite((Direction::DirectionType) this->targetPlayer->direction);
    this->fleeResets = 0;
    this->model->playSklAnim("fly_magic");
    this->lefted = false;
}

void Kamiya::executeState_Fleeing() {
    // Escape player

    if (!lefted) {

    }

    this->fleeTimer++;

    this->speed.x -= (this->targetPlayer->position.x - this->position.x) / (3000.0f - (this->fleeTimer / 2));

    // Clamp speed
    if (this->speed.x > 1.0f) this->speed.x -= 0.025f;   if (this->speed.x > 3.0f) this->speed.x -= 0.25f;
    if (this->speed.x < -1.0f) this->speed.x += 0.025f;  if (this->speed.x < -3.0f) this->speed.x += 0.25f;

    this->position.x += this->speed.x;

    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], 25000000);

    // Don't unfairly flee forever (2 or 3 max)
    if (this->fleeResets > 2 + sead::randBool()) {
        this->doStateChange(&Kamiya::StateID_Flying);
        this->fleeResets = 0;
    }

    if (this->fleeTimer > 240) {
        if (sead::randBool())
            this->doStateChange(&Kamiya::StateID_Flying);
        else {
            this->fleeTimer = 120;
            this->fleeResets++;
        }
    }
}

void Kamiya::endState_Fleeing() { }

/** STATE: Dying */

void Kamiya::beginState_Dying() {
    this->model->playSklAnim("fly_damage");
    this->model->loopSklAnims(false);
}

void Kamiya::executeState_Dying() {
    if (this->model->sklAnims[0]->frameCtrl.isDone())
        this->isDeleted = true;
}

void Kamiya::endState_Dying() { }

/** STATE: Damage */

void Kamiya::beginState_Damage() {
    this->model->loopSklAnims(true);
    this->model->playSklAnim("fly_damage_s");
    this->easerY.set(&Easing::circInOut, unfixDeg(this->rotation.y), 360.0f, 3.33f);
    this->easerExtra.set(&Easing::circInOut, this->scale.x, 0.0f, 3.33f);
    this->removeHitboxColliders();
}

void Kamiya::executeState_Damage() {
    bool spin = this->easerY.ease(this->spawnRotationY);
    bool scale = this->easerExtra.ease(this->targetScale);

    if (spin && scale)
        this->doStateChange(&Kamiya::StateID_Teleport);

    this->rotation.y = fixDeg(this->spawnRotationY);
    this->scale = (this->targetScale);
}

void Kamiya::endState_Damage() {}

/** STATE: Teleport */

void Kamiya::beginState_Teleport() {
    this->removeHitboxColliders();
    if (sead::randBool())
        this->targetPosition = this->targetPlayer->get2DPosition();
    else
        this->targetPosition = this->get2DPosition();

    targetPosition.x += sead::randF32(-100.0f, 100.0f) * (sead::randBool() + 1);

    this->easerX.set(&Easing::circInOut, this->position.x, targetPosition.x, 3.33f);
    this->easerY.set(&Easing::circInOut, this->position.y, targetPosition.y, 3.33f);

    Vec3u rotation(0.0f);
    Vec3f scale(0.5f);
    Effect::spawn(RP_Bunbun_ScaleUp_0, &this->position, &rotation, &scale);
}

void Kamiya::executeState_Teleport() {
    bool x = this->easerX.ease(this->position.x);
    bool y = this->easerY.ease(this->position.y);

    if (x && y) {
        this->model->playSklAnim("fly_appear");
        this->model->loopSklAnims(false);
        this->doStateChange(&Kamiya::StateID_Spawning);
    }
}

void Kamiya::endState_Teleport() { }

/** STATE: Snipe */

void Kamiya::beginState_Snipe() {
    this->model->playSklAnim("fly_throw_st");
    this->model->loopSklAnims(false);
    this->snipeTimer = 0;
    this->throwing = false;
}

void Kamiya::executeState_Snipe() {
    if (!this->throwing && this->model->sklAnims[0]->frameCtrl.isDone()) {
        this->throwing = true;
        this->model->loopSklAnims(true);
        this->model->playSklAnim("fly_throw_st_wait");

        ActorBuildInfo poltergeist = { 0 };
        poltergeist.position = this->position;
        poltergeist.profile = Profile::get(ProfileID::Poltergeist);

        ActorMgr::instance()->create(poltergeist, 0);

        return;
    }

    if (this->throwing && this->snipeTimer++ >= 210)
        this->doStateChange(&Kamiya::StateID_Flying);
}

void Kamiya::endState_Snipe() { }

class KamiyaMagic : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(KamiyaMagic, Enemy)

public:
    KamiyaMagic(const ActorBuildInfo* buildInfo);
    virtual ~KamiyaMagic() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
    Vec2f targetDirection;
};

const Profile KamiyaMagicProfile(&KamiyaMagic::build, ProfileID::KamiyaMagic);

KamiyaMagic::KamiyaMagic(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
{ }

Actor* KamiyaMagic::build(const ActorBuildInfo* buildInfo) {
    return new KamiyaMagic(buildInfo);
}

u32 KamiyaMagic::onCreate() {
    this->scale = (0.25f);
    this->speed = 1.0f;
    this->model = ModelWrapper::create("star_coin", "star_coinB");

    return 1;
}

u32 KamiyaMagic::onExecute() {
    this->updateModel();
    this->states.execute();

    return 1;
}

u32 KamiyaMagic::onDraw() {
    this->model->draw();

    return 1;
}

void KamiyaMagic::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}
