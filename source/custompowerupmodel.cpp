#include "tsuru/custompowerupmodel.h"
#include "tsuru/playeradditionalresource.h"
#include "game/actor/stage/player.h"

CustomPowerupModel::CustomPowerupModel()
    : hammerHelmet(nullptr)
    , hammerShell(nullptr)
{ }

CustomPowerupModel::~CustomPowerupModel() {
    delete this->hammerHelmet;
    delete this->hammerShell;
}

void CustomPowerupModel::init_(Player* target) {
    this->hammerHelmet = ModelWrapper::create("hmrpy", "hmrpy_partsC");
    this->hammerShell = ModelWrapper::create("hmrpy", "hmrpy_partsB");
}

void CustomPowerupModel::draw_(Player* target) {
    PlayerModel* playerModel = target->modelMgr.playerModel;

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

            Mtx34 mtx;

            headModel->getBoneWorldMatrix(headBoneID, &mtx);
            this->hammerHelmet->setMtx(mtx);
            this->hammerHelmet->setScale(target->scale);
            this->hammerHelmet->updateModel();
            this->hammerHelmet->updateAnimations();
            this->hammerHelmet->draw();

            bodyModel->getBoneWorldMatrix(shellBoneID, &mtx);

            this->hammerShell->setMtx(mtx);
            this->hammerShell->setScale(target->scale);
            this->hammerShell->updateModel();
            this->hammerShell->updateAnimations();
            this->hammerShell->draw();
        }
    }
}

void CustomPowerupModel::init(Player* target) {
    PlayerAdditionalResource::data[target->playerID].customPowerupModel.init_(target);
}

void CustomPowerupModel::draw(Player* target) {
    PlayerAdditionalResource::data[target->playerID].customPowerupModel.draw_(target);
}

ASM_BEGIN

.include "macros.S"

.global DrawCustomPowerupModel
DrawCustomPowerupModel:
    SaveVolatileRegisters
    mr r3, r31
    bl draw__18CustomPowerupModelSFP6Player
    RestoreVolatileRegisters

    li r3, 1
    blr

ASM_END
