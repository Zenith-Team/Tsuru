#include "actor/actor.h"

#include "model.h"
#include "drawmgr.h"
#include "effect.h"
#include "sound.h"


class FakeCheckpoint : public Actor {
public:
    FakeCheckpoint(const ActorBuildInfo* buildInfo);
    
    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void touch();

    void updateModel();

    static void collisionCallback(ActiveCollider* acSelf, ActiveCollider* acOther);

    ModelWrapper* model;

    static const ActiveCollider::Info collisionInfo;
};

const Profile FakeCheckpointProfile(&FakeCheckpoint::build, ProfileId::Sprite312, "FakeCheckpoint", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite312, "middle_flag");

const ActiveCollider::Info FakeCheckpoint::collisionInfo = { Vec2(0.0f, -3.0f), Vec2(12.0f, 15.0f), 0, 5, 0, 0x824F, 0x20208, 0, &FakeCheckpoint::collisionCallback };

FakeCheckpoint::FakeCheckpoint(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo) { }

ActorBase* FakeCheckpoint::build(const ActorBuildInfo* buildInfo) {
    return new FakeCheckpoint(buildInfo);
}

u32 FakeCheckpoint::onCreate() {
    model = ModelWrapper::create("middle_flag", "middle_flag", 4);
    model->playSklAnim("wait", 0);

    aCollider.init(this, &FakeCheckpoint::collisionInfo, 0);
    addActiveColliders();

    for (u32 i = 0; i <= 64; i += 1) {
        rotation.y += 0x1000000;
    }

    updateModel();

    return 1;
}

u32 FakeCheckpoint::onExecute() {
    updateModel();

    return 1;
}

u32 FakeCheckpoint::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void FakeCheckpoint::updateModel() {
    model->updateAnimations();

    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->updateModel();
}

void FakeCheckpoint::touch() {
    Vec3 effectPos(position.x, position.y, 4500.0f);

    Effect::spawn(921, &effectPos, nullptr, nullptr);
    PlaySound("SE_OBJ_DOOR_OPEN", position);

    isDeleted = true;
}

void FakeCheckpoint::collisionCallback(ActiveCollider* acSelf, ActiveCollider* acOther) {
    reinterpret_cast<FakeCheckpoint*>(acSelf->owner)->touch();
}
