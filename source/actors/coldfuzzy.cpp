#include "game/actor/stage/enemy.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/actor/stage/playerbase.h"
#include "game/playermgr.h"

class ColdFuzzy : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(ColdFuzzy, Enemy)

public:
    ColdFuzzy(const ActorBuildInfo* buildInfo);
    virtual ~ColdFuzzy() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;

    static HitboxCollider::Info collisionInfo;

    // others
    ModelWrapper* model;

    struct PlayerTimer {
        PlayerBase* player;
        u32 timer;
    };
    PlayerTimer playerTimers[4];
};

// stuffs
const Profile ColdFuzzyProfile(&ColdFuzzy::build, ProfileID::ColdFuzzy);
PROFILE_RESOURCES(ProfileID::ColdFuzzy, Profile::LoadResourcesAt_Course, "chorobon");

// collider stuff
HitboxCollider::Info ColdFuzzy::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

void ColdFuzzy::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    for (u32 i = 0; i < 4; i++) {
        if (hcOther->owner == this->playerTimers[i].player && this->playerTimers[i].timer >= 240) {
            this->playerTimers[i].timer = 0;
            ((PlayerBase*) hcOther->owner)->doDamage(this, PlayerBase::DamageType_Ice);
        }
    }
    
}

// 
ColdFuzzy::ColdFuzzy(const ActorBuildInfo* buildInfo) 
    : Enemy(buildInfo)
    , model(nullptr)
{ }

Actor* ColdFuzzy::build(const ActorBuildInfo* buildInfo) {
    return new ColdFuzzy(buildInfo);
}

u32 ColdFuzzy::onCreate() {
    this->model = ModelWrapper::create("chorobon", "chorobon", 1);
    this->model->playSklAnim("run");
    this->model->loopSklAnims(true);
    
    this->hitboxCollider.init(this, &ColdFuzzy::collisionInfo);
    this->addHitboxColliders();

    for (u32 i = 0; i < 4; i++) {
        this->playerTimers[i].player = PlayerMgr::instance()->players[i];
    }

    return this->onExecute();
}

u32 ColdFuzzy::onExecute() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();

    for (u32 i = 0; i < 4; i++) {
        if (this->playerTimers[i].timer < 240) {
            this->playerTimers[i].timer++;
        }

    }


    return 1;
}

u32 ColdFuzzy::onDraw() {
    DrawMgr::instance()->drawModel(this->model);


    return 1;
}