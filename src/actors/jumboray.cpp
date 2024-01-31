#include "game/actor/stage/stageactor.h"
#include "game/collision/solid/polylinecollider.h"
#include "game/collision/collidermgr.h"
#include "game/graphics/model/modelnw.h"
#include "log.h"

class JumboRay : public StageActor {
    SEAD_RTTI_OVERRIDE(JumboRay, StageActor);

public:
    JumboRay(const ActorBuildInfo* buildInfo);
    virtual ~JumboRay() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    f32 baseline;
    PolylineCollider collider;
};

REGISTER_PROFILE(JumboRay, ProfileID::JumboRay);
PROFILE_RESOURCES(ProfileID::JumboRay, Profile::LoadResourcesAt::Course, "star_coin");

JumboRay::JumboRay(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
{ }

u32 JumboRay::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");
    this->baseline = this->position.y;

    sead::Vector2f points[2] = { sead::Vector2f(-32.0f, 0.0f), sead::Vector2f(32.0f, 0.0f) };
    PolylineCollider::Info collisionInfo = { sead::Vector2f(0.0f, 0.0f), 0, 0, points, 0 };

    this->collider.init(this, collisionInfo, 2);
    this->collider.setType(ColliderBase::Type::Solid);
    ColliderMgr::instance()->add(&this->collider);

    return this->onExecute();
}

u32 JumboRay::onExecute() {
    f32 sin; sead::Mathf::sinCosIdx(&sin, nullptr, sead::Mathf::deg2idx(this->position.x / 6.0f));

    this->position.x += 1.1f;
    this->position.y = this->baseline + 5.0f * powf(sin, 2.0f) * 16.0f;

    sead::Mathf::sinCosIdx(&sin, nullptr, sead::Mathf::deg2idx(this->position.x / 3.0f));
    this->rotation.z = sead::Mathf::rad2idx(acosf(1.0f / sqrtf(1.0f + 25.0f / 36.0f * (sin * sin))) * (sin < 0.0f ? -1.0f : 1.0f));

    sead::Matrix34f mtx;
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
