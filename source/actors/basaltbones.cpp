#include "tsuru/actor/bosswrapper.h"
#include "game/graphics/model/model.h"
#include "game/actor/actormgr.h"
#include "game/actor/stage/player.h"
#include "game/zonerumblemgr.h"
#include "math/bezier.h"
#include "math/easing.h"
#include "log.h"

class BasaltBones : public BossWrapper<18> {
    SEAD_RTTI_OVERRIDE_IMPL(BasaltBones, Boss)

public:
    BasaltBones(const ActorBuildInfo* buildInfo);
    virtual ~BasaltBones() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onExecute() override;
    u32 onDraw() override;
    
    void initHitboxCollider() override;
    void initModels() override;
    void updateModel() override;
    void onStompDamage(StageActor*) override;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info sCollisionInfo;

    struct Bone {
        static const HitboxCollider::Info sCollisionInfo;
        static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
            if (((BasaltBones*)hcSelf->owner)->states.currentState()->ID != BasaltBones::StateID_Assemble.ID) {
                return;
            }
            
            if (hcOther->owner->type == StageActor::StageActorType_Player) {
                ((Player*)hcOther->owner)->tryDamage(hcSelf);
            }
        }

        Bone(): model(nullptr), hitbox(), bezier(), easer(), position(0,0,0), rotation(0), t(0.0f), render(false) { }
  
        ModelWrapper* model;
        HitboxCollider hitbox;
        QuadraticBezier bezier;
        Easing easer;
        Vec3f position;
        u32 rotation;
        f32 t;
        bool render;
    } bones[6];
    ModelWrapper* model;
    enum {
        SpawnStage_Wait,
        SpawnStage_Shake,
        SpawnStage_FlyOut,
        SpawnStage_Assemble
    } spawnStage;
    struct SpawnParamters {
        SpawnParamters(): down(0.0f), timer(0) { }

        f32 down;
        u32 timer;
    } spawnParams;
    Vec3f startPosition;
    u32 assembler;

    DECLARE_STATE(BasaltBones, Spawning);
    DECLARE_STATE(BasaltBones, Active);
    DECLARE_STATE(BasaltBones, Disassemble);
    DECLARE_STATE(BasaltBones, Assemble);
};

CREATE_STATE(BasaltBones, Spawning);
CREATE_STATE(BasaltBones, Active);
CREATE_STATE(BasaltBones, Disassemble);
CREATE_STATE(BasaltBones, Assemble);

const Profile BasaltBonesProfile(&BasaltBones::build, ProfileID::BasaltBones);
PROFILE_RESOURCES(ProfileID::BasaltBones, Profile::LoadResourcesAt_Course, "star_coin");

const HitboxCollider::Info BasaltBones::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &BasaltBones::collisionCallback
};

const HitboxCollider::Info BasaltBones::Bone::sCollisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::HitboxShape_Rectangle, 5, 0, 0x824F, 0x20208, 0, &BasaltBones::Bone::collisionCallback
};

Actor* BasaltBones::build(const ActorBuildInfo* buildInfo) {
    return new BasaltBones(buildInfo);
}

BasaltBones::BasaltBones(const ActorBuildInfo* buildInfo)
    : BossWrapper<18>(buildInfo)
    , model(nullptr)
    , spawnStage(SpawnStage_Wait)
    , spawnParams()
    , startPosition(buildInfo->position)
{ }

u32 BasaltBones::onExecute() {
    this->states.execute();
    this->updateModelTrampoline();

    for (u32 i = 0; i < 6; i++) {
        Bone& bone = bones[i];
        
        bone.rotation += fixDeg(1.0f);
    }

    return 1;
}

u32 BasaltBones::onDraw() {
    if (this->states.currentState()->ID == StateID_Active.ID) {
        this->model->draw();
    }


    for (u32 i = 0; i < 6; i++) {
        if (this->bones[i].render) {
            this->bones[i].model->draw();
        }
    }

    return 0;
}

void BasaltBones::initHitboxCollider() {
    this->hitboxCollider.init(this, &BasaltBones::sCollisionInfo);
    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
    
        bone.hitbox.init(this, &BasaltBones::Bone::sCollisionInfo);
        HitboxColliderMgr::instance()->safeAddToCreateList(&bone.hitbox);
    }
}

