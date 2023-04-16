#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/playerbase.h"
#include "game/playermgr.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/effect/effect.h"
#include "sead/random.h"
#include "game/movementhandler.h"
const u32 timerThreshold = 315;

class ColdFuzzy : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(ColdFuzzy, Enemy);

public:
    ColdFuzzy(const ActorBuildInfo* buildInfo);
    virtual ~ColdFuzzy() { }
    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    void collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    bool collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) override;
    static HitboxCollider::Info collisionInfo;

    ModelWrapper* model;
    MovementHandler movementHandler;
    struct {
        PlayerBase* player;
        u32 timer;
    } playerTimers[4];
};

REGISTER_PROFILE(ColdFuzzy, ProfileID::ColdFuzzy);
PROFILE_RESOURCES(ProfileID::ColdFuzzy, Profile::LoadResourcesAt::Course, "coldobon");

HitboxCollider::Info ColdFuzzy::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(12.0f, 12.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

ColdFuzzy::ColdFuzzy(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , movementHandler()
{ }

u32 ColdFuzzy::onCreate() {
    this->model = ModelWrapper::create("coldobon", "coldobon", 1);
    this->model->playSklAnim("run");
    this->model->loopSklAnims(true);

    this->hitboxCollider.init(this, &ColdFuzzy::collisionInfo);
    this->addHitboxColliders();

    for (u32 i = 0; i < 4; i++) {
        this->playerTimers[i].player = PlayerMgr::instance()->players[i];
        this->playerTimers[i].timer = timerThreshold;
    }

    u32 movementMask = this->movementHandler.getMaskForMovementType(3);
    // path support because tsuru doesn't support line-controlled things just yet
    this->movementHandler.link(this->position, movementMask, this->movementID);
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
        if (this->playerTimers[i].timer <= timerThreshold) {
            this->playerTimers[i].timer++;
        }
    }

    this->movementHandler.execute();
    this->position = this->movementHandler.position;
    return 1;
}

u32 ColdFuzzy::onDraw() {
    this->model->draw();

    return 1;
}

void ColdFuzzy::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    for (u32 i = 0; i < 4; i++) {
        if (hcOther->owner == this->playerTimers[i].player && this->playerTimers[i].timer >= timerThreshold) {
            this->playerTimers[i].timer = 0;
            static_cast<PlayerBase*>(hcOther->owner)->doDamage(this, PlayerBase::DamageType::Ice);
        }
    }
}

void ColdFuzzy::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);
}


bool ColdFuzzy::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->scale);

    this->isDeleted = true;

    return true;
}

bool ColdFuzzy::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;
    return this->collisionStar(hcSelf, hcOther);
}

bool ColdFuzzy::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    hcOther->owner->isDeleted = true;

    return true;
}

bool ColdFuzzy::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool ColdFuzzy::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool ColdFuzzy::collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);
    return true;
}

bool ColdFuzzy::collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool ColdFuzzy::collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);

    return true;
}

bool ColdFuzzy::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionStar(hcSelf, hcOther);

    return true;
}

bool ColdFuzzy::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionStar(hcSelf, hcOther);

    return true;
}
