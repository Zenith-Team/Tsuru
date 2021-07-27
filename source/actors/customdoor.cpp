#include "game/actor/doorbase.h"

class CustomDoor : public DoorBase {
public:
    CustomDoor(const ActorBuildInfo* buildInfo);
    virtual ~CustomDoor() {};

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    void loadModel() override;
    void initHitboxCollider() override;
    void vf594() override;
    void vf5A4() override;

    static const HitboxCollider::Info sHCInfo;
};

const ActorInfo CustomDoorActorInfo = {
    Vec2i(10, -48), Vec2i(0, 18), Vec2i(10, 18), 40, 40, 0, 0, 0
};
const Profile CustomDoorProfile(&CustomDoor::build, ProfileID::CustomDoor, "CustomDoor", &CustomDoorActorInfo, 2);
PROFILE_RESOURCES(ProfileID::CustomDoor, "obj_door");

CustomDoor::CustomDoor(const ActorBuildInfo* buildInfo)
    : DoorBase(buildInfo)
    {}
BaseActor* CustomDoor::build(const ActorBuildInfo* buildInfo) {
    return new CustomDoor(buildInfo);
}

const HitboxCollider::Info CustomDoor::sHCInfo = {
    Vec2f(0.0f, 20.0f), Vec2f(12.0f, 20.0f), HitboxCollider::Rectangle, 3, 0, 1, 0, 0, &DoorBase::colliderCallback
};

void CustomDoor::initHitboxCollider() {
    mHitboxCollider.init(this, &CustomDoor::sHCInfo, nullptr);
    this->addHitboxColliders();
}

void CustomDoor::loadModel() {
    this->mModel = ModelWrapper::create("obj_door", "obj_doorA", 1, 1, 2, 1);
    this->mModel->playSklAnim("obj_doorA", 0);
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = -1.0f;
    sklAnim->setRepeat(false);
}

// open door anim
void CustomDoor::vf594() {
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = 1.0f;
    sklAnim->reset();
    sklAnim->setRepeat(false);
};

// close door anim
void CustomDoor::vf5A4() {
    SkeletalAnimation* sklAnim = this->mModel->mSklAnims[0];
    sklAnim->mSpeed = -1.0f;
    sklAnim->reset();
    sklAnim->setRepeat(false);
};
