#include "game/actor/stage/enemy.h"
#include "game/actor/actormgr.h"
#include "game/direction.h"
#include "game/graphics/drawmgr.h"
#include "game/util.h"
#include "log.h"
#include "tsuru/utils.h"
#include "math/functions.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/rectcollider.h"

class Cataquack : public Enemy {
public:
    Cataquack(const ActorBuildInfo* buildInfo);
    virtual ~Cataquack() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();
    void beginChase();
    void endChase();

    static const HitboxCollider::Info collisionInfo;
    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    RectCollider rectCollider;
    ModelWrapper* model;
    bool chasing;

    StageActor* target;
    f32 targetInitialY;
    f32 launchHeight;

    DECLARE_STATE(Cataquack, Walk);
    DECLARE_STATE(Cataquack, Turn);
    DECLARE_STATE(Cataquack, Launch);
};
CREATE_STATE(Cataquack, Walk);
CREATE_STATE(Cataquack, Turn);
CREATE_STATE(Cataquack, Launch);

const ActorInfo CataquackActorInfo = {
    Vec2i(8, -8), Vec2i(8, -8), Vec2i(32, 32), 0, 0, 0, 0, 0
};
const Profile CataquackProfile(&Cataquack::build, ProfileID::Cataquack, "Cataquack", &CataquackActorInfo, Profile::Flag_DontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::Cataquack, Profile::LoadResourcesAt_Course, "poihana");

Cataquack::Cataquack(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , chasing(false)
    , target(nullptr)
    , targetInitialY(0.0f)
    , launchHeight(128.0f)
{ };

Actor* Cataquack::build(const ActorBuildInfo* buildInfo) {
    return new Cataquack(buildInfo);
}

const HitboxCollider::Info Cataquack::collisionInfo = {
    Vec2f(0.0f, 14.0f), Vec2f(11.0f, 14.0f), HitboxCollider::HitboxShape_Rectangle, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Cataquack::collisionCallback
};

u32 Cataquack::onCreate() {
    this->model = ModelWrapper::create("poihana", "poihana", 3);
    this->scale.x = 0.1f;
    this->scale.y = 0.1f;
    this->scale.z = 0.1f;
    this->model->playSklAnim("walk", 0);
    this->model->sklAnims[0]->shouldLoop(true);

    PhysicsMgr::Sensor belowSensor = { -6,  6,  0 };
    PhysicsMgr::Sensor aboveSensor = { -6,  6, 28 };
    PhysicsMgr::Sensor sidesSensor = {  8, 24, 12 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sidesSensor);

    this->direction = this->directionToPlayerH(this->position);
    this->rotation.y = Direction::directionToRotationList[this->direction];

    this->hitboxCollider.init(this, &Cataquack::collisionInfo, nullptr);
    this->addHitboxColliders();

    ShapedCollider::Info colliderInfo = {
        Vec2f(0.0f, 14.0f), 0.0f, 0.0f, Vec2f(-5.5f, 10.0f), Vec2f(5.5f, -12.0f), 0
    };

    this->rectCollider.init(this, colliderInfo);
    this->rectCollider.setType(ColliderBase::Type_Bouncy);
    //ColliderMgr::instance()->add(&rectCollider);

    this->doStateChange(&Cataquack::StateID_Walk);
    this->updateModel();
    return 1;
}

u32 Cataquack::onExecute() {
    if (this->target != nullptr) {
        if (this->target->position.y > this->targetInitialY + this->launchHeight) {
            this->target->speed.y *= 0.3f;
            this->target = nullptr;
        }
    }
    this->states.execute();
    this->updateModel();
    this->offscreenDelete(0);
    this->rectCollider.execute();
    return 1;
}

u32 Cataquack::onDraw() {
    DrawMgr::instance()->drawModel(this->model);
    return 1;
}

void Cataquack::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position + Vec3f(0.0f, 20.0f, 0.0f));
    this->model->setMtx(mtx);
    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->updateModel();
}

