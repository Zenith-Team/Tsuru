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
    32.0f, Vec3f(0.0f)
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
    Mtx34 mtx;

    mtx.rotateAndTranslate(this->mRotation, this->mPosition);

    this->mModel->setMtx(mtx);
    this->mModel->setScale(this->mScale);
    this->mModel->updateModel();

    CSHitboxColliderMgr::sInstance->add(&this->mHitboxCollider);

    if (CSHitboxColliderMgr::sInstance->FUN_21c5894(&this->mHitboxCollider) != 0) { LOG("NOT zero"); }
    else { LOG("YES zero"); }

    return 1;
}

u32 CSCustomActor::onDraw() {
    DrawMgr::sInstance->drawModel(mModel);

    return 1;
}
