#include "game/actor/stage/boss.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "game/actor/stage/bosscontroller.h"
#include "game/actor/actormgr.h"
#include "game/task/coursetask.h"
#include "game/actorglobalsholder.h"
#include "game/actor/stage/cutscenekamek.h"
#include "log.h"

class MilitaryCheep : public Boss {
    SEAD_RTTI_OVERRIDE_IMPL(MilitaryCheep, Boss)

public:
    MilitaryCheep(const ActorBuildInfo* buildInfo);
    virtual ~MilitaryCheep() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    DECLARE_STATE_OVERRIDE(MilitaryCheep, BossState1);
    DECLARE_STATE_OVERRIDE(MilitaryCheep, BossState5);

    //! WHAT A MESS
    void startCutscene() override;
    void endCutscene() override;
    bool vf58C() override;
    void vf594() override { }
    u32 vf59C() override;
    bool isNextDamageKill() override;
    void vf5AC() override;
    void processHits(u32 amount) override;
    u32 fireDamageAmount() override { return 1; }
    u32 stompDamageAmount() override { return 6; }
    u32 groundPoundDamageAmount() override { return 6; }
    u32 vf5DC() { return 0; }
    u32 vf5E4() { return 0; }
    u32 vf5EC() { return 0; }
    u32 stompDamageAmount2() override { return 6; }
    u32 stompDamageAmountEx() override { return 6; }
    u32 fireTime() override { return 24; }
    u32 stompTime() override { return 24; }
    void vf634(u32 param1) override { this->FUN_202D0F8(param1, &this->position, 3); }
    void vf63C(u32 param1) override { this->FUN_202D0F8(param1, &this->position, 4); }
    void onStompDamage(StageActor* col) override { this->FUN_202D030(col, &this->position, 5); }
    void onStompKill(StageActor* collidingPlayer) override;
    void onKill() override;
    void setLookTarget() override;
    void initHitboxCollider() override;
    void initModels() override;
    void updateModel() override;
    void initHitsToDeath() override;
    void initHitsToDamage() override;
    u32 init() override;

    static const HitboxCollider::Info sCollisionInfo;

    ModelWrapper* model;
};

CREATE_STATE_OVERRIDE(MilitaryCheep, Boss, BossState1);
CREATE_STATE_OVERRIDE(MilitaryCheep, Boss, BossState5);

const Profile MilitaryCheepProfile(&MilitaryCheep::build, ProfileID::MilitaryCheep);
PROFILE_RESOURCES(ProfileID::MilitaryCheep, Profile::LoadResourcesAt_Course, "star_coin");

const HitboxCollider::Info MilitaryCheep::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

Actor* MilitaryCheep::build(const ActorBuildInfo* buildInfo) {
    return new MilitaryCheep(buildInfo);
}

MilitaryCheep::MilitaryCheep(const ActorBuildInfo* buildInfo)
    : Boss(buildInfo)
    , model(nullptr)
{ }

u32 MilitaryCheep::onExecute() {
    this->states.execute();
    this->updateModelTrampoline();

    return 1;
}

u32 MilitaryCheep::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 0;
}

void MilitaryCheep::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther);

    if (hitType == 1) {
        this->onStomp(hcOther->owner);
    }
}

void MilitaryCheep::startCutscene() {
    LOG("start cutscene");
    this->isCutscene = true;
}

void MilitaryCheep::endCutscene() {
    LOG("end cutscene");
    this->isCutscene = false;
}

bool MilitaryCheep::vf58C() {
    return this->freezeMgr._44 ^ 1;
}

u32 MilitaryCheep::vf59C() {
    extern u32 (*vf59C__10BoomBoomW1Fv)(Boss*);
    return vf59C__10BoomBoomW1Fv(this);
}

bool MilitaryCheep::isNextDamageKill() {
    return (this->hitsToDeath - 1) / this->hitsToDamage == 1;
}

void MilitaryCheep::vf5AC() {
    extern void (*vf5AC__10BoomBoomW1Fv)(Boss*);
    vf5AC__10BoomBoomW1Fv(this);
}

void MilitaryCheep::processHits(u32 amount) {
    void (*processHits__10BoomBoomW1FUi)(Boss*, u32) = (void(*)(Boss*,u32)) 0x205d82c;
    processHits__10BoomBoomW1FUi(this, amount);
}

void MilitaryCheep::onStompKill(StageActor* collidingPlayer) {
    this->FUN_202D094(collidingPlayer, &this->position, 6);
}

void MilitaryCheep::onKill() {
    this->vf574();

    ActorGlobalsHolder::instance()->activeBossController->bossDoneDying = true;
}

void MilitaryCheep::setLookTarget() {
    this->lookTarget.targetPosition.x = this->position.x;
    this->lookTarget.targetPosition.y = this->position.y;
}

void MilitaryCheep::initHitboxCollider() {
    this->hitboxCollider.init(this, &MilitaryCheep::sCollisionInfo);
}

void MilitaryCheep::initModels() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");
}

void MilitaryCheep::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();
}

void MilitaryCheep::initHitsToDeath() {
    this->hitsToDeath = 18;
}

void MilitaryCheep::initHitsToDamage() {
    this->hitsToDamage = 6;
}

u32 MilitaryCheep::init() {
    

    return 1;
}

void MilitaryCheep::beginState_BossState1() {
    this->beginState_DieFumi();
}

void MilitaryCheep::executeState_BossState1() {
    this->executeState_DieFumi();
}

void MilitaryCheep::endState_BossState1() {
    this->endState_DieFumi();
}

void MilitaryCheep::beginState_BossState5() {
    this->beginState_DieFumi();
}

void MilitaryCheep::executeState_BossState5() {
    this->executeState_DieFumi();
}

void MilitaryCheep::endState_BossState5() {
    this->endState_DieFumi();
}

//!-----------------------------------
//! Military Cheep Controller 
//!-----------------------------------

class MilitaryCheepController : public BossController {
public:
    MilitaryCheepController(const ActorBuildInfo* buildInfo);
    virtual ~MilitaryCheepController() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 vf1F4() override;
    u8 vf1FC() override;
    u32 vf204() override;
    StageActor* getTargetBoss() override;
    void spawnCutsceneKamek() override;
};

const Profile MilitaryCheepControllerProfile(&MilitaryCheepController::build, ProfileID::MilitaryCheepController);

Actor* MilitaryCheepController::build(const ActorBuildInfo* buildInfo) {
    return new MilitaryCheepController(buildInfo);
}

MilitaryCheepController::MilitaryCheepController(const ActorBuildInfo* buildInfo)
    : BossController(buildInfo)
{ }

u32 MilitaryCheepController::vf1F4() {
    return 1;
}

u8 MilitaryCheepController::vf1FC() {
    return this->_17CA;
}

u32 MilitaryCheepController::vf204() {
    return 1;
}

StageActor* MilitaryCheepController::getTargetBoss() {
    for (Actor** current = ActorMgr::instance()->actors.start.buffer; current < ActorMgr::instance()->actors.end.buffer; current++) {
        Actor* actor = *current;
        if (actor && actor->getProfileID() == ProfileID::MilitaryCheep) {
            return (MilitaryCheep*) actor;
        }
    }

    return nullptr;
}

void MilitaryCheepController::spawnCutsceneKamek() {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(ProfileID::CutsceneKamek);

    ((CutsceneKamek*) ActorMgr::instance()->create(buildInfo, 0))->doStateChange(&CutsceneKamek::StateID_CutsceneKamekState2);
}
