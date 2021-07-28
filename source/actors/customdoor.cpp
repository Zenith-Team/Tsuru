#include "game/actor/doorbase.h"
#include "log.h"

class CustomDoor : public DoorBase {
public:
    CustomDoor(const ActorBuildInfo* buildInfo);
    virtual ~CustomDoor() {};

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    //void ZOrder() override; // broken
    void loadModel() override;
    void initHitboxCollider() override;
    void playOpenDoorAnim() override;
    void playCloseDoorAnim() override;
    //void vf5BC() override; // broken

    static const HitboxCollider::Info sCollisionInfo;
};

const ActorInfo CustomDoorActorInfo = {
    Vec2i(16, -48), Vec2i(0, 24), Vec2i(16, 24), 64, 64, 0, 0, 0
};

const Profile CustomDoorProfile(&CustomDoor::build, ProfileID::CustomDoor, "CustomDoor", &CustomDoorActorInfo, Profile::FlagDontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::CustomDoor, "obj_door");

CustomDoor::CustomDoor(const ActorBuildInfo* buildInfo)
    : DoorBase(buildInfo)
{
    this->_1890 = 0;
    this->_18A0 = 0x1E;
}

BaseActor* CustomDoor::build(const ActorBuildInfo* buildInfo) {
    return new CustomDoor(buildInfo);
}

const HitboxCollider::Info CustomDoor::sCollisionInfo = {
    Vec2f(0.0f, 20.0f), Vec2f(12.0f, 20.0f), HitboxCollider::Rectangle, 3, 0, 1, 0, 0, &DoorBase::collisionCallback
};

void CustomDoor::initHitboxCollider() {
    mHitboxCollider.init(this, &CustomDoor::sCollisionInfo, nullptr);
    this->addHitboxColliders();
}

// Broken override
/*void CustomDoor::ZOrder() {
    // nybble5 checkbox
    if (this->mSettings1 >> 0x1C == 1) this->mPosition.z  = 0xC5228000;
    else this->mPosition.z = 0x42000000;
};*/

void CustomDoor::loadModel() {
    this->mModel = ModelWrapper::create("obj_door", "obj_doorA", 1, 1, 2, 1);
    this->mModel->playSklAnim("obj_doorA", 0);
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = -1.0f;
    sklAnim->setRepeat(false);
}

void CustomDoor::playOpenDoorAnim() {
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = 1.0f;
    sklAnim->reset();
    sklAnim->setRepeat(false);
};

void CustomDoor::playCloseDoorAnim() {
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = -1.0f;
    sklAnim->reset();
    sklAnim->setRepeat(false);
};

// Broken override
/*void CustomDoor::vf5BC() {
    LOG("vf5BC called.");
    return;
}*/
