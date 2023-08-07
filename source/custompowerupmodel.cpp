#include "tsuru/custompowerupmodel.h"
#include "tsuru/playeradditionalresource.h"
#include "game/actor/stage/player.h"

CustomPowerupModel::CustomPowerupModel()
    : headBoneID(-1)
    , shellBoneID(-1)
    , hammerHelmet(nullptr)
    , hammerShell(nullptr)
{ }

CustomPowerupModel::~CustomPowerupModel() {
    delete this->hammerHelmet;
    delete this->hammerShell;
}

void CustomPowerupModel::init_(Player* target) {   
    PlayerModel* const mdl = target->model.playerModel;

    this->headBoneID = mdl->headModels[mdl->currentPowerupModel]->model->searchBoneIndex("player_head");
    this->shellBoneID = mdl->bodyModels[mdl->currentPowerupModel]->model->searchBoneIndex("spin");

    this->hammerHelmet = ModelWrapper::create("hmrpy", "hmrpy_partsC");
    this->hammerShell = ModelWrapper::create("hmrpy", "hmrpy_partsB");
}

void CustomPowerupModel::draw_(Player* target) {
    switch (target->powerupState) {
        case PlayerBase::PowerupState::Hammer: {
            ModelWrapper* const mdl = target->model.playerModel->bodyModels[target->model.playerModel->currentPowerupModel];
            ModelWrapper* const head = target->model.playerModel->headModels[target->model.playerModel->currentPowerupModel];
            
            s32 hairIdx = head->model->searchMaterialIndex("mat_player_hair");
            s32 hatIdx = head->model->searchMaterialIndex("mat_player_hat");

            if (hairIdx > -1)
                head->model->setMaterialVisible(hairIdx, true);

            if (hatIdx > -1)
                head->model->setMaterialVisible(hatIdx, false);

            Mtx34 mtx;

            head->model->getBoneWorldMatrix(this->headBoneID, &mtx);
            this->hammerHelmet->setMtx(mtx);
            this->hammerHelmet->setScale(target->scale);
            this->hammerHelmet->updateModel();
            this->hammerHelmet->updateAnimations();
            this->hammerHelmet->draw();

            mdl->model->getBoneWorldMatrix(this->shellBoneID, &mtx);

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

    lwz r0, 0x14(r1)
    lwz r31, 0xC(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr

ASM_END