void BasaltBones::initModels() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");
    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
    
        bone.model = ModelWrapper::create("star_coin", "star_coinA");
        bone.position = this->position;
    }

    this->doStateChange(&BasaltBones::StateID_Spawning);
}

void BasaltBones::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->setScale(1);
    this->model->updateModel();

    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
    
        Mtx34 mtx;
        mtx.makeRTIdx(Vec3u(0, 0, bone.rotation), bone.position);
        bone.model->setScale(0.5f);
        bone.model->setMtx(mtx);
        bone.model->updateModel();
    }
}

void BasaltBones::onStompDamage(StageActor* collidingActor) {
    this->doStateChange(&BasaltBones::StateID_Disassemble);

    return BossWrapper<18>::onStompDamage(collidingActor);
}

void BasaltBones::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (((BasaltBones*)hcSelf->owner)->states.currentState()->ID != BasaltBones::StateID_Active.ID) {
        return;
    }

    return BossWrapper<18>::collisionCallback(hcSelf, hcOther);
}

/** STATE: Spawning */

void BasaltBones::beginState_Spawning() {
    this->bones[0].bezier.set(this->position + Vec3f(0, -3*16, 0),      this->position + Vec3f(0, 0, 0),         this->position + Vec3f(-19.6, 82.3, 0));
    this->bones[1].bezier.set(this->position + Vec3f(0, -3*16, 0),      this->position + Vec3f(0, 0, 0),         this->position + Vec3f(0.3, 70.8, 0));
    this->bones[2].bezier.set(this->position + Vec3f(5*16, -3*16, 0),   this->position + Vec3f(5*16, 7*16, 0),   this->position + Vec3f(19.3, 81.8, 0));
    this->bones[3].bezier.set(this->position + Vec3f(-5*16, -3*16, 0),  this->position + Vec3f(-5*16, 7*16, 0),  this->position + Vec3f(19.6, 104.3, 0));
    this->bones[4].bezier.set(this->position + Vec3f(8*16, -3*16, 0),   this->position + Vec3f(8*16, 5*16, 0),   this->position + Vec3f(0.3, 115.8, 0));
    this->bones[5].bezier.set(this->position + Vec3f(-8*16, -3*16, 0),  this->position + Vec3f(-8*16, 5*16, 0),  this->position + Vec3f(-19.3, 104.8, 0));

    for (u32 i = 0; i < 6; i++) {
        this->bones[i].easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.0075f);
    }

    this->spawnParams.timer = 63 * 6;
}

void BasaltBones::executeState_Spawning() {
    switch (this->spawnStage) {
        case SpawnStage_Wait: {
            if (--this->spawnParams.timer == 0) {
                this->spawnStage = SpawnStage_Shake;
                this->spawnParams.timer = 60 * 2;
            }
            
            break;
        }

        case SpawnStage_Shake: {
            ZoneRumbleMgr::instance()->rumble(1);

            if (--this->spawnParams.timer == 0) {
                this->spawnStage = SpawnStage_FlyOut;
                this->spawnParams.timer = 63 * 5;
            }

            break;
        }

        case SpawnStage_FlyOut: {
            for (u32 i = 0; i < 6; i++) {
                Bone& bone = this->bones[i];
                
                bone.render = true;
                bool done = bone.easer.ease(bone.t);
                bone.bezier.execute(&bone.position, bone.t);
            
                if (done) {
                    this->spawnStage = SpawnStage_Assemble;
                    bone.easer.set(Easing::cubicIn, 360.0f, 0.0f, 0.004f);
                }
            }

            break;
        }

        case SpawnStage_Assemble: {
            Vec3f centerPoint = (this->bones[0].bezier.keyframes[2] + this->bones[1].bezier.keyframes[2] + this->bones[2].bezier.keyframes[2] + this->bones[3].bezier.keyframes[2] + this->bones[4].bezier.keyframes[2] + this->bones[5].bezier.keyframes[2]) / 6;
            this->spawnParams.down += 0.0014 * this->bones[0].t;
            centerPoint.y -= this->spawnParams.down;

            for (u32 i = 0; i < 6; i++) {
                Bone& bone = this->bones[i];
                
                bool done = bone.easer.ease(bone.t);
                bone.position.x = centerPoint.x + (bone.t / 16) * cosf(bone.t / 16 + i * M_PI / 3.0f);
                bone.position.y = centerPoint.y + (bone.t / 16) * sinf(bone.t / 16 + i * M_PI / 3.0f);
            
                if (done) {
                    this->doStateChange(&BasaltBones::StateID_Active);
                    bone.render = false;
                }
            }

            break;
        }
    }
}

