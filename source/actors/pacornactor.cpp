#include "game/actor/stage/powerup.h"

class PAcornActor : public Powerup {
public:
    PAcornActor(const ActorBuildInfo* buildInfo);
    virtual ~PAcornActor() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    void vf18C() override;
    void playBlockReleaseUpAnim() override;
    void playBlockReleaseDownAnim() override;
    void playIdleAnim() override;
    void playFloatAnim() override;
    void vf1B4() override;
    u32 vf1C4() override;
    void vf1FC() override;
};

const Profile PAcornActorProfile(&PAcornActor::build, ProfileID::PAcornActor, "PAcornActor", nullptr, 0x4016);
PROFILE_RESOURCES(ProfileID::PAcornActor, "I_musasabi");

PAcornActor::PAcornActor(const ActorBuildInfo* buildInfo)
    : Powerup(buildInfo)
{ }

BaseActor* PAcornActor::build(const ActorBuildInfo* buildInfo) {
    return new PAcornActor(buildInfo);
}

u32 PAcornActor::onCreate() {
    this->_1827 = true;
    this->_1808 = 0;
    this->mModel = ModelWrapper::create("I_musasabi", "I_musasabiP", 1, 1, 0, 0, 0);

    this->FUN_2517f90();
    this->spawnMethod();
    this->updateModel();

    return 1;
}

u32 PAcornActor::onExecute() {
    this->mStates.execute();
    // FUN_0232a958((this->_)._.unk6 + 0x28); //? Possibly ActorScaler related
    this->updateModel();
    this->deleteActorWhenOutOfView(0);
    this->FUN_2518f94();
    this->FUN_25183ac();

    return 1;
}

void PAcornActor::vf18C() {
    this->doStateChange(&StateID_PowerupState1);
}

void PAcornActor::playBlockReleaseUpAnim() {
    this->mModel->playSklAnim("out", 1);
}


void PAcornActor::playBlockReleaseDownAnim() {
    this->mModel->playSklAnim("out3", 3);
}

void PAcornActor::playIdleAnim() {
    this->mModel->playSklAnim("wait", 4);
}

void PAcornActor::playFloatAnim() {
    this->mModel->playSklAnim("wait2", 5);
}

void PAcornActor::vf1B4() {
    this->mModel->playSklAnim("out2", 2);
}

u32 PAcornActor::vf1C4() {
    u32 local;

    if (FUN_25196e8(&local, PowerupStatePAcorn, 1) != 0)
        return FUN_2519580(local, this->_1830);
    else
        return 0;
}

void PAcornActor::vf1FC() {
    this->doStateChange(&StateID_PowerupState1);
}
 