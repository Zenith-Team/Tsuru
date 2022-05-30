#include "game/actor/stage/enemy.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
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

    void updateModel();
    
    static HitboxCollider::Info sCollisionInfo;
    static const PhysicsMgr::Sensor bottomSensor;//, sideSensor, topSensor;

    ModelWrapper* model;
};

const Profile AngryGrrrolProfile(&AngryGrrrol::build, ProfileID::AngryGrrrol);
PROFILE_RESOURCES(ProfileID::AngryGrrrol, Profile::LoadResourcesAt_Course, "guruguru");

HitboxCollider::Info AngryGrrrol::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &AngryGrrrol::collisionCallback
};

const PhysicsMgr::Sensor AngryGrrrol::bottomSensor = {
    16.0f, 16.0f, 8.0f
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
    this->updateModel();


    this->hitboxCollider.init(this, &AngryGrrrol::sCollisionInfo);
    this->addHitboxColliders();

    return 1;
}

u32 AngryGrrrol::onExecute() {
    this->updateModel();

    Vec2f d2p = this->distanceToPlayer();

    this->speed.x += d2p.x * 0.00025f;

    const f32 maximum = 0.25f * ((this->eventID1 >> 0x4 & 0xF) + 1);

    if (d2p.x > 0.0f && this->speed.x > maximum) {
        this->speed.x = maximum;
    } else if (d2p.x < 0.0f && this->speed.x < -maximum) {
        this->speed.x = -maximum;
    }

    this->rotation.z -= fixDeg(2.0f * this->speed.x);

    this->handleSpeed();

    return 1;
}

u32 AngryGrrrol::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

void AngryGrrrol::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateAnimations();
    this->model->setScale(this->scale);
    this->model->updateModel();
}
