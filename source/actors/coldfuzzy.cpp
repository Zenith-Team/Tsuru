#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/playerbase.h"
#include "game/playermgr.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "sead/random.h"
#include "math/functions.h"

class ColdFuzzy : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(ColdFuzzy, Enemy);

public:
    ColdFuzzy(const ActorBuildInfo* buildInfo);
    virtual ~ColdFuzzy() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static HitboxCollider::Info collisionInfo;

    ModelWrapper* model;

    struct {
        PlayerBase* player;
        u32 timer;
    } playerTimers[4];

    u32 projectileTimer;
};

const Profile ColdFuzzyProfile(&ColdFuzzy::build, ProfileID::ColdFuzzy);
PROFILE_RESOURCES(ProfileID::ColdFuzzy, Profile::LoadResourcesAt_Course, "coldobon");

HitboxCollider::Info ColdFuzzy::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

ColdFuzzy::ColdFuzzy(const ActorBuildInfo* buildInfo) 
    : Enemy(buildInfo)
    , model(nullptr)
    , projectileTimer(0)
{ }

Actor* ColdFuzzy::build(const ActorBuildInfo* buildInfo) {
    return new ColdFuzzy(buildInfo);
}

u32 ColdFuzzy::onCreate() {
    this->model = ModelWrapper::create("coldobon", "coldobon", 1);
    this->model->playSklAnim("run");
    this->model->loopSklAnims(true);
    
    this->hitboxCollider.init(this, &ColdFuzzy::collisionInfo);
    this->addHitboxColliders();

    for (u32 i = 0; i < 4; i++) {
        this->playerTimers[i].player = PlayerMgr::instance()->players[i];
        this->playerTimers[i].timer = 240;
    }

    return this->onExecute();
}

u32 ColdFuzzy::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();

    for (u32 i = 0; i < 4; i++) {
        if (this->playerTimers[i].timer <= 240) {
            this->playerTimers[i].timer++;
        }
    }
    // i copied all of this from the angry sun sprite
    if (this->projectileTimer == 30) {
        this->projectileTimer = 0;
        
        Vec2f target;
        this->distanceToPlayer(target);

        f32 angle = atan2f(target.y, target.x);

        StageActor* iceball;

        ActorBuildInfo projectileBuildInfo = { 0 };
        projectileBuildInfo.profile = Profile::get(ProfileID::PiranhaPlantIceBall);
        projectileBuildInfo.position = this->position;
        projectileBuildInfo.parentID = this->id;

        if (sead::randBool()) {
            projectileBuildInfo.rotation = fixRad(angle);
            iceball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            iceball->speed.x = cosf(angle) * 3.0f;
            iceball->speed.y = sinf(angle) * 3.0f;
        }

        else {
            projectileBuildInfo.rotation = fixRad(angle);
            iceball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            iceball->speed.x = cosf(angle) * 2.5f;
            iceball->speed.y = sinf(angle) * 2.5f;

            projectileBuildInfo.rotation = fixRad(angle + 0.4f);
            iceball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            iceball->speed.x = cosf(angle + 0.4f) * 2.5f;
            iceball->speed.y = sinf(angle + 0.4f) * 2.5f;

            projectileBuildInfo.rotation = fixRad(angle - 0.4f);
            iceball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            iceball->speed.x = cosf(angle - 0.4f) * 2.5f;
            iceball->speed.y = sinf(angle - 0.4f) * 2.5f;
        }
        this->projectileTimer++;
    }
    return 1;
}

u32 ColdFuzzy::onDraw() {
    this->model->draw();
    return 1;
}

void ColdFuzzy::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    for (u32 i = 0; i < 4; i++) {
        if (hcOther->owner == this->playerTimers[i].player && this->playerTimers[i].timer >= 240) {
            this->playerTimers[i].timer = 0;
            static_cast<PlayerBase*>(hcOther->owner)->doDamage(this, PlayerBase::DamageType_Ice);
        }
    }
}
