#include "actor/stageactor.h"

#include "movementhandler.h"
#include "model.h"
#include "drawmgr.h"
#include "effect.h"
#include "sound.h"
#include "eventmgr.h"

class FakeStarCoin : public StageActor {
public:
    FakeStarCoin(const ActorBuildInfo* buildInfo);
    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();
    void collect();

    static void collisionCallback(HitboxCollider* acSelf, HitboxCollider* acOther);

    ModelWrapper* model;
    MovementHandler movementHandler;
    
    u8 rotationDirection;

    static const HitboxCollider::Info collisionInfo;
};

const Profile fakeStarCoinProfile(&FakeStarCoin::build, Profile::spriteToProfileList[449], "FakeStarCoin", nullptr, 0);
PROFILE_RESOURCES(Profile::spriteToProfileList[449], "star_coin");

const HitboxCollider::Info FakeStarCoin::collisionInfo = { Vec2(0.0f, -3.0f), Vec2(12.0f, 15.0f), 0, 5, 0, 0x824F, 0x20208, 0, &FakeStarCoin::collisionCallback };

FakeStarCoin::FakeStarCoin(const ActorBuildInfo* buildInfo) : StageActor(buildInfo) { }

BaseActor* FakeStarCoin::build(const ActorBuildInfo* buildInfo) {
    return new FakeStarCoin(buildInfo);
}


u32 FakeStarCoin::onCreate() {
    rotationDirection = settings1 & 3;
    model = ModelWrapper::create("star_coin", (settings1 & 0x10) ? "star_coinB" : "star_coinA");

    aCollider.init(this, &FakeStarCoin::collisionInfo, 0);
    addHitboxColliders();

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    updateModel();

    return 1;
}

u32 FakeStarCoin::onExecute() {
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

u32 FakeStarCoin::onDraw() {
    DrawMgr::instance->drawModel(model);
    return 1;
}


void FakeStarCoin::updateModel() {
    model->updateAnimations();

    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->updateModel();
}

void FakeStarCoin::collect() {
    Vec3 effectPos(position.x, position.y - 18.0f, 4500.0f);

    Effect::spawn(921, &effectPos, nullptr, nullptr);
    PlaySound("SE_OBJ_DDOOR_OPEN", position);

    if (eventId1)
        EventMgr::instance->set(eventId1 - 1, 0, true);

    isDeleted = true;
}


void FakeStarCoin::collisionCallback(HitboxCollider* acSelf, HitboxCollider* acOther) {
    reinterpret_cast<FakeStarCoin*>(acSelf->owner)->collect();
}
