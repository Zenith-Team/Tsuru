#include "tsuru/actor/blockwrapper.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "game/graphics/model/modelnw.h"
#include "game/savemgr.h"
#include "game/actor/actormgr.h"
#include "log.h"

class SwitchBlock : public BlockWrapper {
    SEAD_RTTI_OVERRIDE_IMPL(SwitchBlock, BlockWrapper);

public:
    SwitchBlock(const ActorBuildInfo* buildInfo);
    virtual ~SwitchBlock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void spawnItemUp() override;
    void spawnItemDown() override;

    ModelWrapper* model;
};

const ActorInfo SwitchBlockActorInfo = {
    Vec2i(8, -16), Vec2i(8, -8), Vec2i(0x100, 0x100), 0, 0, 0, 0, ActorInfo::Flag_Unknown1
};

const Profile SwitchBlockProfile(&SwitchBlock::build, ProfileID::SwitchBlock, "SwitchBlock", &SwitchBlockActorInfo, 0x1002);
PROFILE_RESOURCES(ProfileID::SwitchBlock, Profile::LoadResourcesAt_Course, "block_stch");

SwitchBlock::SwitchBlock(const ActorBuildInfo* buildInfo)
    : BlockWrapper(buildInfo)
{ }

Actor* SwitchBlock::build(const ActorBuildInfo* buildInfo) {
    return new SwitchBlock(buildInfo);
}

u32 SwitchBlock::onCreate() {
    if (!BlockWrapper::init()) {
        return 2;
    }

    this->model = ModelWrapper::create("block_stch", "block_stch", 0, 1);
    this->model->playTexPatternAnim("switch");
    this->model->texPatternAnims[0]->frameCtrl.speed = 0;
    this->model->texPatternAnims[0]->frameCtrl.currentFrame = TsuruSaveMgr::sSaveData.switchBlockBlue[SaveMgr::instance()->saveData->header.lastSessionSaveSlot] ? 1 : 0;

    return this->onExecute();
}

u32 SwitchBlock::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position + Vec3f(0, 8, 0));
    this->model->setMtx(mtx);
    this->model->updateModel();

    return BlockWrapper::onExecute();
}

u32 SwitchBlock::onDraw() {
    this->model->draw();

    return 1;
}

void SwitchBlock::spawnItemUp() {
    this->doStateChange(&StateID_Active);

    bool& isBlue = TsuruSaveMgr::sSaveData.switchBlockBlue[SaveMgr::instance()->saveData->header.lastSessionSaveSlot];

    isBlue = !isBlue;

    for (Actor** actor = ActorMgr::instance()->actors.start.buffer; actor != ActorMgr::instance()->actors.end.buffer; actor++) {
        if (*actor == nullptr) {
            continue;
        }

        if ((*actor)->getProfileID() != ProfileID::SwitchBlock) {
            continue;
        }

        SwitchBlock* sb = static_cast<SwitchBlock*>(*actor);
        sb->model->texPatternAnims[0]->frameCtrl.currentFrame = isBlue ? 1 : 0;
    }
}

void SwitchBlock::spawnItemDown() {
    this->doStateChange(&StateID_Active);

    bool& isBlue = TsuruSaveMgr::sSaveData.switchBlockBlue[SaveMgr::instance()->saveData->header.lastSessionSaveSlot];

    isBlue = !isBlue;

    for (Actor** actor = ActorMgr::instance()->actors.start.buffer; actor != ActorMgr::instance()->actors.end.buffer; actor++) {
        if (*actor == nullptr) {
            continue;
        }

        if ((*actor)->getProfileID() != ProfileID::SwitchBlock) {
            continue;
        }

        SwitchBlock* sb = static_cast<SwitchBlock*>(*actor);
        sb->model->texPatternAnims[0]->frameCtrl.currentFrame = isBlue ? 1 : 0;
    }
}
