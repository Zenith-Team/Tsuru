#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/actor/actormgr.h"

class StarCoinShard : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(StarCoinShard, MultiStateActor)

public:
    StarCoinShard(const ActorBuildInfo* buildInfo);
    virtual ~StarCoinShard() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    static u8 sCollectedCount;
    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info sCollisionInfo;

    ModelWrapper* model;
};

const Profile StarCoinShardProfile(&StarCoinShard::build, ProfileID::StarCoinShard);
PROFILE_RESOURCES(ProfileID::StarCoinShard, Profile::LoadResourcesAt_Course, "star_coin");

const HitboxCollider::Info StarCoinShard::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &StarCoinShard::collisionCallback
};

u8 StarCoinShard::sCollectedCount = 0;

StarCoinShard::StarCoinShard(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
{ }

Actor* StarCoinShard::build(const ActorBuildInfo* buildInfo) {
    return new StarCoinShard(buildInfo);
}

u32 StarCoinShard::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");

    this->hitboxCollider.init(this, &StarCoinShard::sCollisionInfo, nullptr);
    this->addHitboxColliders();

    return 1;
}

u32 StarCoinShard::onExecute() {
    this->model->updateAnimations();

    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();

    this->rotation.y += 0x3FD27D2;

    return 1;
}

u32 StarCoinShard::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

void StarCoinShard::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    StarCoinShard::sCollectedCount++;
    if (StarCoinShard::sCollectedCount % 4 == 0) {

        ActorBuildInfo starCoinBuildInfo = { 0 };

        starCoinBuildInfo.settings1 = hcSelf->owner->settings1;
        starCoinBuildInfo.profile = Profile::get(ProfileID::StarCoin);
        starCoinBuildInfo.position = hcSelf->owner->position;

        ActorMgr::instance()->create(starCoinBuildInfo, 0);
    }

    hcSelf->owner->isDeleted = true;
}
