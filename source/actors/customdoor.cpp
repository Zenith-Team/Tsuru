#include <game/actor/stage/doorbase.h>
#include <log.h>

class CustomDoor : public DoorBase {
    SEAD_RTTI_OVERRIDE_IMPL(CustomDoor, DoorBase)

public:
    CustomDoor(const ActorBuildInfo* buildInfo);
    virtual ~CustomDoor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

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

const Profile CustomDoorProfile(&CustomDoor::build, ProfileID::CustomDoor, "CustomDoor", &CustomDoorActorInfo, Profile::Flag_DontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::CustomDoor, "obj_door");

CustomDoor::CustomDoor(const ActorBuildInfo* buildInfo)
    : DoorBase(buildInfo)
{
    this->_1890 = 0;
    this->_18A0 = 0x1E;
}

Actor* CustomDoor::build(const ActorBuildInfo* buildInfo) {
    return new CustomDoor(buildInfo);
}

const HitboxCollider::Info CustomDoor::sCollisionInfo = {
    Vec2f(0.0f, 20.0f), Vec2f(12.0f, 20.0f), HitboxCollider::HitboxShape_Rectangle, 3, 0, 1, 0, 0, &DoorBase::collisionCallback
};

void CustomDoor::initHitboxCollider() {
    hitboxCollider.init(this, &CustomDoor::sCollisionInfo, nullptr);
    this->addHitboxColliders();
}

// Broken override
/*void CustomDoor::ZOrder() {
    // nybble5 checkbox
    if (this->settings1 >> 0x1C == 1) this->position.z  = 0xC5228000;
    else this->position.z = 0x42000000;
};*/

void CustomDoor::loadModel() {
    this->model = ModelWrapper::create("obj_door", "obj_doorA", 1, 1, 2, 1);
    this->model->playSklAnim("obj_doorA", 0);
    SkeletalAnimation* sklAnim = this->model->sklAnims[0];
    sklAnim->speed = -1.0f;
    sklAnim->shouldLoop(false);
}

void CustomDoor::playOpenDoorAnim() {
    SkeletalAnimation* sklAnim = this->model->sklAnims[0];
    sklAnim->speed = 1.0f;
    sklAnim->reset();
    sklAnim->shouldLoop(false);
};

void CustomDoor::playCloseDoorAnim() {
    SkeletalAnimation* sklAnim = this->model->sklAnims[0];
    sklAnim->speed = -1.0f;
    sklAnim->reset();
    sklAnim->shouldLoop(false);
};

// Broken override
/*void CustomDoor::vf5BC() {
    LOG("vf5BC called.");
    return;
}*/
