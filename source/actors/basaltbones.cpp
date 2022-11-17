#include "tsuru/actor/bosswrapper.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/actormgr.h"
#include "game/actor/stage/player.h"
#include "game/zonerumblemgr.h"
#include "game/effect/effect.h"
#include "game/effect/effectid.h"
#include "game/graphics/lightsource.h"
#include "game/actor/stage/envterrain.h"
#include "game/sound/sound.h"
#include "tsuru/heatdistorter.h"
#include "game/tilemgr.h"
#include "math/bezier.h"
#include "math/easing.h"
#include "sead/random.h"
#include "log.h"

class BasaltBoneProjectile : public Enemy {
    SEAD_RTTI_OVERRIDE_IMPL(BasaltBoneProjectile, Enemy);

public:
    BasaltBoneProjectile(const ActorBuildInfo* buildInfo) : Enemy(buildInfo), effect() { }
    virtual ~BasaltBoneProjectile() { }

    static Actor* build(const ActorBuildInfo* buildInfo) {
        return new BasaltBoneProjectile(buildInfo);
    }

    u32 onCreate() override {
        this->hitboxCollider.init(this, &BasaltBoneProjectile::collisionInfo);
        this->addHitboxColliders();

        this->offscreenDelete(true);

        Vec3u r; Vec3f s(1);

        this->timer = 0;

        return this->onExecute();
    }

    u32 onExecute() override {
        this->position.x += this->direction ? -2.0f : 2.0f;

        Vec3u r; Vec3f s(1);
        this->effect.update(rp_Jr_FireBall, &this->position, &r, &s);

        if (++this->timer > 520) {
            this->isDeleted = true;
        }

        return 1;
    }

    static const HitboxCollider::Info collisionInfo;

    EffectWrapper effect;
    u32 timer;
};

class BasaltBones : public BossWrapper<18> {
    SEAD_RTTI_OVERRIDE_IMPL(BasaltBones, Boss);

public:
    ENUM_CLASS(SpawnStage,
        Wait,
        Shake,
        FlyOut,
        Assemble
    );

    class Bone {
    public:
        Bone(): model(nullptr), hitbox(), bezier(), easer(), position(0), rotation(0), t(0), render(false) { }

        void draw() {
            if (this->render) {
                this->model->draw();
            }
        }

        static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
            BasaltBones* self = (BasaltBones*)hcSelf->owner;

            if (self->states.currentState()->ID != StateID_Assemble.ID && self->states.currentState()->ID != StateID_AssembleFinalize.ID) {
                return;
            }

            if (hcOther->owner->type == StageActor::Type::Player) {
                ((Player*)hcOther->owner)->tryDamage(hcSelf);
            }
        }

        static const HitboxCollider::Info collisionInfo;

        ModelWrapper* model;
        HitboxCollider hitbox;
        QuadraticBezier bezier;
        Easing easer;
        Vec3f position;
        Vec3u rotation;
        f32 t;
        bool render;
    };

public:
    BasaltBones(const ActorBuildInfo* buildInfo);
    virtual ~BasaltBones() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void initHitboxCollider() override;
    void initModels() override;
    void updateModel() override;
    void onStompDamage(StageActor*) override;
    void onStompKill(StageActor*) override;

    u32 fireDamageAmount() override { return 0; }

    static const HitboxCollider::Info collisionInfo;

    static const Vec3f launchKeyframes[6][2][3];

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    ModelWrapper* model;
    Vec3f startPosition;
    SpawnStage::__type__ spawnStage;
    Bone bones[6];
    union { u32 timer, assembler; };
    f32 down;
    bool dead, draw, first, threw;
    EnvTerrain* lava;
    HeatDistorter heat;
    EffectWrapper flames;
    Vec3f flamesScale;

    DECLARE_STATE(BasaltBones, Spawn);
    DECLARE_STATE(BasaltBones, Active);
    DECLARE_STATE(BasaltBones, Throw);
    DECLARE_STATE(BasaltBones, Disassemble);
    DECLARE_STATE(BasaltBones, Assemble);
    DECLARE_STATE(BasaltBones, AssembleFinalize);
};

