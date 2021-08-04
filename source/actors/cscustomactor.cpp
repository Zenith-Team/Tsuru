#include "game/actor/courseselect/courseselectsomethingactor.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "log.h"

class CSCustomActor : public CourseSelectSomethingActor {
public:
    CSCustomActor(const ActorBuildInfo* buildInfo);
    virtual ~CSCustomActor() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* mModel;
};

CSCustomActor::CSCustomActor(const ActorBuildInfo* buildInfo) 
    : CourseSelectSomethingActor(buildInfo)
{ }

BaseActor* CSCustomActor::build(const ActorBuildInfo* buildInfo) {
    return new CSCustomActor(buildInfo);
}

u32 CSCustomActor::onCreate() {
    this->mModel = ModelWrapper::create("I_musasabi", "I_musasabiP", 1, 1, 0, 0, 0);

    return 1;
}

u32 CSCustomActor::onExecute() {
    LOG("CSCustomActor onExecute");

    Mtx34 mtx;

    mtx.rotateAndTranslate(this->mRotation, this->mPosition);

    this->mModel->setMtx(mtx);
    this->mModel->setScale(this->mScale * 4);
    this->mModel->updateModel();

    return 1;
}

u32 CSCustomActor::onDraw() {
    DrawMgr::sInstance->drawModel(mModel);

    return 1;
}
