#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/stageactor.h"
#include "game/actor/actormgr.h"
#include "game/resource/util.h"
#include "game/graphics/rendermgr.h"
#include "game/movementhandler.h"
#include "tsuru/actors/stringbank.h"
#include "layer/aglRenderer.h"
#include "ghs.h"
#include "log.h"
#include <cstring>

class ModelLoader : public StageActor {
    SEAD_RTTI_OVERRIDE(ModelLoader, StageActor);

public:
    ModelLoader(const ActorBuildInfo* buildInfo);
    virtual ~ModelLoader() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    char modelFile[49];
    char modelName[49];
    char sklAnimName[49];

    ModelWrapper* model;
    bool parallax;
    bool inFront;
    MovementHandler movementHandler;
};

REGISTER_PROFILE(ModelLoader, ProfileID::ModelLoader);

ModelLoader::ModelLoader(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
    , parallax(false)
{ }

u32 ModelLoader::onCreate() {
    this->parallax = this->eventID1 >> 0x4 & 0xF; // Nybble 1
    this->inFront = this->eventID2 >> 0x4 & 0xF; // Nybble 3

    static const f32 scales[] = {
        1.0f, 0.25f, 0.5f, 0.75f, 1.25f, 1.5f, 1.75f, 2.0f, 2.5f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f
    };

    this->scale *= scales[this->eventID2 & 0xF]; // Nybble 4

    if (this->parallax) {
        this->position.z = -250.0f + static_cast<f32>(this->eventID1 & 0xF) * 70.0f;
    }

    u8 modelFileBankID = this->settings1 >> 0x18 & 0xFF; // Nybbles 5-6
    u8 modelNameBankID = this->settings1 >> 0x10 & 0xFF; // Nybbles 7-8
    u8 sklAnimBankID = this->settings1 >> 0x8 & 0xFF; // Nybbles 9-10
    if (modelFileBankID == 0 || modelNameBankID == 0) {
        return 2;
    }

    __memzero(this->modelFile, 49);
    __memzero(this->modelName, 49);
    __memzero(this->sklAnimName, 49);

    ActorBuffer* actors = &ActorMgr::instance()->actors;
    for (u32 i = 0; i < actors->start.size(); i++) {
        StringBank* strBank = sead::DynamicCast<StringBank, Actor>(actors->start[i]);

        if (!strBank || strBank->layer != StringBank::Type::Primary) {
            continue;
        }

        if (strBank->bankID == modelFileBankID) {
            strncpy(this->modelFile, strBank->string, 49);
            strBank->isDeleted = true;
        }

        if (strBank->bankID == modelNameBankID) {
            strncpy(this->modelName, strBank->string, 49);
            strBank->isDeleted = true;
        }

        if (sklAnimBankID != 0 && strBank->bankID == sklAnimBankID) {
            strncpy(this->sklAnimName, strBank->string, 49);
            strBank->isDeleted = true;
        }
    }

    if (this->modelFile[0] == '\0' || this->modelName[0] == '\0') {
        return 2;
    }

    PRINT(LogColor::Yellow, "(ModelLoader #", modelFileBankID + modelNameBankID, ") Loading model ", this->modelName, " from ", this->modelFile);

    ResArchive* archive = ResArchiveMgr::instance()->get(this->modelFile);
    if (!archive) {
        PRINT(LogColor::Red, "(ModelLoader #", modelFileBankID + modelNameBankID, ") Failed to load model ", this->modelName, " from ", this->modelFile);
        return 2;
    }

    this->model = ModelWrapper::create(archive, this->modelName, sklAnimBankID != 0);

    if (sklAnimBankID != 0) {
        this->model->playSklAnim(this->sklAnimName);
    }

    PRINT(LogColor::Green, "(ModelLoader #", modelFileBankID + modelNameBankID, ") Successfully loaded model ", this->modelName, " from ", this->modelFile);

    this->movementHandler.link(this->position, this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF), this->movementID);

    return this->onExecute();
}

u32 ModelLoader::onExecute() {
    if (this->model) {
        sead::Matrix34f mtx;
        mtx.makeRTIdx(this->rotation, this->position);
        this->model->setMtx(mtx);
        this->model->setScale(this->scale);
        this->model->updateModel();
        this->model->updateAnimations();
    
        this->movementHandler.execute();
        this->position = this->movementHandler.position;
    }

    return 1;
}

u32 ModelLoader::onDraw() {
    if (this->model) {
        if (this->parallax) {
            agl::lyr::Renderer* renderer = agl::lyr::Renderer::instance();

            renderer->getLayer(7)->setClearDepthEnable(false);

            agl::lyr::Layer* layer = renderer->getLayer(11);
            layer->setCamera(renderer->getLayer(5)->getCamera());
            layer->setProjection(renderer->getLayer(5)->getProjection());

            if (this->inFront) {
                DrawMgr::instance()->setTargetLayer(agl::lyr::Renderer::instance()->getLayer(11), 0);
            } else {
                DrawMgr::instance()->setTargetLayer(agl::lyr::Renderer::instance()->getLayer(5), 1);
            }
        }

        this->model->draw();

        if (this->parallax) {
            DrawMgr::instance()->setTargetLayer(agl::lyr::Renderer::instance()->getLayer(9), 0);
        }
    }

    return 1;
}

extern "C" void CreateParallaxLayer() {
    RenderMgr* renderMgr = new RenderMgr("ParallaxFrontMgr");
    renderMgr->init(1, 0x200, 1, 1, nullptr);

    agl::lyr::Renderer* renderer = agl::lyr::Renderer::instance();
    renderer->createLayer<RenderObjLayer>(11, "ParallaxFrontLayer", agl::lyr::cDisplayType_Top_TV, nullptr)->setParentRenderer(renderMgr);
    
    renderer->getLayer(11)->setClearDepthEnable(true);
}