CREATE_STATE(BasaltBones, Spawn);
CREATE_STATE(BasaltBones, Active);
CREATE_STATE(BasaltBones, Throw);
CREATE_STATE(BasaltBones, Disassemble);
CREATE_STATE(BasaltBones, Assemble);
CREATE_STATE(BasaltBones, AssembleFinalize);

const Profile BasaltBonesProfile(&BasaltBones::build, ProfileID::BasaltBones);
PROFILE_RESOURCES(ProfileID::BasaltBones, Profile::LoadResourcesAt::Course, "laron", "star_coin");

const Profile BasaltBoneProjectileProfile(&BasaltBoneProjectile::build, ProfileID::BasaltBoneProjectile);

const HitboxCollider::Info BasaltBones::collisionInfo = {
    Vec2f(0.0f, 6.0f), Vec2f(14.0f, 22.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &BasaltBones::collisionCallback
};

const HitboxCollider::Info BasaltBones::Bone::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &BasaltBones::Bone::collisionCallback
};

const HitboxCollider::Info BasaltBoneProjectile::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &BasaltBoneProjectile::collisionCallback
};

static const f32 __x16(const f32 x) { return x * 16.f; }

#define b __x16

const Vec3f BasaltBones::launchKeyframes[6][2][3] = { // 6 bones, 2 possible paths each containing 3 positions
    {
        { Vec3f(b(-9), b(-3)), Vec3f(b(-9), b(3)), Vec3f(b(-9), b(8)) },
        { Vec3f(b(-9), b(-3)), Vec3f(b(-4), b(3)), Vec3f(b(-9), b(8)) }
    },
    {
        { Vec3f(b(-5), b(-3)), Vec3f(b(-2), b(3)), Vec3f(b(-5), b(8)) },
        { Vec3f(b(-9), b(-3)), Vec3f(b(-8), b(3)), Vec3f(b(-5), b(8)) }
    },
    {
        { Vec3f(b(-2), b(-3)), Vec3f(b(-2), b(6)), Vec3f(b(2),  b(8)) },
        { Vec3f(b(-2), b(-3)), Vec3f(b(2),  b(6)), Vec3f(b(2),  b(8)) }
    },
    {
        { Vec3f(b(2),  b(-3)), Vec3f(b(2),  b(6)), Vec3f(b(-2), b(8)) },
        { Vec3f(b(2),  b(-3)), Vec3f(b(-2), b(6)), Vec3f(b(-2), b(8)) }
    },
    {
        { Vec3f(b(5),  b(-3)), Vec3f(b(2),  b(3)), Vec3f(b(5),  b(8)) },
        { Vec3f(b(5),  b(-3)), Vec3f(b(8),  b(3)), Vec3f(b(5),  b(8)) }
    },
    {
        { Vec3f(b(9),  b(-3)), Vec3f(b(9),  b(3)), Vec3f(b(9),  b(8)) },
        { Vec3f(b(9),  b(-3)), Vec3f(b(4),  b(3)), Vec3f(b(9),  b(8)) }
    }
};

#undef b

static f32 defaultWaveRippleHeight = 0;
static u32 defaultWaveHorizontalSpeed = 0;

Actor* BasaltBones::build(const ActorBuildInfo* buildInfo) {
    return new BasaltBones(buildInfo);
}

BasaltBones::BasaltBones(const ActorBuildInfo* buildInfo)
    : BossWrapper<18>(buildInfo)
    , model(nullptr)
    , startPosition()
    , spawnStage(SpawnStage::Wait)
    , bones()
    , timer(0)
    , down(0.0f)
    , dead(false)
    , draw(false)
    , threw(false)
    , lava(nullptr)
    , heat()
{ }

u32 BasaltBones::onCreate() {
    this->startPosition = this->position;

    this->doStateChange(&StateID_Spawn);

    for (Actor** i = ActorMgr::instance()->actors.start.buffer; i < ActorMgr::instance()->actors.end.buffer; i++) {
        if ((*i) != nullptr && (*i)->getProfileID() == ProfileID::Lava) {
            this->lava = (EnvTerrain*) * i;
            return BossWrapper<18>::onCreate();
        }
    }

    PRINT("BasaltBones: Couldn't find lava!");

    return BossWrapper<18>::onCreate();
}

