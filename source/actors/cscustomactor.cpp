#include <game/actor/courseselect/cscollisionactor.h>
#include <game/graphics/model/model.h>
#include <game/graphics/drawmgr.h>
#include <log.h>

class CSCustomActor : public CSCollisionActor {
public:
    CSCustomActor(const ActorBuildInfo* buildInfo);
    virtual ~CSCustomActor() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* mModel;
    
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
    this->mModel = ModelWrapper::create("cobStarGate", "cobStarGate", 3);

    this->mHitboxCollider.init(this, &CSCustomActor::sCollisionInfo);

    return 1;
}

u32 CSCustomActor::onExecute() {
    // This needs to be in onExecute for the collision check below to work so it's probably not "add"
    CSHitboxColliderMgr::instance()->add(&this->mHitboxCollider);

    // Checks if player collided (gets called twice around 1 second after player collision, also causes the player to bounce back and go into a fighting stance)
    if (CSHitboxColliderMgr::instance()->FUN_21c5894(&this->mHitboxCollider) != 0) {
        this->mRotation += 0x5000000;
        LOG("Player collided");
    }

    return 1;
}

u32 CSCustomActor::onDraw() {
    Mtx34 mtx;

    mtx.rotateAndTranslate(this->mRotation, this->mPosition);

    this->mModel->setMtx(mtx);
    this->mModel->setScale(this->mScale);
    this->mModel->updateModel();

    DrawMgr::instance()->drawModel(mModel);

    return 1;
}
