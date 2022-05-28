#include "tsuru/actor/bosswrapper.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "game/actor/actormgr.h"
#include "game/task/coursetask.h"
#include "game/actor/stage/cutscenekamek.h"
#include "log.h"

class MilitaryCheep : public BossWrapper<18> {
    SEAD_RTTI_OVERRIDE_IMPL(MilitaryCheep, Boss)

public:
    MilitaryCheep(const ActorBuildInfo* buildInfo);
    virtual ~MilitaryCheep() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
    u32 onDraw() override;
    
    void startCutscene() override;
    void endCutscene() override;
    void initHitboxCollider() override;
    void initModels() override;
    void updateModel() override;

    static const HitboxCollider::Info sCollisionInfo;

    ModelWrapper* model;
};

const Profile MilitaryCheepProfile(&MilitaryCheep::build, ProfileID::MilitaryCheep);
PROFILE_RESOURCES(ProfileID::MilitaryCheep, Profile::LoadResourcesAt_Course, "star_coin");

const HitboxCollider::Info MilitaryCheep::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

Actor* MilitaryCheep::build(const ActorBuildInfo* buildInfo) {
    return new MilitaryCheep(buildInfo);
}

MilitaryCheep::MilitaryCheep(const ActorBuildInfo* buildInfo)
    : BossWrapper<18>(buildInfo)
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

void MilitaryCheep::startCutscene() {
    LOG("start cutscene");
    this->isCutscene = true;
}

void MilitaryCheep::endCutscene() {
    LOG("end cutscene");
    this->isCutscene = false;
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

//!-----------------------------------
//! Military Cheep Controller 
//!-----------------------------------

class MilitaryCheepController : public BossControllerWrapper<ProfileID::MilitaryCheep> {
public:
    MilitaryCheepController(const ActorBuildInfo* buildInfo);
    virtual ~MilitaryCheepController() { }

    static Actor* build(const ActorBuildInfo* buildInfo);
};

const Profile MilitaryCheepControllerProfile(&MilitaryCheepController::build, ProfileID::MilitaryCheepController);

Actor* MilitaryCheepController::build(const ActorBuildInfo* buildInfo) {
    return new MilitaryCheepController(buildInfo);
}

MilitaryCheepController::MilitaryCheepController(const ActorBuildInfo* buildInfo)
    : BossControllerWrapper<ProfileID::MilitaryCheep>(buildInfo)
{ }