u32 BasaltBones::onExecute() {
    this->states.execute();
    this->updateModelTrampoline();

    for (u32 i = 0; i < 6; i++) {
        this->bones[i].rotation += Vec3u(fixDeg(1), fixDeg(1.25f), fixDeg(0.4f));
    }

    if (this->draw) {
        this->heat.execute(this->position + Vec3f(0, 8, 0), Vec3f(1.75f));

        for (u32 i = 0; i < 6; i++) {
            this->bones[i].hitbox.colliderInfo.distToCenter = 9999;
        }
    } else {
        this->heat.execute(0, 0);
    }

    return 1;
}

u32 BasaltBones::onDraw() {
    if (this->draw) {
        this->model->draw();
    }

    for (u32 i = 0; i < 6; i++) {
        this->bones[i].draw();
    }

    return 0;
}

void BasaltBones::initHitboxCollider() {
    this->hitboxCollider.init(this, &BasaltBones::collisionInfo);
}

void BasaltBones::initModels() {
    this->model = ModelWrapper::create("laron", "laron", 2);

    for (u32 i = 0; i < 6; i++) {
        static const sead::SafeString boneModels[6] = {
            "laron_partsB",
            "laron_partsE",
            "laron_partsC",
            "laron_partsD",
            "laron_partsF",
            "laron_head",
        };

        this->bones[i].model = ModelWrapper::create("laron", boneModels[i]);
    }
}

void BasaltBones::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position + Vec3f(0, -16.0f, 0));
    this->model->setScale(2.0f);
    this->model->updateAnimations();
    this->model->setMtx(mtx);
    this->model->updateModel();

    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];

        mtx.makeRTIdx(bone.rotation, bone.position);

        bone.model->setMtx(mtx);
        bone.model->setScale(2.0f);
        bone.model->updateModel();
    }
}

void BasaltBones::onStompDamage(StageActor* collidingActor) {
    this->doStateChange(&StateID_Disassemble);

    for (u32 i = 0; i < 6; i++) {
        this->bones[i].position = 0;
    }

    return BossWrapper<18>::onStompDamage(collidingActor);
}

void BasaltBones::onStompKill(StageActor* collidingActor) {
    this->dead = true;

    this->doStateChange(&StateID_Disassemble);

    return BossWrapper<18>::onStompKill(collidingActor);
}

void BasaltBones::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    BasaltBones* self = (BasaltBones*)hcSelf->owner;

    if (self->states.currentState()->ID == BasaltBones::StateID_Throw.ID && hcOther->owner->type == StageActor::Type::Player) {
        return self->damagePlayer(hcSelf, hcOther);
    }

    if (self->states.currentState()->ID != BasaltBones::StateID_Active.ID) {
        return;
    }

    if (hcOther->owner->getProfileID() == ProfileID::PlayerFireball || hcOther->owner->getProfileID() == ProfileID::PlayerIceBall) {
        self->collisionFireball(hcSelf, hcOther);
        hcOther->owner->isDeleted = true;
        return;
    }

    return BossWrapper<18>::collisionCallback(hcSelf, hcOther);
}

/** STATE: Spawn */

void BasaltBones::beginState_Spawn() {
    this->bones[0].bezier.set(this->position + Vec3f( 0,      -3 * 16, 0),  this->position + Vec3f( 0,      0,      0),  this->position + Vec3f(-19.6, 82.3, 0));
    this->bones[1].bezier.set(this->position + Vec3f( 0,      -3 * 16, 0),  this->position + Vec3f( 0,      0,      0),  this->position + Vec3f(0.3, 70.8, 0));
    this->bones[2].bezier.set(this->position + Vec3f( 5 * 16, -3 * 16, 0),  this->position + Vec3f( 5 * 16, 7 * 16, 0),  this->position + Vec3f(19.3, 81.8, 0));
    this->bones[3].bezier.set(this->position + Vec3f(-5 * 16, -3 * 16, 0),  this->position + Vec3f(-5 * 16, 7 * 16, 0),  this->position + Vec3f(19.6, 104.3, 0));
    this->bones[4].bezier.set(this->position + Vec3f( 8 * 16, -3 * 16, 0),  this->position + Vec3f( 8 * 16, 5 * 16, 0),  this->position + Vec3f(0.3, 115.8, 0));
    this->bones[5].bezier.set(this->position + Vec3f(-8 * 16, -3 * 16, 0),  this->position + Vec3f(-8 * 16, 5 * 16, 0),  this->position + Vec3f(-19.3, 104.8, 0));

    for (u32 i = 0; i < 6; i++) {
        this->bones[i].easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.0075f);
    }

    this->timer = 378;
    this->rotation.y = Direction::directionToRotationList[Direction::Left];
}

