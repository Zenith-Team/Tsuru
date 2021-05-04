#include "actor/actor.h"

#include "movementhandler.h"
#include "model.h"
#include "drawmgr.h"
#include "effect.h"
#include "sound.h"
#include "eventmgr.h"
#include "level.h"

class TimeClock : public Actor {
public:
    TimeClock(const ActorBuildInfo* buildInfo);
    virtual ~TimeClock() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();
    void collect();

    static void collisionCallback(ActiveCollider* acSelf, ActiveCollider* acOther);

    ModelWrapper* model;
    MovementHandler movementHandler;
    u8 rotationDirection;

    static const ActiveCollider::Info collisionInfo;
};

const Profile timeClockProfile(&TimeClock::build, ProfileId::Sprite555, "TimeClock", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite555, "star_coin");

const ActiveCollider::Info TimeClock::collisionInfo = { Vec2(0.0f, -3.0f), Vec2(12.0f, 15.0f), 0, 5, 0, 0x824F, 0x20208, 0, &TimeClock::collisionCallback };


TimeClock::TimeClock(const ActorBuildInfo* buildInfo) : Actor(buildInfo) { }

ActorBase* TimeClock::build(const ActorBuildInfo* buildInfo) {
    return new TimeClock(buildInfo);
}


u32 TimeClock::onCreate() {
    rotationDirection = settings1 & 3;
    model = ModelWrapper::create("star_coin", (settings1 & 0x10) ? "star_coinB" : "star_coinA");

    aCollider.init(this, &TimeClock::collisionInfo, 0);
    addActiveColliders();

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    updateModel();

    return 1;
}

u32 TimeClock::onExecute() {
    static const u32 rotationSpeed = 0x3FD27D2;

    movementHandler.execute();
    position = movementHandler.position;

    switch (rotationDirection) {
    case 0: rotation.y -= rotationSpeed; break;
    case 1: rotation.y += rotationSpeed; break;
    case 2: rotation.x += rotationSpeed; break;
    case 3: rotation.x -= rotationSpeed; break;
    }

    updateModel();

    return 1;
}

u32 TimeClock::onDraw() {
    DrawMgr::instance->drawModel(model);
    return 1;
}


void TimeClock::updateModel() {
    model->updateAnimations();

    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->updateModel();
}

void TimeClock::collect() {
    Vec3 effectPos(position.x, position.y - 18.0f, 4500.0f);

    Effect::spawn(100, &effectPos, nullptr, nullptr);
    LevelTimer::instance->addTime(10);
    PlaySound("SE_OBJ_DDOOR_OPEN", position);

    if (eventId1)
        EventMgr::instance->set(eventId1 - 1, 0, true);

    isDeleted = true;
}


void TimeClock::collisionCallback(ActiveCollider* acSelf, ActiveCollider* acOther) {
    reinterpret_cast<TimeClock*>(acSelf->owner)->collect();
}
