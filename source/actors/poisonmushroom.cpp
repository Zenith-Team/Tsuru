#include "game/actor/stage/powerup.h"
#include "game/actor/stage/player.h"
#include "game/playermgr.h"
#include "game/effect/effect.h"

class PoisonMushroom : public Powerup {
    SEAD_RTTI_OVERRIDE_IMPL(PoisonMushroom, Powerup);

public:
    PoisonMushroom(const ActorBuildInfo* buildInfo);
    virtual ~PoisonMushroom() { }

    u32 onCreate() override;
    u32 onExecute() override;

    void vf18C() override;
    void playBlockReleaseUpAnim() override;
    void playBlockReleaseDownAnim() override;
    void playIdleAnim() override;
    void playFloatAnim() override;
    void vf1B4() override;
    void initHitboxes() override;
    u32 vf1C4() override;
    void vf1FC() override;

    static const HitboxCollider::Info collisionInfo;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
};

REGISTER_PROFILE(PoisonMushroom, ProfileID::PoisonMushroom, "PoisonMushroom", nullptr, 16406);
PROFILE_RESOURCES(ProfileID::PoisonMushroom, Profile::LoadResourcesAt::Course, "I_kinxkx");

const HitboxCollider::Info PoisonMushroom::collisionInfo = {
    Vec2f(0.0f, 7.0f), Vec2f(7.0f, 7.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x42F, 0x420000, 0, &PoisonMushroom::collisionCallback
};

PoisonMushroom::PoisonMushroom(const ActorBuildInfo* buildInfo)
    : Powerup(buildInfo)
{ }

u32 PoisonMushroom::onCreate() {
    this->_1827 = true;
    this->_1808 = 0;
    this->model = ModelWrapper::create("I_kinxkx", "I_kinxkx", 5); // Funny

    this->setupActor();
    this->spawnMethod();
    this->updateModel();

    return 1;
}

u32 PoisonMushroom::onExecute() {
    this->states.execute();
    this->updateModel();
    this->offscreenDelete(0);
    this->FUN_2518f94();
    this->FUN_25183ac();

    return 1;
}

void PoisonMushroom::vf18C() {
    this->doStateChange(&StateID_PowerupState1);
}

void PoisonMushroom::playBlockReleaseUpAnim() {
    this->model->playSklAnim("out", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->_1810 = 1;
}

void PoisonMushroom::playBlockReleaseDownAnim() {
    this->model->playSklAnim("out3", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(false);
    this->_1810 = 3;
}

void PoisonMushroom::playIdleAnim() {
    if (this->_1810 == 4)
        return;
    this->model->playSklAnim("wait", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 4;
}

void PoisonMushroom::playFloatAnim() {
    this->model->playSklAnim("wait2", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 5;
}

void PoisonMushroom::vf1B4() {
    this->model->playSklAnim("out2", 0);
    this->model->sklAnims[0]->frameCtrl.shouldLoop(true);
    this->_1810 = 2;
}

void PoisonMushroom::initHitboxes() {
    this->hitboxCollider.init(this, &PoisonMushroom::collisionInfo);
    this->_18AC.init(this, &PoisonMushroom::collisionInfo);
}

u32 PoisonMushroom::vf1C4() {
    return 0;
}

void PoisonMushroom::vf1FC() {
    this->doStateChange(&StateID_PowerupState1);
}

void PoisonMushroom::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type == StageActor::Type::Player) {
        ((Player*)hcOther->owner)->doDamage(hcSelf->owner, PlayerBase::DamageType::Poison);
    }
}
