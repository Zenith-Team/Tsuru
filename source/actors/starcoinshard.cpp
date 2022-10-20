#include "game/actor/stage/stageactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/actormgr.h"
#include "log.h"

class StarCoinShardMgr;

class StarCoinShard : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(StarCoinShard, StageActor);

public:
    StarCoinShard(const ActorBuildInfo* buildInfo);
    virtual ~StarCoinShard() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    StarCoinShardMgr* mgr;
    u8 mgrID;
};

class StarCoinShardMgr : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(StarCoinShardMgr, StageActor);

public:
    StarCoinShardMgr(const ActorBuildInfo* buildInfo);
    virtual ~StarCoinShardMgr() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;

    u32 collectedCount;
    u32 id;
};

const Profile StarCoinShardProfile(&StarCoinShard::build, ProfileID::StarCoinShard);
const Profile StarCoinShardMgrProfile(&StarCoinShardMgr::build, ProfileID::StarCoinShardMgr);

PROFILE_RESOURCES(ProfileID::StarCoinShard, Profile::LoadResourcesAt::Course, "star_shard");

const HitboxCollider::Info StarCoinShard::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(10.0f, 10.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &StarCoinShard::collisionCallback
};

StarCoinShard::StarCoinShard(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
    , mgr(nullptr)
{ }

Actor* StarCoinShard::build(const ActorBuildInfo* buildInfo) {
    return new StarCoinShard(buildInfo);
}

u32 StarCoinShard::onCreate() {
    this->model = ModelWrapper::create("star_shard", "star_shard");

    this->hitboxCollider.init(this, &StarCoinShard::collisionInfo);
    this->addHitboxColliders();

    this->mgrID = this->eventID1 >> 0x4 & 0xF;

    return this->onExecute();
}

u32 StarCoinShard::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->rotation.y += fixDeg(3.0f);

    this->model->setMtx(mtx);
    this->model->updateModel();

    for (Actor** it = ActorMgr::instance()->actors.start.buffer; it != ActorMgr::instance()->actors.end.buffer; ++it) {
        if (*it != nullptr) {
            Actor& actor = **it;
            if (actor.getProfileID() == ProfileID::StarCoinShardMgr) {
                StarCoinShardMgr* mgr = static_cast<StarCoinShardMgr*>(&actor);
                if (mgr->id == this->mgrID) {
                    this->mgr = mgr;
                    break;
                }
            }
        }
    }
    
    return 1;
}

u32 StarCoinShard::onDraw() {
    this->model->draw();

    return 1;
}

void StarCoinShard::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type == StageActor::Type::Player) {
        StarCoinShard* self = (StarCoinShard*)hcSelf->owner;

        self->mgr->collectedCount++;
        self->isDeleted = true;
    }
}

StarCoinShardMgr::StarCoinShardMgr(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , collectedCount(0)
    , id(buildInfo->eventID1 >> 0x4 & 0xF)
{ }

Actor* StarCoinShardMgr::build(const ActorBuildInfo* buildInfo) {
    return new StarCoinShardMgr(buildInfo);
}

u32 StarCoinShardMgr::onExecute() {
    if (this->collectedCount >= (this->eventID1 & 0xF)) {
        this->isDeleted = true;

        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(ProfileID::StarCoin);
        buildInfo.position = this->position;
        buildInfo.settings1 = this->settings1;

        ActorMgr::instance()->create(buildInfo, 0);
    }
    
    return 1;
}
