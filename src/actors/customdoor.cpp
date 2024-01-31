#include "game/actor/stage/doorbase.h"
#include "log.h"

class CustomDoor : public DoorBase {
    SEAD_RTTI_OVERRIDE(CustomDoor, DoorBase);

public:
    CustomDoor(const ActorBuildInfo* buildInfo);
    virtual ~CustomDoor() { }

    void loadModel() override;
    void initHitboxCollider() override;
    void playOpenDoorAnim() override;
    void playCloseDoorAnim() override;

    static const HitboxCollider::Info sCollisionInfo;
};

const ActorInfo CustomDoorActorInfo = {
    sead::Vector2i(16, -48), sead::Vector2i(0, 24), sead::Vector2i(16, 24), 64, 64, 0, 0, 0
};

REGISTER_PROFILE(CustomDoor, ProfileID::CustomDoor, "CustomDoor", &CustomDoorActorInfo, Profile::Flags::DontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::CustomDoor, Profile::LoadResourcesAt::Course, "obj_door");

CustomDoor::CustomDoor(const ActorBuildInfo* buildInfo)
    : DoorBase(buildInfo)
{
    this->_1890 = 0;
    this->_18A0 = 0x1E;
}

const HitboxCollider::Info CustomDoor::sCollisionInfo = {
    sead::Vector2f(0.0f, 20.0f), sead::Vector2f(12.0f, 20.0f), HitboxCollider::Shape::Rectangle, 3, 0, 1, 0, 0, &DoorBase::collisionCallback
};

void CustomDoor::initHitboxCollider() {
    hitboxCollider.init(this, &CustomDoor::sCollisionInfo, nullptr);
    this->addHitboxColliders();
}

void CustomDoor::loadModel() {
    this->model = ModelWrapper::create("obj_door", "obj_doorA", 1, 1, 2, 1);
    this->model->playSklAnim("obj_doorA", 0);
    SkeletalAnimation* sklAnim = this->model->sklAnims[0];
    sklAnim->frameCtrl.speed = -1.0f;
    sklAnim->frameCtrl.shouldLoop(false);
}

void CustomDoor::playOpenDoorAnim() {
    SkeletalAnimation* sklAnim = this->model->sklAnims[0];
    sklAnim->frameCtrl.speed = 1.0f;
    sklAnim->frameCtrl.reset();
    sklAnim->frameCtrl.shouldLoop(false);
};

void CustomDoor::playCloseDoorAnim() {
    SkeletalAnimation* sklAnim = this->model->sklAnims[0];
    sklAnim->frameCtrl.speed = -1.0f;
    sklAnim->frameCtrl.reset();
    sklAnim->frameCtrl.shouldLoop(false);
};
