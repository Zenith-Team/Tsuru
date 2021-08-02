#include "game/actor/stage/powerup.h"

class CustomPowerup : public Powerup {
public:
    CustomPowerup(const ActorBuildInfo* buildInfo);
    virtual ~CustomPowerup() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    void vf18C() override;
    void playBlockReleaseUpAnim() override;
    void playBlockReleaseDownAnim() override;
    void playIdleAnim() override;
    void playFloatAnim() override;
    void vf1B4() override;
    u32 vf1C4() override;  //? We will make this point to Mushroom::vf1C4 in the symbols until the function has been figured out
    void vf1FC() override;
};

const Profile CustomPowerupProfile(&CustomPowerup::build, ProfileID::CustomPowerup, "CustomPowerup", nullptr, 0);
PROFILE_RESOURCES(ProfileID::CustomPowerup, "I_kinoko");

CustomPowerup::CustomPowerup(const ActorBuildInfo* buildInfo)
    : Powerup(buildInfo)
{ }

BaseActor* CustomPowerup::build(const ActorBuildInfo* buildInfo) {
    return new CustomPowerup(buildInfo);
}

u32 CustomPowerup::onCreate() {
    this->_1827 = true;
    this->_1808 = 0;
    this->mModel = ModelWrapper::create("I_kinoko", "I_kinoko", 1, 1, 0, 0, 0);

    this->FUN_2517f90();
    this->spawnMethod();
    this->updateModel();

    return 1;
}

u32 CustomPowerup::onExecute() {
    this->mStates.execute();
    // FUN_0232a958((this->_)._.unk6 + 0x28); //? Possibly ActorScaler related
    this->updateModel();
    this->deleteActorWhenOutOfView(0);
    this->FUN_2518f94();
    this->FUN_25183ac();

    return 1;
}

void CustomPowerup::vf18C() {
    doStateChange(&StateID_PowerupState1);
}

void CustomPowerup::playBlockReleaseUpAnim() {
    mModel->playSklAnim("out", 1);
}


void CustomPowerup::playBlockReleaseDownAnim() {
    mModel->playSklAnim("out3", 3);
}

void CustomPowerup::playIdleAnim() {
    mModel->playSklAnim("wait", 4);
}

void CustomPowerup::playFloatAnim() {
    mModel->playSklAnim("wait2", 5);
}

void CustomPowerup::vf1B4() {
    mModel->playSklAnim("out2", 2);
}

void CustomPowerup::vf1FC() {
    doStateChange(&StateID_PowerupState1);
}
 