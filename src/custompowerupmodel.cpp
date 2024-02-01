#include "tsuru/custompowerupmodel.h"
#include "tsuru/playeradditionalresource.h"
#include "game/actor/stage/player.h"
#include "tsuru/log.h"

CustomPowerupModel::CustomPowerupModel()
    : hammerHelmet(nullptr)
    , hammerShell(nullptr)
{ }

CustomPowerupModel::~CustomPowerupModel() {
    delete this->hammerHelmet;
    delete this->hammerShell;
}

void CustomPowerupModel::init_() {
    this->hammerHelmet = ModelWrapper::create("hmrpy", "hmrpy_partsC");
    this->hammerShell = ModelWrapper::create("hmrpy", "hmrpy_partsB");
}

void CustomPowerupModel::draw_(PlayerModel* playerModel) {
    switch (playerModel->powerupState) {
        case PlayerBase::PowerupState::Hammer: {
            Model* headModel = playerModel->headModel->model;
            Model* bodyModel = playerModel->bodyModel->model;
            
            s32 hairIdx = headModel->searchMaterialIndex("mat_player_hair");
            s32 hatIdx = headModel->searchMaterialIndex("mat_player_hat");

            if (hairIdx > -1)
                headModel->setMaterialVisible(hairIdx, true);

            if (hatIdx > -1)
                headModel->setMaterialVisible(hatIdx, false);

            s32 headBoneID = headModel->searchBoneIndex("player_head");
            s32 shellBoneID = bodyModel->searchBoneIndex("spin");

            sead::Matrix34f mtx;

            headModel->getBoneWorldMatrix(headBoneID, &mtx);
            this->hammerHelmet->setMtx(mtx);
            //this->hammerHelmet->setScale(target->scale); //!
            this->hammerHelmet->updateModel();
            this->hammerHelmet->updateAnimations();
            this->hammerHelmet->draw();

            bodyModel->getBoneWorldMatrix(shellBoneID, &mtx);

            this->hammerShell->setMtx(mtx);
            //this->hammerShell->setScale(target->scale); //!
            this->hammerShell->updateModel();
            this->hammerShell->updateAnimations();
            this->hammerShell->draw();
        }
    }
}

void CustomPowerupModel::draw(s8 playerID, PlayerModel* playerModel) {
    PlayerAdditionalResource::data[playerID].customPowerupModel.draw_(playerModel);
}

ASM_BEGIN

.include "macros.S"

.global DrawCustomPowerupModel
DrawCustomPowerupModel:
    SaveVolatileRegisters
    lbz r3, 0x54(r31)       // this->playerID
    lwz r4, 0x275C(r31)     // this->modelMgr->playerModel
    bl draw__18CustomPowerupModelSFScP11PlayerModel
    RestoreVolatileRegisters

    li r3, 1 // Replaced instruction
    blr

.global DrawCustomPowerupModelCS
DrawCustomPowerupModelCS: // r3 = &this->modelMgr
    stwu r1, -0x8(r1) // Replaced instruction

    SaveVolatileRegisters
    lwz r4, 0xC(r3)       // modelMgr->playerModel
    li r3, 0
    bl draw__18CustomPowerupModelSFScP11PlayerModel
    RestoreVolatileRegisters

    blr

ASM_END
