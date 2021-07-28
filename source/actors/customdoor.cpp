#include "game/actor/doorbase.h"

class CustomDoor : public DoorBase {
public:
    CustomDoor(const ActorBuildInfo* buildInfo);
    virtual ~CustomDoor() {};

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    void ZOrder() override;
    void loadModel() override;
    void initHitboxCollider() override;
    void playOpenDoorAnim() override;
    void playCloseDoorAnim() override;
    void vf5BC() override;

    static const HitboxCollider::Info sCollisionInfo;
};

const ActorInfo CustomDoorActorInfo = {
    Vec2i(10, -48), Vec2i(0, 18), Vec2i(10, 18), 40, 40, 0, 0, 0
};
const Profile CustomDoorProfile(&CustomDoor::build, ProfileID::CustomDoor, "CustomDoor", &CustomDoorActorInfo, 2);
PROFILE_RESOURCES(ProfileID::CustomDoor, "obj_door");

CustomDoor::CustomDoor(const ActorBuildInfo* buildInfo)
    : DoorBase(buildInfo)
{
    this->_1890 = 0;
    this->_18A0 = 0x1E;
}

BaseActor* CustomDoor::build(const ActorBuildInfo* buildInfo) {
    return new CustomDoor(buildInfo);
};

const HitboxCollider::Info CustomDoor::sCollisionInfo = {
    Vec2f(0.0f, 20.0f), Vec2f(12.0f, 20.0f), HitboxCollider::Rectangle, 3, 0, 1, 0, 0, &DoorBase::collisionCallback
};

void CustomDoor::initHitboxCollider() {
    mHitboxCollider.init(this, &CustomDoor::sCollisionInfo, nullptr);
    this->addHitboxColliders();
};

void CustomDoor::ZOrder() {
    // nybble5 checkbox
    if (this->mSettings1 >> 0x1C == 1) this->mPosition.z  = 0xC5228000;
    else this->mPosition.z = 0x42000000;
};

void CustomDoor::vf5BC() {
    //SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    //sklAnim->mSpeed = 0.0f;
    //sklAnim->mFrame = 0.0f;
    //sklAnim->mFlags |= Animation::FlagUnk2;
};

void CustomDoor::loadModel() {
    this->mModel = ModelWrapper::create("obj_door", "obj_doorA", 1, 1, 2, 1);
    this->mModel->playSklAnim("obj_doorA", 0);
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = -1.0f;
    sklAnim->setRepeat(false);
};

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
