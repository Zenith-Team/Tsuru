#include "game/actor/stage/stageactor.h"
#include "game/collision/solid/solidontopcollider.h"
#include "game/collision/collidermgr.h"
#include "game/graphics/model/modelnw.h"
#include "log.h"

class JumboRay : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(JumboRay, StageActor);

public:
    JumboRay(const ActorBuildInfo* buildInfo);
    virtual ~JumboRay() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    f32 baseline;
    SolidOnTopCollider collider;
};

const Profile JumboRayProfile(&JumboRay::build, ProfileID::JumboRay);
PROFILE_RESOURCES(ProfileID::JumboRay, Profile::LoadResourcesAt::Course, "star_coin");

JumboRay::JumboRay(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
{ }

Actor* JumboRay::build(const ActorBuildInfo* buildInfo) {
    return new JumboRay(buildInfo);
}

u32 JumboRay::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");
    this->baseline = this->position.y;

    Vec2f points[2] = { Vec2f(-32.0f, 0.0f), Vec2f(32.0f, 0.0f) };
    SolidOnTopCollider::Info collisionInfo = { Vec2f(0.0f, 0.0f), 0, 0, points, 0 };

    this->collider.init(this, collisionInfo, 2);
    this->collider.setType(ColliderBase::Type::Solid);
    ColliderMgr::instance()->add(&this->collider);

    return this->onExecute();
}

u32 JumboRay::onExecute() {
    f32 sin; sead::Mathf::sinCosIdx(&sin, nullptr, fixDeg(this->position.x / 6.0f));

    this->position.x += 1.1f;
    this->position.y = this->baseline + 5.0f * powf(sin, 2.0f) * 16.0f;

    sead::Mathf::sinCosIdx(&sin, nullptr, fixDeg(this->position.x / 3.0f));
    this->rotation.z = fixRad(acosf(1.0f / sqrtf(1.0f + 25.0f / 36.0f * (sin * sin))) * (sin < 0.0f ? -1.0f : 1.0f));

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();

    this->collider.rotation = this->rotation.z;
    this->collider.execute();

    return 1;
}

u32 JumboRay::onDraw() {
    this->model->draw();

    return 1;
}
