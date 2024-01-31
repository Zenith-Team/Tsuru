#include "game/actor/stage/stageactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/actormgr.h"
#include "game/audio/gameaudio.h"
#include "game/effect/effect.h"
#include "log.h"

class StarCoinShardMgr;

class StarCoinShard : public StageActor {
    SEAD_RTTI_OVERRIDE(StarCoinShard, StageActor);

public:
    StarCoinShard(const ActorBuildInfo* buildInfo);
    virtual ~StarCoinShard() { }

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
    SEAD_RTTI_OVERRIDE(StarCoinShardMgr, StageActor);

public:
    StarCoinShardMgr(const ActorBuildInfo* buildInfo);
    virtual ~StarCoinShardMgr() { }

    u32 onExecute() override;

    u32 collectedCount;
    u32 id;
};

const ActorInfo StarCoinShardMgrActorInfo = {
    sead::Vector2i(0, 0), sead::Vector2i(0, 0), sead::Vector2i(9000, 9000), 0, 0, 0, 0, 0
};

REGISTER_PROFILE(StarCoinShard, ProfileID::StarCoinShard);
REGISTER_PROFILE(StarCoinShardMgr, ProfileID::StarCoinShardMgr, "StarCoinShardMgr", &StarCoinShardMgrActorInfo);

PROFILE_RESOURCES(ProfileID::StarCoinShard, Profile::LoadResourcesAt::Course, "star_shard");
PROFILE_RESOURCES(ProfileID::StarCoinShardMgr, Profile::LoadResourcesAt::Course, "star_coin");

const HitboxCollider::Info StarCoinShard::collisionInfo = {
    sead::Vector2f(0.0f, 0.0f), sead::Vector2f(10.0f, 10.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &StarCoinShard::collisionCallback
};

StarCoinShard::StarCoinShard(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
    , mgr(nullptr)
{ }

u32 StarCoinShard::onCreate() {
    this->model = ModelWrapper::create("star_shard", "star_shard");

    this->hitboxCollider.init(this, &StarCoinShard::collisionInfo);
    this->addHitboxColliders();

    this->mgrID = this->eventID1 >> 0x4 & 0xF;

    return this->onExecute();
}

u32 StarCoinShard::onExecute() {
    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position);

    this->rotation.y += sead::Mathf::deg2idx(3.0f);

    this->model->setMtx(mtx);
    this->model->updateModel();

    if (this->mgr != nullptr) {
        return 1;
    }

    for (Actor** it = &ActorMgr::instance()->actors.start.front(); it != ActorMgr::instance()->actors.end; ++it) {
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
    if (hcOther->owner->type == StageActor::Type::Player || hcOther->owner->type == StageActor::Type::Yoshi) {
        StarCoinShard* self = (StarCoinShard*)hcSelf->owner;

        if ((self->mgr->collectedCount + 1) >= (self->mgr->eventID1 & 0xF)) {
            GameAudio::startSoundMap(SoundEffects::SE_OBJ_GET_RED_COIN_COMPLETE, self->position);
        } else {
            GameAudio::startSoundMap((SoundEffects::IDs)(SoundEffects::SE_OBJ_GET_RED_COIN + self->mgr->collectedCount), self->position);
        }

        Effect::spawn(RP_CoinNormalGet, &self->position);

        self->mgr->collectedCount++;
        self->isDeleted = true;
    }
}

StarCoinShardMgr::StarCoinShardMgr(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , collectedCount(0)
    , id(buildInfo->eventID1 >> 0x4 & 0xF)
{ }

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