void BasaltBones::endState_Spawning() {
    this->finishedSpawning();
}

/** STATE: Active */

void BasaltBones::beginState_Active() {
    this->direction = Direction::Right;
}

void BasaltBones::executeState_Active() {
    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[Direction::opposite((Direction::DirectionType)this->direction)], fixDeg(6.0f));

    static const float threshold = 120.0f;

    if (this->position.x - this->startPosition.x < -threshold) {
        this->direction = Direction::Left;
    } else if (this->position.x - this->startPosition.x > threshold) {
        this->direction = Direction::Right;
    }

    if (this->direction == Direction::Left) {
        this->position.x++;
    } else {
        this->position.x--;
    }
}

void BasaltBones::endState_Active() { }

/** STATE: Disassemble */

void BasaltBones::beginState_Disassemble() {
    this->bones[0].bezier.set(this->position, this->position + Vec3f(0, 0, 0), this->position + Vec3f(0, -3*16, 0));
    this->bones[1].bezier.set(this->position, this->position + Vec3f(0, 0, 0), this->position + Vec3f(0, -3*16, 0));
    this->bones[2].bezier.set(this->position, this->position + Vec3f(3*16, 3*16, 0), this->position + Vec3f(3*16, -7*16, 0));
    this->bones[3].bezier.set(this->position, this->position + Vec3f(-3*16, 3*16, 0), this->position + Vec3f(-3*16, -7*16, 0));
    this->bones[4].bezier.set(this->position, this->position + Vec3f(5*16, 1*16, 0), this->position + Vec3f(5*16, -7*16, 0));
    this->bones[5].bezier.set(this->position, this->position + Vec3f(-5*16, 1*16, 0), this->position + Vec3f(-5*16, -7*16, 0));
    
    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
        
        bone.easer.set(Easing::quadIn, 0.0f, 1.0f, 0.03f);
    }
}

void BasaltBones::executeState_Disassemble() {
    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
        bone.render = true;
        
        bool done = bone.easer.ease(bone.t);
        bone.bezier.execute(&bone.position, bone.t);
    
        if (done) {
            bone.render = false;
            this->doStateChange(&BasaltBones::StateID_Assemble);
        }
    }
}

void BasaltBones::endState_Disassemble() { }

/** STATE: Assemble */

void BasaltBones::beginState_Assemble() {
    this->assembler = 0;

    this->bones[0].bezier.set(this->position + Vec3f(0, -16*3, 0), this->position + Vec3f(0, 2*16, 0), this->position + Vec3f(0, 4*16, 0));
    this->bones[0].render = true;
    this->bones[0].easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.006f);
}

void BasaltBones::executeState_Assemble() {
    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
        bone.hitbox.colliderInfo.distToCenter = Vec2f(bone.position.x - this->position.x, bone.position.y - this->position.y);
    }

    // Launch
    if (this->assembler < 6) {
        Bone& bone1 = this->bones[this->assembler];
        bool bone1done = bone1.easer.ease(bone1.t);
        bone1.bezier.execute(&bone1.position, bone1.t);
        if (bone1done) {
            this->assembler++;
            Bone& bone1next = this->bones[this->assembler];
            bone1next.render = true;
            bone1next.easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.006f);
            bone1next.bezier.set(this->position + Vec3f(0, -16*3, 0), this->position + Vec3f(0, 2*16, 0), this->position + Vec3f(this->assembler*16, 4*16, 0));

            bone1.bezier.set(bone1.position, this->position + Vec3f(0, 2*16, 0), this->position);
            bone1.easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.006f);
        }
    }

    // Assemble
    if (this->assembler > 0) {
        Bone& bone2 = this->bones[this->assembler - 1];

        bool done = bone2.easer.ease(bone2.t);
        bone2.bezier.execute(&bone2.position, bone2.t);

        if (this->assembler == 6 && done) {
            this->doStateChange(&BasaltBones::StateID_Active);
        }
    }
}

void BasaltBones::endState_Assemble() {
    for (u32 i = 0; i < 6; i++) {
        this->bones[i].render = false;
    }
}
