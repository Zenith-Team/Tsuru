#include "game/actor/stage/enemy.h"
#include "game/graphics/model/modelnw.h"
#include "game/movementhandler.h"
#include "game/effect/effect.h"
#include "game/graphics/model/animation.h"

class Biddybud : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(Biddybud, Enemy);

public:
    Biddybud(const ActorBuildInfo* buildInfo);
    virtual ~Biddybud() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

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
    u32 counter;
    MovementHandler movementHandler;
    bool isDead;
    u32 color;
    Vec3f effectScale;
    Vec3f effectOffset;

    DECLARE_STATE(Biddybud, Move);
    DECLARE_STATE(Biddybud, Die);
    DECLARE_STATE(Biddybud, DieSquish);
};

CREATE_STATE(Biddybud, Move);
CREATE_STATE(Biddybud, Die);
CREATE_STATE(Biddybud, DieSquish);

const Profile BiddybudProfile(&Biddybud::build, ProfileID::Biddybud);
PROFILE_RESOURCES(ProfileID::Biddybud, Profile::LoadResourcesAt::Course, "tenten_w");

HitboxCollider::Info Biddybud::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0xFFFBFFFF, 0, &Enemy::collisionCallback
};

Biddybud::Biddybud(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , counter(0)
    , movementHandler()
    , isDead(false)
    , color(0)
    , effectScale(0.5, 0.5, 0.5)
    , effectOffset(0, 0, 0)
{ }

Actor* Biddybud::build(const ActorBuildInfo* buildInfo) {
    return new Biddybud(buildInfo);
}

u32 Biddybud::onCreate() {
    this->color = (this->settings1 >> 0x1C & 0xF); // nybble 5

    this->model = ModelWrapper::create("tenten_w", "tenten_w", 3, 1, 1);
    this->model->playTexPatternAnim("bud", 0);
    this->model->playTexSrtAnim("FlyWait", 0);
    this->model->playSklAnim("FlyWait");
    this->model->texPatternAnims[0]->frameCtrl.startFrame = this->color;
    this->model->texPatternAnims[0]->frameCtrl.speed = 0.0;
    this->model->texSrtAnims[0]->frameCtrl.shouldLoop(true);
    this->model->loopSklAnims(true);
    this->scale = .17f;
    this->position.y -= 8;
    this->position.x += 8;

    this->hitboxCollider.init(this, &Biddybud::collisionInfo);
    this->addHitboxColliders();

    // this->movementID = (this->movementID & 0xFF); // 21-22
    // this->movementID >> 0x4 & 0xF

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF); // nybble 20
    this->movementHandler.link(this->position, movementMask, this->movementID); // nybble 21-22

    this->doStateChange(&Biddybud::StateID_Move);

    return this->onExecute();
}

u32 Biddybud::onExecute() {
    if (!this->isDead) {
        this->movementHandler.execute();
        this->position = this->movementHandler.position;
    }

    this->states.execute();

    Mtx34 mtx;
    Vec3f modelPos = this->position;
    modelPos.y -= 8;
    mtx.makeRTIdx(this->rotation, modelPos);
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();

    return 1;
}

u32 Biddybud::onDraw() {
    this->model->draw();

    return 1;
}

void Biddybud::collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    } else if (hitType == HitType::NormalJump || hitType == HitType::SpinJump) {
        this->killPlayerJump(hcOther->owner, 0.0f, &Biddybud::StateID_DieSquish);
    }
}

void Biddybud::collisionYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    u32 hitType = this->processCollision(hcSelf, hcOther, 0);

    if (hitType == HitType::Collide) {
        this->damagePlayer(hcSelf, hcOther);
    }

    if (hitType == HitType::NormalJump) {
        this->collisionStar(hcSelf, hcOther);
    }
}

bool Biddybud::collisionGroundPound(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    return this->collisionStar(hcSelf, hcOther);
}

bool Biddybud::collisionStar(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin + this->effectOffset);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);
    this->isDeleted = true;

    return 1;
}

bool Biddybud::collisionSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    this->doStateChange(&Biddybud::StateID_Die);

    return 1;
}

bool Biddybud::collisionPenguinSlide(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    doStateChange(&Biddybud::StateID_Die);

    return 1;
}

bool Biddybud::collisionGroundPoundYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Biddybud::collisionStar(hcSelf, hcOther);

    return 1;
}

bool Biddybud::collisionPropellerDrill(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Biddybud::collisionStar(hcSelf, hcOther);

    return 1;
}

bool Biddybud::collisionThrowableObject(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
    Vec3f effectPos(effectOrigin + this->effectOffset);
    Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);
    this->isDeleted = true;

    return 1;
}

bool Biddybud::collisionFireball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Enemy::collisionFireball(hcSelf, hcOther);
    while (this->counter < 32) {
        this->counter++;
    }

    return Biddybud::collisionStar(hcSelf, hcOther);
}

bool Biddybud::collisionIceball(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Biddybud::collisionStar(hcSelf, hcOther);

    return 1;
}

bool Biddybud::collisionFireballYoshi(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    Biddybud::collisionFireball(hcSelf, hcOther);

    return 1;
}

/** STATE: Move */

void Biddybud::beginState_Move() {
    this->counter = 0;
}

void Biddybud::executeState_Move() { }

void Biddybud::endState_Move() { }

/** STATE: Die */

void Biddybud::beginState_Die() {
    // this->isDeleted = true;
    this->model->playSklAnim("BlowDown");
    this->model->loopSklAnims(false);
    this->isDead = true;
    this->removeHitboxColliders();
}

void Biddybud::executeState_Die() {
    this->counter++;
    if (this->counter == 32) { // until there's an "is animation done" function that i'm aware of, i'll just use this
        Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
        Vec3f effectPos(effectOrigin + this->effectOffset);
        Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);
        this->isDeleted = true;
    }
}

void Biddybud::endState_Die() { }

/** STATE: DieSquish */

void Biddybud::beginState_DieSquish() {
    // this->isDeleted = true;
    // this->model->playSklAnim("PressDown");
    this->model->playSklAnim("BlowDown");
    this->model->loopSklAnims(false);
    this->isDead = true;
    this->removeHitboxColliders();
}

void Biddybud::executeState_DieSquish() {
    this->counter++;
    if (this->counter == 32) {
        Vec3f effectOrigin(this->position.x, this->position.y, 4500.0f);
        Vec3f effectPos(effectOrigin + this->effectOffset);
        Effect::spawn(RP_Jugemu_CloudDisapp, &effectPos, nullptr, &this->effectScale);
        this->isDeleted = true;
    }
}

void Biddybud::endState_DieSquish() { }
// plans to make a grounded one? maybe.
