#pragma once

#include "game/actor/stage/enemy.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "game/playermgr.h"
#include "game/sound/sound.h"
#include "game/direction.h"
#include "math/easing.h"
#include "sead/random.h"
#include "sead/mathcalccommon.h"
#include "game/actor/actormgr.h"
#include "log.h"

class Kamiya : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Kamiya, Enemy)

public:
    enum SpawningStage {
        SpawningStage_Growth,
        SpawningStage_Spin,
    };

public:
    Kamiya(const ActorBuildInfo* buildInfo);
    virtual ~Kamiya() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
    Easing easerX;
    Easing easerY;
    Easing easerExtra;
    u32 health;
    Player* targetPlayer;

    //* Spawning
    SpawningStage stage;
    u32 spawningTimer;
    f32 spawnRotationY;
    f32 spawnRotationZ;
    f32 targetScale;
    bool leftSpinDone;
    bool rightSpinSet;

    //* Flying
    u16 flyTimer;

    //* Attacking
    bool projectileSpawned;
    u16 attackTimer;

    //* Fleeing
    u16 fleeTimer;
    u8 fleeResets;

    static const u32 possibleProjectiles[];

    DECLARE_STATE(Kamiya, Spawning);
    DECLARE_STATE(Kamiya, Flying);
    DECLARE_STATE(Kamiya, Attacking);
    DECLARE_STATE(Kamiya, Fleeing);
    DECLARE_STATE(Kamiya, Dying);
};

CREATE_STATE(Kamiya, Spawning);
CREATE_STATE(Kamiya, Flying);
CREATE_STATE(Kamiya, Attacking);
CREATE_STATE(Kamiya, Fleeing);
CREATE_STATE(Kamiya, Dying);

const Profile KamiyaProfile(&Kamiya::build, ProfileID::Kamiya, "Kamiya", nullptr, 0);
PROFILE_RESOURCES(ProfileID::Kamiya, "kameck");


const u32 Kamiya::possibleProjectiles[] = {
    ProfileID::KamiyaArrow,
    512,
    467,
    853,
};

class KamiyaArrow : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(KamiyaArrow, Enemy)

public:
    KamiyaArrow(const ActorBuildInfo* buildInfo);
    virtual ~KamiyaArrow() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
    Vec2f targetDirection;
    u32 adjustTimer;
    Kamiya* parentKamiya;
    f32 targetRotation;
    f32 angle;

    DECLARE_STATE(KamiyaArrow, Following);
    DECLARE_STATE(KamiyaArrow, Adjusting);
};

CREATE_STATE(KamiyaArrow, Following);
CREATE_STATE(KamiyaArrow, Adjusting);

const Profile KamiyaArrowProfile(&KamiyaArrow::build, ProfileID::KamiyaArrow);

Kamiya::Kamiya(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , easerX()
    , easerY()
    , easerExtra()
    , health(20)
    , targetPlayer(nullptr)
    , stage(SpawningStage_Growth)
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
{ }

Actor* Kamiya::build(const ActorBuildInfo* buildInfo) {
    return new Kamiya(buildInfo);
}

u32 Kamiya::onCreate() {
    this->doStateChange(&Kamiya::StateID_Spawning);

    this->model = ModelWrapper::create("kameck", "kameck", 26);
    this->model->playSklAnim("fly_wait", 0);
    this->updateModel();

    return 1;
}

u32 Kamiya::onExecute() {
    this->updateModel();
    this->states.execute();

    return 1;
}

u32 Kamiya::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

void Kamiya::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

/* STATE: Spawning */

void Kamiya::beginState_Spawning() {
    this->scale.set(0.0f);
    this->scale.z = 1.0f;

    this->easerX.set(&Easing::circOut, 0.0f, 0.75f, 0.025f);
}

void Kamiya::executeState_Spawning() {
    switch (this->stage) {
        case SpawningStage_Growth: {
            if (this->easerX.ease(this->targetScale)) {
                this->easerY.set(&Easing::sineInOut, 0.0f, 340.0f, 0.025f);
                this->easerExtra.set(&Easing::sineInOut, this->position.y, this->position.y + 32.0f, 0.01f);
                this->stage = SpawningStage_Spin;
            }

            this->scale.set(this->targetScale);

            break;
        }

        case SpawningStage_Spin: {
            this->rotation.y = fixDeg(this->spawnRotationY);

            bool spin = this->easerY.ease(this->spawnRotationY);
            bool up = this->easerExtra.ease(this->position.y);

            if (spin && up) {
                this->doStateChange(&Kamiya::StateID_Flying);
            }

            break;
        }
    }
}

void Kamiya::endState_Spawning() { }

/* STATE: Flying */

void Kamiya::beginState_Flying() {
    this->flyTimer = 0;
    this->speed.x = 0.0f;
    this->model->playSklAnim("fly_wait", 0);

    this->targetPlayer = PlayerMgr::instance()->getRandomPlayer();
}

void Kamiya::executeState_Flying() {
    // Stalk player

    this->speed.x += (this->targetPlayer->position.x - this->position.x) / 2000.0f;

    this->direction = this->targetPlayer->direction;

    if (this->targetPlayer->direction == Direction::Right)
        this->speed.x -= 0.045f;
    else
        this->speed.x += 0.045f;

    // Clamp speed
    if (this->speed.x > 1.0f) this->speed.x -= 0.03f;   if (this->speed.x > 3.0f) this->speed.x -= 0.3f;
    if (this->speed.x < -1.0f) this->speed.x += 0.03f;  if (this->speed.x < -3.0f) this->speed.x += 0.3f;

    this->position.x += this->speed.x;

    // Face player
    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], 0x600000);

    this->flyTimer++;

    if (this->flyTimer > 360) {
        switch (sead::randU32(3)) {
            case 0:  this->flyTimer = 0;                              break;
            case 1:  this->doStateChange(&Kamiya::StateID_Attacking); break;
            case 2:  this->doStateChange(&Kamiya::StateID_Fleeing);   break;
            default:                                                  break;
        }
    }

    this->rotation.z = fixDeg(this->speed.x * 5.0f);
}

