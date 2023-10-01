#include "game/actor/actormgr.h"
#include "tsuru/actor/blockwrapper.h"

class HammerBlock : public BlockWrapper {
    SEAD_RTTI_OVERRIDE_IMPL(HammerBlock, BlockWrapper);

public:
    HammerBlock(const ActorBuildInfo* buildInfo);
    virtual ~HammerBlock() { }

    u32 onCreate() override;

    void spawnItemUp() override;
    void spawnItemDown() override;

    void spawnPowerup(bool down);

    void beginState_Used() override;
};

const ActorInfo HammerBlockActorInfo = { Vec2i(8, -16), Vec2i(8, -8), Vec2i(0x100, 0x100), 0x0, 0x0, 0x0, 0x0, 0x8 };
REGISTER_PROFILE(HammerBlock, ProfileID::HammerBlock, "HammerBlock", &HammerBlockActorInfo, 0x1002);
PROFILE_RESOURCES(ProfileID::HammerBlock, Profile::LoadResourcesAt::Course, "I_hmrflower");

HammerBlock::HammerBlock(const ActorBuildInfo* buildInfo)
    : BlockWrapper(buildInfo)
{ }

u32 HammerBlock::onCreate() {
    if (!BlockWrapper::init()) {
        return 2;
    }

    this->tileId = 49; // Question Block

    if (this->stateType == BlockWrapper::StateType::UsedBlock) {
        this->doStateChange(&HammerBlock::StateID_Used);
    }

    return this->onExecute();
}

void HammerBlock::spawnItemUp() {
    this->spawnPowerup(false);
}

void HammerBlock::spawnItemDown() {
    this->spawnPowerup(true);
}

void HammerBlock::spawnPowerup(bool down) {
    ActorBuildInfo buildInfo = { 0 };

    switch (this->eventID1 >> 0x4 & 0xF) {
        default:
        case 0: buildInfo.profile = Profile::get(ProfileID::HammerFlower); break;
    }

    buildInfo.position = this->position;
    buildInfo.parentID = this->id;
    buildInfo.layer = this->layer;
    if (down) {
        buildInfo.settings1 = 0x000C3000;
    } else {
        buildInfo.settings1 = 0x00082000;
    }
    ActorMgr::instance()->create(buildInfo);

    this->doStateChange(&HammerBlock::StateID_Used);
}

void HammerBlock::beginState_Used() {
    this->_1AAE = 0;
    this->tileId = 50; // Used Block
    BlockWrapper::beginState_Used();
}
