#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/playerbase.h"
#include "game/playermgr.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/effect/effect.h"
#include "game/movementhandler.h"

class ColdFuzzy : public Enemy {
    SEAD_RTTI_OVERRIDE(ColdFuzzy, Enemy);

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
};

REGISTER_PROFILE(ColdFuzzy, ProfileID::ColdFuzzy);
PROFILE_RESOURCES(ProfileID::ColdFuzzy, Profile::LoadResourcesAt::Course, "coldobon");

HitboxCollider::Info ColdFuzzy::collisionInfo = {
    sead::Vector2f(0.0f, 0.0f), sead::Vector2f(12.0f, 12.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
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

    u32 movementMask = this->movementHandler.getMaskForMovementType(3);
    // path support because tsuru doesn't support line-controlled things just yet
    this->movementHandler.link(this->position, movementMask, this->movementID);
    return this->onExecute();
}

u32 ColdFuzzy::onExecute() {
    sead::Matrix34f mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();

    this->movementHandler.execute();
    this->position = this->movementHandler.position;
    return 1;
}

u32 ColdFuzzy::onDraw() {
    this->model->draw();

    return 1;
}

void ColdFuzzy::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    static_cast<PlayerBase*>(hcOther->owner)->trySpecialDamage(hcSelf->owner, PlayerBase::DamageType::Ice);
}

void ColdFuzzy::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->collisionPlayer(hcSelf, hcOther);
}


bool ColdFuzzy::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    sead::Vector3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    sead::Vector3f effectPos(effectOrigin);
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
