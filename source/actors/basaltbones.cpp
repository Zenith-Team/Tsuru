#include "tsuru/actor/bosswrapper.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "game/zonerumblemgr.h"
#include "game/actor/actormgr.h"
#include "math/functions.h"
#include "sead/mathcalccommon.h"
#include "math/easing.h"
#include "log.h"

class BasaltBone : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(BasaltBone, Enemy);

public:
    BasaltBone(const ActorBuildInfo* buildInfo)
        : Enemy(buildInfo)
        , model(nullptr)
    { }

    virtual ~BasaltBone() { }

    static Actor* build(const ActorBuildInfo* buildInfo) {
        return new BasaltBone(buildInfo);
    }

    u32 onCreate() override {
        this->model = ModelWrapper::create("star_coin", "star_coinA");
    
        this->hitboxCollider.init(this, &BasaltBone::sCollisionInfo);
        this->addHitboxColliders();

        return this->onExecute();
    }

    u32 onExecute() override {
        Mtx34 mtx;
        mtx.makeRTIdx(this->rotation, this->position);
        this->model->setMtx(mtx);
        this->model->setScale(0.5f);
        this->model->updateModel();

        return 1;
    }

    u32 onDraw() override {
        DrawMgr::instance()->drawModel(this->model);
    
        return 1;
    }

    static const HitboxCollider::Info sCollisionInfo;

    ModelWrapper* model;
};

const Profile BasaltBoneProfile(&BasaltBone::build, ProfileID::BasaltBone);

const HitboxCollider::Info BasaltBone::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

class BasaltBones : public BossWrapper<18> {
    SEAD_RTTI_OVERRIDE_IMPL(BasaltBones, Boss);

public:
    enum SpawnStage {
        SpawnStage_Wait,
        SpawnStage_RumbleWait,
        SpawnStage_Rumble,
        SpawnStage_Assemble
    };

public:
    BasaltBones(const ActorBuildInfo* buildInfo);
    virtual ~BasaltBones() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void onStompDamage(StageActor* collidingActor);
    
    void initHitboxCollider() override;
    void initModels() override;
    void updateModel() override;

    static const HitboxCollider::Info sCollisionInfo;
    static const PhysicsMgr::Sensor adjacentSensor;

    DECLARE_STATE(BasaltBones, Spawning);
    DECLARE_STATE(BasaltBones, Active);
    DECLARE_STATE(BasaltBones, Disassembled);
    DECLARE_STATE(BasaltBones, Assembling);

    ModelWrapper* model;
    BasaltBone* bones[6];
    u32 spawnWait;
    SpawnStage spawnStage;
    Vec3f startPosition
    ,     targetBonePositions[6][3];
    f32 boneTimer;
    Easing boneEaser;
};

CREATE_STATE(BasaltBones, Spawning);
CREATE_STATE(BasaltBones, Active);
CREATE_STATE(BasaltBones, Disassembled);
CREATE_STATE(BasaltBones, Assembling);

const Profile BasaltBonesProfile(&BasaltBones::build, ProfileID::BasaltBones);
PROFILE_RESOURCES(ProfileID::BasaltBones, Profile::LoadResourcesAt_Course, "star_coin");

const HitboxCollider::Info BasaltBones::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &Enemy::collisionCallback
};

const PhysicsMgr::Sensor BasaltBones::adjacentSensor = {
    8.0f, -8.0f, 16.0f
};

Actor* BasaltBones::build(const ActorBuildInfo* buildInfo) {
    return new BasaltBones(buildInfo);
}

BasaltBones::BasaltBones(const ActorBuildInfo* buildInfo)
    : BossWrapper<18>(buildInfo)
    , model(nullptr)
    , bones()
    , spawnWait(0)
    , spawnStage(SpawnStage_Wait)
    , startPosition()
    , boneTimer()
    , boneEaser()
{ }

u32 BasaltBones::onCreate() {
    this->startPosition = this->position;

    this->doStateChange(&BasaltBones::StateID_Spawning);

    return BossWrapper<18>::onCreate();
}

u32 BasaltBones::onExecute() {
    this->states.execute();
    this->updateModelTrampoline();

    return 1;
}

u32 BasaltBones::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 0;
}

void BasaltBones::initHitboxCollider() {
    this->hitboxCollider.init(this, &BasaltBones::sCollisionInfo);
}

void BasaltBones::initModels() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");
}

void BasaltBones::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();
}

void BasaltBones::onStompDamage(StageActor* collidingActor) {
    BossWrapper<18>::onStompDamage(collidingActor);

    this->doStateChange(&BasaltBones::StateID_Disassembled);
}

/** STATE: Spawning */

