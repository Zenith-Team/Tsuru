#include "game/actor/stage/stageactor.h"
#include "game/graphics/model/platformmodel.h"
#include "game/collision/solid/polylinecollider.h"
#include "game/collision/collidermgr.h"
#include "game/eventmgr.h"
#include "game/movementhandler.h"
#include "tsuru/utils.h"
#include "tsuru/log.h"

class OneWayPlatform : public StageActor {
    SEAD_RTTI_OVERRIDE(OneWayPlatform, StageActor);

public:
    OneWayPlatform(const ActorBuildInfo* buildinfo);
    virtual ~OneWayPlatform() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    f32 startrotation;
    f32 endrotation;

    PlatformModel platform;
    PolylineCollider collider;
    MovementHandler movementHandler;

};

REGISTER_PROFILE(OneWayPlatform, ProfileID::OneWayPlatform);
PROFILE_RESOURCES(ProfileID::OneWayPlatform, Profile::LoadResourcesAt::Course, "lift_han_wood", "lift_han_stone", "lift_kinoko_yoko", "lift_han_spin", "lift_kinoko_shiso", "lift_han_sky");

OneWayPlatform::OneWayPlatform(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , platform()
    , collider()
    , startrotation()
    , endrotation()
    , movementHandler()
{ }

u32 OneWayPlatform::onCreate() {
    platform.create((settings1 >> 0x18 & 0xF), (settings1 >> 0x1c & 0xF));

    if (platform.width < 2) {
        platform.width = 2;   
    }

    platform.position = this->position;

    sead::Vector2f points[2] = { sead::Vector2f(4.0 - platform.width * 8.0, 8.0), sead::Vector2f(-4.0 + platform.width * 8.0, 8.0) };

	PolylineCollider::Info collisionInfo = { sead::Vector2f(0.0f, 0.0f), 0, 0, points, 0 };

    platform._A0 = sead::Vector3f(0.0f, 0.0f, 0.0f);

    this->collider.init(this, collisionInfo, 2);
    this->collider.setType(ColliderBase::Type::Solid);
    ColliderMgr::instance()->add(&this->collider);
    
    u32 direction = settings1 >> 0x14 & 0xF;
    
    if (direction == 0) { // UP
        this->startrotation = 0.0f;
        this->endrotation = 180.0f;
        platform.rotation.x = sead::Mathf::deg2idx(this->startrotation);
        platform.position.x = this->position.x - (platform.width*16)/2;
    }
    else if (direction == 1) { // DOWN
        this->startrotation = 180.0f;
        this->endrotation = 0.0f;
        platform.rotation.x = sead::Mathf::deg2idx(this->startrotation);
        platform.position.x = this->position.x - (platform.width*16)/2;
    }
    else if (direction == 2) { // RIGHT
        this->startrotation = 90.0f;
        this->endrotation = 270.0f;
        platform.rotation.z = sead::Mathf::deg2idx(this->startrotation);
    }
    else if (direction == 3) { // LEFT
        this->startrotation = 270.0f;
        this->endrotation = 90.0f;
        platform.rotation.z = sead::Mathf::deg2idx(this->startrotation);
    }

    platform.update(platform.position, platform.width * 16.0);

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF);
    this->movementHandler.link(this->position, movementMask, this->movementID);
    
    return this->onExecute();
}

u32 OneWayPlatform::onExecute() {

    u32 direction = settings1 >> 0x14 & 0xF;

    this->movementHandler.execute();

    this->position = this->movementHandler.position;

    if (EventMgr::instance()->isActive(this->eventID1 - 1)) {
        if (direction == 0 || direction == 1) {
            platform.rotation.x = sead::Mathf::deg2idx(this->endrotation);
        }
        else {
            platform.rotation.z = sead::Mathf::deg2idx(this->endrotation);
        }
    }
    else {
        if (direction == 0 || direction == 1) {
            platform.rotation.x = sead::Mathf::deg2idx(this->startrotation);
        }
        else {
            platform.rotation.z = sead::Mathf::deg2idx(this->startrotation);
        }
    }
    
    if (direction == 0 || direction == 1) {
        this->collider.rotation = platform.rotation.x;
        platform.position.x = this->position.x - (platform.width*16)/2;
    }
    else {
        this->collider.rotation = platform.rotation.z;
        platform.position.x = this->position.x - (platform.width*16)/2;
    }

    platform.position.y = this->position.y;

    this->collider.execute();
    platform.update(platform.position, platform.width * 16.0);
    return 1;
}

u32 OneWayPlatform::onDraw() {
    platform.draw();
    return 1;
}
