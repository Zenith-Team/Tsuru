#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "math/functions.h"

class AngryGrrrol : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(AngryGrrrol, Enemy);

public:
    AngryGrrrol(const ActorBuildInfo* buildInfo);
    virtual ~AngryGrrrol() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    
    static HitboxCollider::Info sCollisionInfo;

    ModelWrapper* model;
};

const Profile AngryGrrrolProfile(&AngryGrrrol::build, ProfileID::AngryGrrrol);
PROFILE_RESOURCES(ProfileID::AngryGrrrol, Profile::LoadResourcesAt::Course, "guruguru");

HitboxCollider::Info AngryGrrrol::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &AngryGrrrol::collisionCallback
};

AngryGrrrol::AngryGrrrol(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
{ }

Actor* AngryGrrrol::build(const ActorBuildInfo* buildInfo) {
    return new AngryGrrrol(buildInfo);
}

u32 AngryGrrrol::onCreate() {
    this->model = ModelWrapper::create("guruguru", "guruguru", 0, 0, 1);
    this->model->playTexSrtAnim("guruguru");

    PhysicsMgr::Sensor belowSensor = { -16, 16, -16 };
    PhysicsMgr::Sensor sideSensor = { -16, 16, 16 };
    PhysicsMgr::Sensor aboveSensor = { -16, 16, 16 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sideSensor);

    this->hitboxCollider.init(this, &AngryGrrrol::sCollisionInfo);
    this->addHitboxColliders();

    return this->onExecute();
}

u32 AngryGrrrol::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateAnimations();
    this->model->setScale(this->scale);
    this->model->updateModel();

    Vec2f d2p = this->distanceToPlayer();

    this->speed.x += d2p.x * 0.00025f;

    const f32 maximum = 0.25f * ((this->eventID1 >> 0x4 & 0xF) + 1);

    if (d2p.x > 0.0f && this->speed.x > maximum) {
        this->speed.x = maximum;
    } else if (d2p.x < 0.0f && this->speed.x < -maximum) {
        this->speed.x = -maximum;
    }

    this->rotation.z -= fixDeg(2.0f * this->speed.x);

    this->physicsMgr.processCollisions();
    this->handleSpeed();

    return 1;
}

u32 AngryGrrrol::onDraw() {
    this->model->draw();

    return 1;
}

