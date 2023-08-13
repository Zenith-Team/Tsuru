#include "tsuru/actor/blockwrapper.h"
#include "game/graphics/model/modelnw.h"
#include "game/playermgr.h"
#include "game/coinmgr.h"
#include "sead/array.h"

class TripleBlock : public BlockWrapper {
    SEAD_RTTI_OVERRIDE_IMPL(TripleBlock, BlockWrapper);

public:
    TripleBlock(const ActorBuildInfo* buildInfo);
    virtual ~TripleBlock() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void spawnItemUp() override;
    void spawnItemDown() override;

    void spawnItem(u8 item);
    void spawnSideCoins();

    ModelWrapper* model;
    u8 modelType; // standard, underground, lava 1, lava 2

    void beginState_Used() override;
};

REGISTER_PROFILE(TripleBlock, ProfileID::TripleBlock);
PROFILE_RESOURCES(ProfileID::TripleBlock, Profile::LoadResourcesAt::Course, "blocktripa", "blocktripb", "blocktripc");

TripleBlock::TripleBlock(const ActorBuildInfo* buildInfo)
    : BlockWrapper(buildInfo)
    , modelType(this->eventID1 & 0xF) // Nybble 2
{ }

u32 TripleBlock::onCreate() {
    if (!BlockWrapper::init()) {
        return 2;
    }

    this->position.x += 8;

    // switch/case didn't work
    if (this->modelType == 1) {
        this->model = ModelWrapper::create("blocktripb", "block_stch", 0, 1);
        this->model->playTexPatternAnim("chika");
    }  else if (this->modelType >= 2) {
        this->model = ModelWrapper::create("blocktripc", "block_stch", 0, 2);
        if (this->modelType == 2) {
            this->model->playTexPatternAnim("yougan");
        } else if (this->modelType == 3) {
            this->model->playTexPatternAnim("yougan2");
        }
    } else {
        this->model = ModelWrapper::create("blocktripa", "block_stch", 0, 1);
        this->model->playTexPatternAnim("standard");
    }

    this->rectCollider.points[0].x -= 16.0f;
    this->rectCollider.points[1].x += 16.0f;
    this->rectCollider.points[2].x += 16.0f;
    this->rectCollider.points[3].x -= 16.0f;

    if (this->stateType == BlockWrapper::StateType::UsedBlock) {
        this->doStateChange(&TripleBlock::StateID_Used);
    }

    return this->onExecute();
}

u32 TripleBlock::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position + Vec3f(0.0f, 8.0f, 0.0f));

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();
    this->model->updateAnimations();

    if (this->model->texPatternAnims[0]->frameCtrl.currentFrame == 50) {
        this->model->texPatternAnims[0]->frameCtrl.currentFrame = 0;
    }

    return BlockWrapper::onExecute();
}

u32 TripleBlock::onDraw() {
    this->model->draw();

    return 1;
}

void TripleBlock::spawnItemUp() {
    this->spawnItem(this->eventID1 >> 0x4 & 0xF); // nybble 1
}

void TripleBlock::spawnItemDown() {
    this->spawnItem(this->eventID1 >> 0x4 & 0xF); // nybble 1
}

void TripleBlock::spawnItem(u8 item) {
    this->doStateChange(&BlockBase::StateID_Used);

    u32 playerCount = 0;
    for (u32 i = 0; i < 4; i++) {
        if (PlayerMgr::instance()->players[i] != nullptr) {
            playerCount++;
        }
    }

    switch (item) {
        default:
            return;
        case 0:
            this->content = BlockAndCoinBase::Content::LifeMushroom;
            goto powerupspawn;
        case 1:
            CoinMgr::instance()->spawnItemCoin(this->position, this->spawnDirection, this->hitPlayerID);
            return;
        case 2:
            CoinMgr::instance()->spawnItemCoin(this->position, this->spawnDirection, this->hitPlayerID);
            this->spawnSideCoins();
            return;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            this->content = static_cast<BlockAndCoinBase::Content::__type__>(item);
        powerupspawn:
            if (playerCount > 1) {
                this->spawnMultiPowerup(this->position, 0, 1, false);
            } else {
                this->spawnPowerup(this->position, 0, 1, false);
                this->spawnSideCoins();
            }
            return;
        case 12:
            this->spawnPortableSpring();
            this->spawnSideCoins();
            return;
        case 13:
            this->spawnVine();
            this->spawnSideCoins();
            return;
        case 14:
            this->spawnYoshiEgg(playerCount > 1);
            this->spawnSideCoins();
            return;
    }
}

void TripleBlock::spawnSideCoins() {
    CoinMgr::instance()->spawnItemCoin(this->position + Vec3f(-16.0f, 0.0f, 0.0f), this->spawnDirection, this->hitPlayerID);
    CoinMgr::instance()->spawnItemCoin(this->position + Vec3f( 16.0f, 0.0f, 0.0f), this->spawnDirection, this->hitPlayerID);
}

void TripleBlock::beginState_Used() {
    this->_1AAE = 0; // This fixes the bug where items will bounce off of the block as if its being bumped
    this->model->texPatternAnims[0]->frameCtrl.speed = 0.0f;
    this->model->texPatternAnims[0]->frameCtrl.currentFrame = 51; // the 51st frame of the texpat anim is the "used" one
    BlockWrapper::beginState_Used();
}
