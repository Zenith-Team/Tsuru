#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/stageactor.h"
#include "log.h"
#include "ghs.h"
#include "game/actor/actormgr.h"
#include "tsuru/actors/stringbank.h"
#include "game/resource/util.h"
#include <cstring>

class ModelLoader : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(ModelLoader, StageActor)

public:
    ModelLoader(const ActorBuildInfo* buildInfo);
    virtual ~ModelLoader() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    char modelFile[49];
    char modelName[49];

    ModelWrapper* model;
};

const Profile ModelLoaderProfile(&ModelLoader::build, ProfileID::ModelLoader);

ModelLoader::ModelLoader(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
{ }

Actor* ModelLoader::build(const ActorBuildInfo* buildInfo) {
    return new ModelLoader(buildInfo);
}

u32 ModelLoader::onCreate() {
    u8 modelFileBankID = this->settings1 >> 0x18 & 0xFF; // Nybbles 5-6
    u8 modelNameBankID = this->settings1 >> 0x10 & 0xFF; // Nybbles 7-8
    if (modelFileBankID == 0 || modelNameBankID == 0) return 2;
    __memzero(this->modelFile, 49);
    __memzero(this->modelName, 49);

    ActorBuffer* actors = &ActorMgr::instance()->actors;
    for (u32 i = 0; i < actors->start.size; i++) {
        StringBank* strBank = sead::DynamicCast<StringBank, Actor>(actors->start[i]);
        if (!strBank || strBank->layer != StringBank::Type::Primary) continue;

        if (strBank->bankID == modelFileBankID) {
            strncpy(this->modelFile, strBank->string, 49);
            strBank->isDeleted = true;
        }
        if (strBank->bankID == modelNameBankID) {
            strncpy(this->modelName, strBank->string, 49);
            strBank->isDeleted = true;
        }
    }
    if (this->modelFile[0] == '\0' || this->modelName[0] == '\0') return 2;

    LOG("%s(ModelLoader #%i+%i) Loading model %s from %s", LogColor::Yellow, modelFileBankID, modelNameBankID, this->modelName, this->modelFile);
    ResArchive* archive = ResArchiveMgr::instance()->get(this->modelFile);
    if (!archive) {
        LOG("%s(ModelLoader #%i+%i) Failed to load model %s from %s", LogColor::Red, modelFileBankID, modelNameBankID, this->modelName, this->modelFile);
        return 2;
    }
    this->model = ModelWrapper::create(archive, this->modelName);
    this->updateModel();
    LOG("%s(ModelLoader #%i+%i) Successfully loaded model %s from %s", LogColor::Green, modelFileBankID, modelNameBankID, this->modelName, this->modelFile);
    return 1;
}

u32 ModelLoader::onExecute() {
    if (this->model) this->updateModel();
    return 1;
}

u32 ModelLoader::onDraw() {
    if (this->model) this->model->draw();
    return 1;
}

void ModelLoader::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();
}