void BasaltBones::beginState_Spawning() {
    this->removeHitboxColliders();
    this->isVisible = false;

    this->targetBonePositions[0][0] = this->position + Vec3f(0, -3*16, 0);
    this->targetBonePositions[0][1] = this->position + Vec3f(0, 0, 0);
    this->targetBonePositions[0][2] = this->position + Vec3f(0, 3*16, 0);

    this->targetBonePositions[1][0] = this->position + Vec3f(0, -3*16, 0);
    this->targetBonePositions[1][1] = this->position + Vec3f(0, 0, 0);
    this->targetBonePositions[1][2] = this->position + Vec3f(0, 8*16, 0);

    this->targetBonePositions[2][0] = this->position + Vec3f(5*16, -3*16, 0);
    this->targetBonePositions[2][1] = this->position + Vec3f(5*16, 7*16, 0);
    this->targetBonePositions[2][2] = this->position + Vec3f(2*16, 7*16, 0);

    this->targetBonePositions[3][0] = this->position + Vec3f(-5*16, -3*16, 0);
    this->targetBonePositions[3][1] = this->position + Vec3f(-5*16, 7*16, 0);
    this->targetBonePositions[3][2] = this->position + Vec3f(-2*16, 7*16, 0);

    this->targetBonePositions[4][0] = this->position + Vec3f(8*16, -3*16, 0);
    this->targetBonePositions[4][1] = this->position + Vec3f(8*16, 5*16, 0);
    this->targetBonePositions[4][2] = this->position + Vec3f(3*16, 5*16, 0);

    this->targetBonePositions[5][0] = this->position + Vec3f(-8*16, -3*16, 0);
    this->targetBonePositions[5][1] = this->position + Vec3f(-8*16, 5*16, 0);
    this->targetBonePositions[5][2] = this->position + Vec3f(-3*16, 5*16, 0);

    for (u32 i = 0; i < 6; i++) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(ProfileID::BasaltBone);
        
        f32 left = i % 2 == 0 ? -1.0f : 1.0f;

        buildInfo.position = targetBonePositions[i][0];

        this->bones[i] = (BasaltBone*)ActorMgr::instance()->create(buildInfo, 0);
        this->bones[i]->removeHitboxColliders();
    }

    this->spawnWait = 63 * 6;

    this->boneEaser.set(Easing::quadInOut, 0.0f, 1.0f, 0.01f);
}

void BasaltBones::executeState_Spawning() {
    switch (this->spawnStage) {
        case SpawnStage_Wait: {
            if (--this->spawnWait == 0) {
                this->spawnStage = SpawnStage_Rumble;
                this->spawnWait = 60 * 2;
            }

            break;
        }

        case SpawnStage_Rumble: {
            ZoneRumbleMgr::instance()->rumble(1);

            if (--this->spawnWait == 0) {
                this->spawnStage = SpawnStage_RumbleWait;
                this->spawnWait = 63 * 5;
            }
            
            break;
        }

        case SpawnStage_RumbleWait: {
            if (--this->spawnWait == 0) {
                this->spawnStage = SpawnStage_Rumble;
            }

            this->boneEaser.ease(this->boneTimer);
            
            for (u32 i = 0; i < 6; i++) {
                Vec3f delta = this->bones[i]->position;

                Vec3f a = this->targetBonePositions[i][0]; a.lerp(this->targetBonePositions[i][1], this->boneTimer);
                Vec3f b = this->targetBonePositions[i][1]; b.lerp(this->targetBonePositions[i][2], this->boneTimer);
                Vec3f pos = a; pos.lerp(b, this->boneTimer);

                this->bones[i]->position = pos;

                delta = this->bones[i]->position - delta;
                this->bones[i]->rotation.z += fixDeg(0.1f + delta.length() * 3.0f);
            }
            
            break;
        }

        case SpawnStage_Assemble: {
            this->doStateChange(&BasaltBones::StateID_Active);
            break;
        }
    }
}

void BasaltBones::endState_Spawning() {
    this->isVisible = true;
    this->physicsMgr.init(this, nullptr, nullptr, &BasaltBones::adjacentSensor);

    for (u32 i = 0; i < 6; i++) {
        this->bones[i] = nullptr;
    }

    this->finishedSpawning();
}

/** STATE: Active */

void BasaltBones::beginState_Active() {
    this->direction = Direction::Right;
}

void BasaltBones::executeState_Active() {
    this->physicsMgr.processCollisions();
    LOG("AAAA%dAAAA", this->physicsMgr.output);

    if (this->physicsMgr.isCollidedLeft() || this->physicsMgr.isCollidedRight()) {
        this->direction = Direction::opposite((Direction::DirectionType)this->direction);
    }

    this->position.x + this->direction == Direction::Right ? this->position.x += 1.0f : this->position.x -= 1.0f;
}

void BasaltBones::endState_Active() { }

/** STATE: Disassembled */

void BasaltBones::beginState_Disassembled() {
    this->removeHitboxColliders();
    this->isVisible = false;
    
    for (u32 i = 0; i < 6; i++) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(ProfileID::BasaltBone);
        buildInfo.position = this->position;
    
        this->bones[i] = (BasaltBone*)ActorMgr::instance()->create(buildInfo, 0);
        this->bones[i]->removeHitboxColliders();
    }
}

void BasaltBones::executeState_Disassembled() {
    this->boneTimer++;

    for (u32 i = 0; i < 6; i++) {
        bool left = i % 2 == 0;

        this->bones[i]->position.x += tanf(this->boneTimer * (i) * 0.001f) * (left ? -1.0f : 1.0f);
        this->bones[i]->position.y --;
    }

    static const f32 threshold = 16.0f * 5.0f;

    if (
        this->bones[0]->position.y - this->position.y > threshold &&
        this->bones[1]->position.y - this->position.y > threshold &&
        this->bones[2]->position.y - this->position.y > threshold &&
        this->bones[3]->position.y - this->position.y > threshold &&
        this->bones[4]->position.y - this->position.y > threshold &&
        this->bones[5]->position.y - this->position.y > threshold
    ) {
        this->doStateChange(&BasaltBones::StateID_Assembling);
    }
}

void BasaltBones::endState_Disassembled() { }

/** STATE: Assembling */

void BasaltBones::beginState_Assembling() { }
void BasaltBones::executeState_Assembling() { }
void BasaltBones::endState_Assembling() { }
