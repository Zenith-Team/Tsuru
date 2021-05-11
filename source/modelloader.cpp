#include "actor/actorbase.h"

#include "drawmgr.h"

class ModelLoader : public ActorBase {
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

ModelLoader::ModelLoader(const ActorBuildInfo* buildInfo)
    : ActorBase(buildInfo) { }

ActorBase* ModelLoader::build(const ActorBuildInfo* buildInfo) {
    return new ModelLoader(buildInfo);
}

u32 ModelLoader::onCreate() {
    switch (/* Nybble dropdown */) {
        
    }
}
