#include <game/actor/stage/multistateactor.h>
#include <game/graphics/model/model.h>
#include <game/graphics/drawmgr.h>
#include <game/actor/actormgr.h>

class StarCoinShard : public MultiStateActor {
public:
    StarCoinShard(const ActorBuildInfo* buildInfo);
    virtual ~StarCoinShard() { }

    static ActorBase* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    static u8 sCollectedCount;
    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info sCollisionInfo;

    ModelWrapper* mModel;
};

const Profile StarCoinShardProfile(&StarCoinShard::build, ProfileID::StarCoinShard, "StarCoinShard", nullptr, 0);

const HitboxCollider::Info StarCoinShard::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::ShapeRectangle, 5, 0, 0x824F, 0x20208, 0, &StarCoinShard::collisionCallback
};

u8 StarCoinShard::sCollectedCount = 0;

StarCoinShard::StarCoinShard(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
{ }

ActorBase* StarCoinShard::build(const ActorBuildInfo* buildInfo) {
    return new StarCoinShard(buildInfo);
}

u32 StarCoinShard::onCreate() {
    this->mModel = ModelWrapper::create("star_coin", "star_coinA");

    this->mHitboxCollider.init(this, &StarCoinShard::sCollisionInfo, nullptr);
    this->addHitboxColliders();

    return 1;
}

u32 StarCoinShard::onExecute() {
    this->mModel->updateAnimations();
    
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->mRotation, this->mPosition);
    this->mModel->setMtx(mtx);
    this->mModel->updateModel();

    this->mRotation.y += 0x3FD27D2;

    return 1;
}

u32 StarCoinShard::onDraw() {
    DrawMgr::sInstance->drawModel(this->mModel);

    return 1;
}

void StarCoinShard::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    StarCoinShard::sCollectedCount++;
    if (StarCoinShard::sCollectedCount % 4 == 0) {

        ActorBuildInfo starCoinBuildInfo = { 0 };

        starCoinBuildInfo.mSettings1 = hcSelf->mOwner->mSettings1;
        starCoinBuildInfo.mProfile = Profile::get(426);
        starCoinBuildInfo.mPosition = hcSelf->mOwner->mPosition;

        ActorMgr::sInstance->create(&starCoinBuildInfo, 0);
    }

    hcSelf->mOwner->mIsDeleted = true;
}
