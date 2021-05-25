#include "actor/actor.h"

#include "drawmgr.h"

class ModelLoader : public Actor {
public:
    ModelLoader(const ActorBuildInfo* buildInfo);
    virtual ~ModelLoader() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* model;
};

const Profile ModelLoaderProfile(&ModelLoader::build, ProfileId::Sprite308, "ModelLoader", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite308, "modelpack");

ModelLoader::ModelLoader(const ActorBuildInfo* buildInfo) : Actor(buildInfo) { }

ActorBase* ModelLoader::build(const ActorBuildInfo* buildInfo) {
    return new ModelLoader(buildInfo);
}

u32 ModelLoader::onCreate() {
    u8 nybble12 = settings1 >>  0 & 0xF;
    switch (nybble12) {
        case 0: model = ModelWrapper::create("modelpack", "glare");
        default: model = ModelWrapper::create("modelpack", "default");
    }

    updateModel();

    return 1;
}

u32 ModelLoader::onExecute() {
    updateModel();

    return 1;
}

u32 ModelLoader::onDraw() {
    DrawMgr::instance->drawModel(model);

    return 1;
}

void ModelLoader::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->updateModel();
    model->updateAnimations();
}