void BasaltBones::executeState_Spawn() {
    switch (this->spawnStage) {
        case SpawnStage::Wait: {
            if (--this->timer == 0) {
                this->spawnStage = SpawnStage::Shake;
                this->timer = 60 * 2;

                TileMgr::instance()->hasWaves = true;
                TileMgr::instance()->waveType = TileMgr::WaveType::Lava;

                defaultWaveRippleHeight = lava->effects.waveRippleHeight;
                defaultWaveHorizontalSpeed = lava->effects.waveHorizontalSpeed;

                lava->effects.waveWidth = 70887560;
            }

            break;
        }

        case SpawnStage::Shake: {
            ZoneRumbleMgr::instance()->rumble(1);

            if (--this->timer == 0) {
                this->spawnStage = SpawnStage::FlyOut;
                this->timer = 63 * 5;
            }

            sead::Mathf::chase(&lava->effects.waveRippleHeight, 28.0f, 0.2f);
            sead::Mathu::chase(&lava->effects.waveHorizontalSpeed, 42472454 / 2, 42472454 / 40);

            break;
        }

        case SpawnStage::FlyOut: {
            for (u32 i = 0; i < 6; i++) {
                Bone& bone = this->bones[i];

                bone.render = true;
                bool done = bone.easer.ease(bone.t);
                bone.bezier.execute(&bone.position, bone.t);

                if (done) {
                    this->spawnStage = SpawnStage::Assemble;
                    bone.easer.set(Easing::cubicIn, 360.0f, 0.0f, 0.004f);
                }
            }

            break;
        }

        case SpawnStage::Assemble: {
            sead::Mathf::chase(&lava->effects.waveRippleHeight, defaultWaveRippleHeight, 0.2f);
            sead::Mathu::chase(&lava->effects.waveHorizontalSpeed, defaultWaveHorizontalSpeed, 42472454 / 40);

            Vec3f centerPoint = (this->bones[0].bezier.keyframes[2] + this->bones[1].bezier.keyframes[2] + this->bones[2].bezier.keyframes[2] + this->bones[3].bezier.keyframes[2] + this->bones[4].bezier.keyframes[2] + this->bones[5].bezier.keyframes[2]) / 6;
            this->down += 0.0012f * this->bones[0].t;
            centerPoint.y -= this->down;

            bool change = false;

            for (u32 i = 0; i < 6; i++) {
                Bone& bone = this->bones[i];

                bool done = bone.easer.ease(bone.t);
                bone.position.x = centerPoint.x + (bone.t / 16) * cosf(bone.t / 16 + i * M_PI / 3.0f);
                bone.position.y = centerPoint.y + (bone.t / 16) * sinf(bone.t / 16 + i * M_PI / 3.0f);

                if (done) {
                    change = true;
                }
            }

            if (change) {
                this->draw = true;
                for (u32 i = 0; i < 6; i++) {
                    Bone& bone = this->bones[i];

                    bone.render = false;
                    bone.position = Vec3f(0, 0, 0);

                    bone.hitbox.init(this, &BasaltBones::Bone::collisionInfo);
                    HitboxColliderMgr::instance()->safeAddToCreateList(&bone.hitbox);
                }

                Vec3f scale = 2.3f;
                Effect::spawn(RP_Cmn_FireballHit, &this->position, nullptr, &scale);
                this->first = true;
                this->doStateChange(&BasaltBones::StateID_Throw);
            }

            break;
        }
    }
}