void Cataquack::beginChase() {
    this->chasing    = true;
    this->speed.x    = this->direction == Direction::Left ? -1.0f : 1.0f;
    this->maxSpeed.x = this->direction == Direction::Left ? -1.0f : 1.0f;
    this->model->sklAnims[0]->speed = 2.0f;
}

void Cataquack::endChase() {
    this->chasing    = false;
    this->speed.x    = this->direction == Direction::Left ? -0.5f : 0.5f;
    this->maxSpeed.x = this->direction == Direction::Left ? -0.5f : 0.5f;
    this->model->sklAnims[0]->speed = 1.0f;
}

/** STATE: Walk */

void Cataquack::beginState_Walk() {
    f32 speed = this->chasing ? 1.0f : 0.5f;
    this->speed.x    = this->direction == Direction::Left ? -speed : speed;
    this->maxSpeed.x = this->direction == Direction::Left ? -speed : speed;
}

void Cataquack::executeState_Walk() {
    this->handleGravity();
    this->handleSpeed();
    this->physicsMgr.processCollisions();
    if (this->physicsMgr.isOnGround()) this->speed.y = 0.0f;

    Vec2f distToPlayer;
    if (this->distanceToPlayer(distToPlayer) > -1 && fabs(distToPlayer.x) < 8.0f * 16.0f && fabs(distToPlayer.y) < 6.0f * 16.0f) {
        if ((this->direction == Direction::Left && distToPlayer.x < 0) || (this->direction == Direction::Right && distToPlayer.x > 0)) {
            this->beginChase();
        }

        if (this->chasing) {
            if ((this->direction == Direction::Left && distToPlayer.x > 0) || (this->direction == Direction::Right && distToPlayer.x < 0)) {
                this->doStateChange(&Cataquack::StateID_Turn);
            }
        }
    } else {
        this->endChase();
    }

    if (this->physicsMgr.isOnGround()) this->speed.y = 0.0f;
    if (this->physicsMgr.isCollided(this->direction) && !this->chasing) this->doStateChange(&Cataquack::StateID_Turn);
}

void Cataquack::endState_Walk() { }

/** STATE: Turn */

void Cataquack::beginState_Turn() {
    this->direction ^= 1;
    this->speed.x    = 0.0f;
    this->maxSpeed.x = 0.0f;
}

void Cataquack::executeState_Turn() {
    this->handleGravity();
    this->handleSpeed();
    this->physicsMgr.processCollisions();
    if (this->physicsMgr.isOnGround()) this->speed.y = 0.0f;

    u32 step = this->chasing ? fixDeg(6.0f) : fixDeg(3.0f);
    if (moveValueWithOverflowTo(this->rotation.y, Direction::directionToRotationList[this->direction], step, this->direction)) {
        this->doStateChange(&Cataquack::StateID_Walk);
    }
}

void Cataquack::endState_Turn() {
    this->rotation.y = Direction::directionToRotationList[this->direction];
}

/** STATE: Launch */

void Cataquack::beginState_Launch() {
    this->direction = this->directionToPlayerH(this->position);
    this->rotation.y = Direction::directionToRotationList[this->direction];

    this->model->playSklAnim("throw", 0);
    this->model->sklAnims[0]->shouldLoop(false);
    this->speed.x = 0.0f;
    this->target->speed.y = 1.0f + this->launchHeight / 14.0f;
}

void Cataquack::executeState_Launch() {
    this->handleGravity();
    this->handleSpeed();
    this->physicsMgr.processCollisions();
    if (this->physicsMgr.isOnGround()) this->speed.y = 0.0f;
    if (this->model->sklAnims[0]->isAnimationDone()) this->doStateChange(&Cataquack::StateID_Walk);
}

void Cataquack::endState_Launch() {
    this->model->playSklAnim("walk", 0);
    this->model->sklAnims[0]->shouldLoop(true);
}

void Cataquack::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type != StageActorType_Player && hcOther->owner->type != StageActorType_Yoshi) return;
    Cataquack* self = static_cast<Cataquack*>(hcSelf->owner);

    self->target = hcOther->owner;
    self->targetInitialY = self->target->position.y;
    self->doStateChange(&Cataquack::StateID_Launch);
}
