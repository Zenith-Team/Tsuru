#include <game/actor/courseselect/cscollisionactor.h>
#include <game/graphics/model/model.h>
#include <game/graphics/drawmgr.h>
#include <log.h>

class CSCustomActor : public CSCollisionActor {
public:
    CSCustomActor(const ActorBuildInfo* buildInfo);
    virtual ~CSCustomActor() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* mModel;
    
    static const CSHitboxCollider::Info sCollisionInfo;
};

const Profile CSCustomActorProfile(&CSCustomActor::build, 869, "CSCustomActor", nullptr, 0);

const CSHitboxCollider::Info CSCustomActor::sCollisionInfo = {
    32.0f,      // Size
    Vec3f(0.0f) // Offset
};

CSCustomActor::CSCustomActor(const ActorBuildInfo* buildInfo) 
    : CSCollisionActor(buildInfo)
{ }

ActorBase* CSCustomActor::build(const ActorBuildInfo* buildInfo) {
    return new CSCustomActor(buildInfo);
}

u32 CSCustomActor::onCreate() {
    this->mModel = ModelWrapper::create("cobStarGate", "cobStarGate", 3);

    this->mHitboxCollider.init(this, &CSCustomActor::sCollisionInfo);

    CSHitboxColliderMgr::sInstance->FUN_21c5894(&this->mHitboxCollider);

    return 1;
}

u32 CSCustomActor::onExecute() {
    // This needs to be in onExecute for the collision check below to work so it's probably not "add"
    CSHitboxColliderMgr::sInstance->add(&this->mHitboxCollider);

    // Checks if player collided (gets called twice around 1 second after player collision, also causes the player to bounce back and go into a fighting stance)
    if (CSHitboxColliderMgr::sInstance->FUN_21c5894(&this->mHitboxCollider) != 0) {
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

    DrawMgr::sInstance->drawModel(mModel);

    sead::PrimitiveRenderer::sInstance->begin();
    sead::PrimitiveRenderer::sInstance->mRendererImpl->drawWireCubeImpl(mtx, sead::colorRed, sead::colorBlue);
    sead::PrimitiveRenderer::sInstance->end();

    return 1;
}