void Kamiya::endState_Flying() { }

/* STATE: Attacking */

void Kamiya::beginState_Attacking() {
    this->model->playSklAnim("fly_throw_ed", 0);
    this->model->loopSklAnims(false);
    this->projectileSpawned = false;
}

void Kamiya::executeState_Attacking() {
    if (this->model->sklAnims[0]->isAnimationDone() && !this->projectileSpawned) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.position = this->position;
        buildInfo.parentID = this->id;
        buildInfo.profile = Profile::get(512);
        /*((KamiyaArrow*)*/ActorMgr::instance()->create(buildInfo, 0)/*)->parentKamiya = this*/;

        this->projectileSpawned = true;
        this->model->playSklAnim("fly_throw_ed_wait", 0);
        this->attackTimer = 0;
    } else {
        if (this->attackTimer++ >= 120)
            this->doStateChange(&Kamiya::StateID_Flying);
    }
}

void Kamiya::endState_Attacking() {
    this->model->loopSklAnims(true);
}

/* STATE: Fleeing */

void Kamiya::beginState_Fleeing() {
    this->fleeTimer = 0;
    this->direction = Direction::opposite((Direction::DirectionType) this->targetPlayer->direction);
    this->fleeResets = 0;
}

void Kamiya::executeState_Fleeing() {
    // Escape player

    this->fleeTimer++;

    this->speed.x -= (this->targetPlayer->position.x - this->position.x) / 3000.0f;

    // Clamp speed
    if (this->speed.x > 1.0f) this->speed.x -= 0.03f;   if (this->speed.x > 3.0f) this->speed.x -= 0.3f;
    if (this->speed.x < -1.0f) this->speed.x += 0.03f;  if (this->speed.x < -3.0f) this->speed.x += 0.3f;

    this->position.x += this->speed.x;

    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[this->direction], 10000000);

    if (this->fleeTimer > 360) {
        this->doStateChange(&Kamiya::StateID_Flying);
        if (sead::randBool())
            this->doStateChange(&Kamiya::StateID_Attacking);
        else {
            this->fleeTimer = 120;
            this->fleeResets++;
        }
    }

    // Don't unfairly flee forever
    if (this->fleeResets > 2 + sead::randBool()) {
        this->doStateChange(&Kamiya::StateID_Spawning);
        this->fleeResets = 0;
    }
}

void Kamiya::endState_Fleeing() { }

/* STATE: Dying */

void Kamiya::beginState_Dying() { }
void Kamiya::executeState_Dying() { }
void Kamiya::endState_Dying() { }



KamiyaArrow::KamiyaArrow(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , targetDirection(0.0f)
    , parentKamiya(nullptr)
{ }

Actor* KamiyaArrow::build(const ActorBuildInfo* buildInfo) {
    return new KamiyaArrow(buildInfo);
}

u32 KamiyaArrow::onCreate() {
    this->scale.set(0.25f);
    this->speed.set(1.0f);
    this->model = ModelWrapper::create("star_coin", "star_coinB");
    this->doStateChange(&KamiyaArrow::StateID_Following);

    return 1;
}

u32 KamiyaArrow::onExecute() {
    this->updateModel();
    this->states.execute();

    return 1;
}

u32 KamiyaArrow::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

void KamiyaArrow::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

/* STATE: Following */

void KamiyaArrow::beginState_Following() { }

void KamiyaArrow::executeState_Following() {
    this->position.x += this->targetDirection.x * this->speed.x;
    this->position.y += this->targetDirection.y * this->speed.y;

    if (this->adjustTimer++ > 30) {
        this->adjustTimer = 0;
        this->doStateChange(&KamiyaArrow::StateID_Adjusting);
    }
}

void KamiyaArrow::endState_Following() { }

/* STATE: Adjusting */

void KamiyaArrow::beginState_Adjusting() {
    this->targetRotation = unfixDeg(this->rotation.z);
    this->angle = atan2f(this->parentKamiya->targetPlayer->position.y - this->position.y, this->parentKamiya->targetPlayer->position.x - this->position.x);
    this->targetDirection = radToDirection(this->angle);
}

void KamiyaArrow::executeState_Adjusting() {
    if (sead::Mathf::chase(&this->targetRotation, this->angle, 0.5f))
        this->doStateChange(&KamiyaArrow::StateID_Following);

    this->rotation.z = fixDeg(this->targetRotation);
}

void KamiyaArrow::endState_Adjusting() { }
