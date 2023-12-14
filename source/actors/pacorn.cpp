#include "game/actor/stage/powerup.h"
#include "game/playermgr.h"
#include "game/effect/effect.h"

class PAcorn : public Powerup {
    SEAD_RTTI_OVERRIDE_IMPL(PAcorn, Powerup);

public:
    PAcorn(const ActorBuildInfo* buildInfo);
    virtual ~PAcorn() { }

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

const ActorInfo PAcornActorInfo = { 0, 0, 0x20, 0x200, 0x200, 0x400, 0x400, 0 };
REGISTER_PROFILE(PAcorn, ProfileID::PAcorn, "PAcorn", &PAcornActorInfo, 16406);
PROFILE_RESOURCES(ProfileID::PAcorn, Profile::LoadResourcesAt::Course, "I_musasabi");

PAcorn::PAcorn(const ActorBuildInfo* buildInfo)
    : Powerup(buildInfo)
{ }

u32 PAcorn::onCreate() {
    this->_1827 = true;
    this->_1808 = 0;
    this->model = ModelWrapper::create("I_musasabi", "I_musasabiP", 5);

    this->setupActor();
    this->spawnMethod();
    this->updateModel();

    return 1;
}

u32 PAcorn::onExecute() {
    this->states.execute();
    // FUN_0232a958((this->_)._.unk5 + 0x28); //? Possibly ActorScaler related
    this->updateModel();
    this->offscreenDelete(0);
    this->FUN_2518f94();
    this->FUN_25183ac();

    return 1;
}

void PAcorn::vf18C() {
    this->doStateChange(&StateID_PowerupState1);
}

void PAcorn::playBlockReleaseUpAnim() {
    this->model->playSklAnim("out", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->_1810 = 1;
}

void PAcorn::playBlockReleaseDownAnim() {
    this->model->playSklAnim("out3", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->_1810 = 3;
}

void PAcorn::playIdleAnim() {
    if (this->_1810 == 4)
        return;

    this->model->playSklAnim("wait", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 4;
}

void PAcorn::playFloatAnim() {
    this->model->playSklAnim("wait2", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 5;
}

void PAcorn::vf1B4() {
    this->model->playSklAnim("out2", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 2;
}

u32 PAcorn::vf1C4() {
    u32 local;

    if (this->FUN_25196e8(&local, PlayerBase::PowerupState::PAcorn, 1) != 0)
        return this->FUN_2519580(local, this->_1830);

    return 0;
}

void PAcorn::vf1FC() {
    this->doStateChange(&StateID_PowerupState1);
}
