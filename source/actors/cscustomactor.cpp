#include <game/actor/courseselect/cscollisionactor.h>
#include <game/graphics/model/model.h>
#include <game/graphics/drawmgr.h>
#include <log.h>

class CSCustomActor : public CSCollisionActor {
    SEAD_RTTI_OVERRIDE_IMPL(CSCustomActor, CSCollisionActor)

public:
    CSCustomActor(const ActorBuildInfo* buildInfo);
    virtual ~CSCustomActor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    
    static const CSHitboxCollider::Info sCollisionInfo;
};

const CSHitboxCollider::Info CSCustomActor::sCollisionInfo = {
    64.0f,      // Size
    Vec3f(0.0f) // Offset
};

CSCustomActor::CSCustomActor(const ActorBuildInfo* buildInfo) 
    : CSCollisionActor(buildInfo)
{ }

Actor* CSCustomActor::build(const ActorBuildInfo* buildInfo) {
    return new CSCustomActor(buildInfo);
}

u32 CSCustomActor::onCreate() {
    this->model = ModelWrapper::create("cobStarGate", "cobStarGate", 3);

    this->hitboxCollider.init(this, &CSCustomActor::sCollisionInfo);

    return 1;
}

u32 CSCustomActor::onExecute() {
    // This needs to be in onExecute for the collision check below to work so it's probably not "add"
    CSHitboxColliderMgr::instance()->add(&this->hitboxCollider);

    // Checks if player collided (gets called twice around 1 second after player collision, also causes the player to bounce back and go into a fighting stance)
    if (CSHitboxColliderMgr::instance()->FUN_21c5894(&this->hitboxCollider) != 0) {
        this->rotation += 0x5000000;
        LOG("Player collided");
    }

    return 1;
}

u32 CSCustomActor::onDraw() {
    Mtx34 mtx;

    mtx.rotateAndTranslate(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateModel();

    DrawMgr::instance()->drawModel(model);

    return 1;
}
