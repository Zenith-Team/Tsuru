#include "game/actor/stage/stageactor.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/rectcollider.h"
#include "log.h"

class Solid : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(Solid, StageActor);

public:
    Solid(const ActorBuildInfo* buildInfo);
    virtual ~Solid() { }

    u32 onCreate();
    u32 onExecute();

    RectCollider collider;
};

REGISTER_PROFILE(Solid, ProfileID::Solid);

Solid::Solid(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

u32 Solid::onCreate() {

    PolygonCollider::Info info = {
        Vec2f(0.0f, 0.0f),
        0.0f, 0.0f,
        Vec2f(
            static_cast<f32>((this->eventID1 >> 0x4 & 0xF)+1) * ((this->eventID1 & 0xF) == 0 ? 1.0f : -1.0f),
            static_cast<f32>((this->eventID2 >> 0x4 & 0xF)+1) * ((this->eventID2 & 0xF) == 0 ? 1.0f : -1.0f)
        ),
        Vec2f(
            static_cast<f32>((this->settings1 >> 0x1C & 0xF)+1) * ((this->settings1 >> 0x18 & 0xF) == 0 ? 1.0f : -1.0f),
            static_cast<f32>((this->settings1 >> 0x14 & 0xF)+1) * ((this->settings1 >> 0x10 & 0xF) == 0 ? 1.0f : -1.0f)
        ),
        fixDeg(static_cast<f32>(this->settings1 >> 0xC & 0xF) * 11.25f)
    };

    this->collider.init(this, info);
    ColliderMgr::instance()->add(&this->collider);

    return 1;
}

u32 Solid::onExecute() {
    this->collider.execute();

    return 1;
}