void BasaltBones::endState_Spawn() {
    this->finishedSpawning();
}

/** STATE: Active */

void BasaltBones::beginState_Active() {
    this->model->playSklAnim("walk");

    if (!this->first && !this->threw) {
        Vec3f scale = 2.3f;
        Vec3f pos = this->position + Vec3f(0, 0, 4500.0f);
        Effect::spawn(RP_Cmn_FireballHit, &pos, nullptr, &scale);
    }

    this->direction = sead::randBool();

    this->draw = true;
    this->first = false;

    this->timer = 0;
}

void BasaltBones::executeState_Active() {
    sead::Mathf::chase(&lava->effects.waveRippleHeight, defaultWaveRippleHeight, 0.2f);
    sead::Mathu::chase(&lava->effects.waveHorizontalSpeed, defaultWaveHorizontalSpeed, 42472454 / 40);

    sead::Mathu::chase(&this->rotation.y, Direction::directionToRotationList[Direction::opposite((Direction::DirectionType)this->direction)], fixDeg(6.0f));

    static const f32 threshold = 8 * 16;

    this->timer++;

    if (this->timer > 60 && sead::randU32(100) == 0 && (this->rotation.y == Direction::directionToRotationList[Direction::Left] || this->rotation.y == Direction::directionToRotationList[Direction::Right])) {
        this->doStateChange(&BasaltBones::StateID_Throw);
    }

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

void BasaltBones::endState_Active() {
    this->draw = false;
}

/** STATE: Throw */

void BasaltBones::beginState_Throw() {
    this->draw = true;
    this->model->playSklAnim("big_stop");
    this->model->sklAnims[0]->frameCtrl.speed = 1;
    this->model->loopSklAnims(false);
    this->flamesScale = 0;
}

void BasaltBones::executeState_Throw() {
    sead::Mathf::chase(&this->flamesScale.x, 1.7f, 0.1367f);
    sead::Mathf::chase(&this->flamesScale.y, 2.5f, 0.1367f);
    sead::Mathf::chase(&this->flamesScale.z, 2.5f, 0.1367f);

    Vec3f pos = this->position + Vec3f(0, 9, 0);
    this->flames.update(rp_Jr_FireBall, &pos, nullptr, &this->flamesScale);

    if (this->model->sklAnims[0]->frameCtrl.currentFrame / this->model->sklAnims[0]->frameCtrl.frameMax == 0.4f) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(ProfileID::BasaltBoneProjectile);
        buildInfo.position = this->position + Vec3f(0, 20, 0);
        static_cast<BasaltBoneProjectile*>(ActorMgr::instance()->create(buildInfo, false))->direction = !this->direction;
        playSound(SoundEffects::SE_BOSS_KOOPA_ATTACK, this->position);
    } else if (this->model->sklAnims[0]->frameCtrl.isDone()) {
        this->doStateChange(&BasaltBones::StateID_Active);
    }
}

void BasaltBones::endState_Throw() {
    this->threw = true;
    this->flamesScale = 0;
}

/** STATE: Disassemble */

void BasaltBones::beginState_Disassemble() {
    this->threw = false;

    this->bones[0].bezier.set(this->position, this->position + Vec3f(0, 0, 0),            this->position + Vec3f( 0,      -3 * 16, 0));
    this->bones[1].bezier.set(this->position, this->position + Vec3f(0, 0, 0),            this->position + Vec3f( 0,      -3 * 16, 0));
    this->bones[2].bezier.set(this->position, this->position + Vec3f( 3 * 16, 3 * 16, 0), this->position + Vec3f( 3 * 16, -7 * 16, 0));
    this->bones[3].bezier.set(this->position, this->position + Vec3f(-3 * 16, 3 * 16, 0), this->position + Vec3f(-3 * 16, -7 * 16, 0));
    this->bones[4].bezier.set(this->position, this->position + Vec3f( 5 * 16, 1 * 16, 0), this->position + Vec3f( 5 * 16, -7 * 16, 0));
    this->bones[5].bezier.set(this->position, this->position + Vec3f(-5 * 16, 1 * 16, 0), this->position + Vec3f(-5 * 16, -7 * 16, 0));

    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];

        bone.easer.set(Easing::quadIn, 0.0f, 1.0f, 0.03f);
    }
}

