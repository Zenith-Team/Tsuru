#include "game/actor/actormgr.h"
#include "tsuru/actor/blockwrapper.h"

class CustomPowerupBlock : public BlockWrapper {
    SEAD_RTTI_OVERRIDE_IMPL(CustomPowerupBlock, BlockWrapper);

public:
    CustomPowerupBlock(const ActorBuildInfo* buildInfo);
    virtual ~CustomPowerupBlock() { }

    u32 onCreate() override;

    void spawnItemUp() override;
    void spawnItemDown() override;

    void spawnPowerup(bool down);

    void beginState_Used() override;
};

const ActorInfo CustomPowerupBlockActorInfo = { Vec2i(8, -16), Vec2i(8, -8), Vec2i(0x100, 0x100), 0x0, 0x0, 0x0, 0x0, 0x8 };
REGISTER_PROFILE(CustomPowerupBlock, ProfileID::CustomPowerupBlock, "CustomPowerupBlock", &CustomPowerupBlockActorInfo, 0x1002);
PROFILE_RESOURCES(ProfileID::CustomPowerupBlock, Profile::LoadResourcesAt::Course, "I_hmrflower", "I_kinxkx", "I_musasabi");

CustomPowerupBlock::CustomPowerupBlock(const ActorBuildInfo* buildInfo)
    : BlockWrapper(buildInfo)
{ }

u32 CustomPowerupBlock::onCreate() {
    if (!BlockWrapper::init()) {
        return 2;
    }

    switch (eventID1 & 0xF) {
        default:
        case 0: this->tileId = 49; break; // Question Block
        case 1: this->tileId = 48; break; // Brick Block
        case 2: this->tileId = 5; this->stateType = BlockWrapper::StateType::InvisibleBlock; break; // Hidden Block (WHAT ARE THE TILE IDS?! :sob:)
    }

    if (this->stateType == BlockWrapper::StateType::UsedBlock) {
        this->doStateChange(&CustomPowerupBlock::StateID_Used);
    }

    return this->onExecute();
}

void CustomPowerupBlock::spawnItemUp() {
    this->spawnPowerup(false);
}

void CustomPowerupBlock::spawnItemDown() {
    this->spawnPowerup(true);
}

void CustomPowerupBlock::spawnPowerup(bool down) {
    ActorBuildInfo buildInfo = { 0 };

    switch (this->eventID1 >> 0x4 & 0xF) {
        default:
        case 0: buildInfo.profile = Profile::get(ProfileID::HammerFlower); break;
        case 1: buildInfo.profile = Profile::get(ProfileID::PoisonMushroom); break;
        case 2: buildInfo.profile = Profile::get(ProfileID::PAcorn); break;
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

    this->doStateChange(&CustomPowerupBlock::StateID_Used);
}

void CustomPowerupBlock::beginState_Used() {
    this->_1AAE = 0;
    this->tileId = 50; // Used Block
    BlockWrapper::beginState_Used();
}
