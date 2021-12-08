#include <game/actor/stage/enemy.h>
#include <game/actor/actormgr.h>
#include <game/direction.h>
#include <game/graphics/drawmgr.h>
#include <game/util.h>
#include <log.h>
#include <tsuru/utils.h>
#include <math/functions.h>

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

    ModelWrapper* model;
    bool chasing;

    DECLARE_STATE(Cataquack, Walk);
    DECLARE_STATE(Cataquack, Turn);
    //DECLARE_STATE(Cataquack, Launch);
};
CREATE_STATE(Cataquack, Walk);
CREATE_STATE(Cataquack, Turn);
//CREATE_STATE(Cataquack, Launch);

const ActorInfo CataquackActorInfo = {
    Vec2i(8, -8), Vec2i(8, -8), Vec2i(32, 32), 0, 0, 0, 0, 0
};
const Profile CataquackProfile(&Cataquack::build, ProfileID::Cataquack, "Cataquack", &CataquackActorInfo, Profile::Flag_DontRenderOffScreen);
PROFILE_RESOURCES(ProfileID::Cataquack, "poihana");

Cataquack::Cataquack(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , chasing(false)
{ };

Actor* Cataquack::build(const ActorBuildInfo* buildInfo) {
    return new Cataquack(buildInfo);
}

u32 Cataquack::onCreate() {
    this->model = ModelWrapper::create("poihana", "poihana", 3);
    this->scale.x = 0.1f;
    this->scale.y = 0.1f;
    this->scale.z = 0.1f;
    this->model->playSklAnim("walk", 0);

    PhysicsMgr::Sensor belowSensor = { -6,  6,  0 };
    PhysicsMgr::Sensor aboveSensor = { -6,  6, 28 };
    PhysicsMgr::Sensor sidesSensor = {  8, 24, 12 };
    this->physicsMgr.init(this, &belowSensor, &aboveSensor, &sidesSensor);

    this->direction = this->directionToPlayerH(this->position);
    this->rotation.y = Direction::directionToRotationList[this->direction];

    this->doStateChange(&Cataquack::StateID_Walk);
    this->updateModel();
    return 1;
}

u32 Cataquack::onExecute() {
    this->states.execute();
    this->updateModel();
    this->deleteActorWhenOutOfView(0); //! UNTESTED
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

/* STATE: Walk */

void Cataquack::beginState_Walk() {
    f32 speed = this->chasing ? 1.0f : 0.5f;
    this->speed.x    = this->direction == Direction::Left ? -speed : speed;
    this->maxSpeed.x = this->direction == Direction::Left ? -speed : speed;
}

void Cataquack::executeState_Walk() {
    this->handleGravity();
    this->handleSpeed();
    this->physicsMgr.processCollisions();

    Vec2f distToPlayer;
    if (this->distanceToPlayer(distToPlayer) > -1 && fabsf(distToPlayer.x) < 8.0f * 16.0f && fabsf(distToPlayer.y) < 6.0f * 16.0f) {
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

/* STATE: Turn */

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

void Cataquack::beginChase() {
    this->chasing    = true;
    this->speed.x    = this->direction == Direction::Left ? -1.0f : 1.0f;
    this->maxSpeed.x = this->direction == Direction::Left ? -1.0f : 1.0f;
    this->model->sklAnims[0]->speed = 2.0f;
}

    //Vec2f distToPlayer;
    //if (this->distanceToPlayer(distToPlayer) < 0 || (fabs(distToPlayer.x) > 8.0f * 16.0f || fabs(distToPlayer.y) > 6.0f * 16.0f)) {
    //    if ((this->direction == Direction::Left && distToPlayer.x < 0) || (this->direction == Direction::Right && distToPlayer.x > 0)) {
    //        this->doStateChange(&Cataquack::StateID_Walk);

void Cataquack::endChase() {
    this->chasing    = false;
    this->speed.x    = this->direction == Direction::Left ? -0.5f : 0.5f;
    this->maxSpeed.x = this->direction == Direction::Left ? -0.5f : 0.5f;
    this->model->sklAnims[0]->speed = 1.0f;
}