void BasaltBones::executeState_Disassemble() {
    bool change = false;

    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
        bone.render = true;

        bool done = bone.easer.ease(bone.t);
        bone.bezier.execute(&bone.position, bone.t);

        if (done) {
            bone.render = false;
            change = true;
        }
    }

    if (change) {
        if (this->dead) {
            this->finishedDying();
        } else {
            this->doStateChange(&BasaltBones::StateID_Assemble);
        }
    }
}

void BasaltBones::endState_Disassemble() { }

/** STATE: Assemble */

void BasaltBones::beginState_Assemble() {
    this->assembler = 0;

    this->position = this->startPosition;

    const Vec3f* keyframes = launchKeyframes[this->assembler][sead::randBool()];

    Bone& bone = this->bones[0];

    bone.bezier.set(this->position + keyframes[0], this->position + keyframes[1], this->position + keyframes[2]);
    bone.render = true;
    bone.easer.set(Easing::quadInOut, 0, 1, 0.008f);
}

#define xrb ((sead::randF32() * 2) - 1) * 3

void BasaltBones::executeState_Assemble() {
    sead::Mathf::chase(&lava->effects.waveRippleHeight, 28.0f, 0.2f);
    sead::Mathu::chase(&lava->effects.waveHorizontalSpeed, 42472454 / 2, 42472454 / 40);

    // Launch
    if (this->assembler < 6) {
        Bone& bone1 = this->bones[this->assembler];
        bool bone1done = bone1.easer.ease(bone1.t);
        bone1.bezier.execute(&bone1.position, bone1.t);
        if (bone1done) {
            this->assembler++;

            if (this->assembler < 6) {
                const Vec3f* keyframes = launchKeyframes[this->assembler][sead::randBool()];

                Bone& bone1next = this->bones[this->assembler];
                bone1next.render = true;
                bone1next.easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.008f);
                bone1next.bezier.set(this->position + keyframes[0], this->position + keyframes[1], this->position + keyframes[2]);

                bone1.bezier.set(bone1.position, this->position + Vec3f(0, 2 * 16, 0), this->position + Vec3f(xrb, xrb, 0.f));
                bone1.easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.008f);
            }
        }
    }

    bool change = false;

    // Assemble
    if (this->assembler > 0) {
        Bone& bone2 = this->bones[this->assembler - 1];

        bool done = bone2.easer.ease(bone2.t);
        bone2.bezier.execute(&bone2.position, bone2.t);

        if (this->assembler == 6 && done) {
            change = true;
        }
    }

    for (u32 i = 0; i < 6; i++) {
        Bone& bone = this->bones[i];
        bone.hitbox.colliderInfo.distToCenter = Vec2f(bone.position.x - this->position.x, bone.position.y - this->position.y);
    }

    if (change) {
        this->doStateChange(&BasaltBones::StateID_AssembleFinalize);
    }
}

#undef xrb

void BasaltBones::endState_Assemble() { }

/** STATE: AssembleFinalize */

void BasaltBones::beginState_AssembleFinalize() {
    Bone& bone = this->bones[5];

    bone.bezier.set(bone.position, this->position + Vec3f(0, 2 * 16, 0), this->position);
    bone.easer.set(Easing::quadInOut, 0.0f, 1.0f, 0.006f);
}

void BasaltBones::executeState_AssembleFinalize() {
    Bone& bone = this->bones[5];

    bool done = bone.easer.ease(bone.t);
    bone.bezier.execute(&bone.position, bone.t);

    bone.hitbox.colliderInfo.distToCenter = Vec2f(bone.position.x - this->position.x, bone.position.y - this->position.y);

    if (done) {
        for (u32 i = 0; i < 6; i++) {
            Bone& bone = this->bones[i];
            bone.render = false;
        }

        this->doStateChange(&BasaltBones::StateID_Throw);
    }
}

void BasaltBones::endState_AssembleFinalize() { }
