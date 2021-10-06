#include <game/actor/stage/enemy.h>
#include <game/graphics/model/model.h>
#include <game/graphics/drawmgr.h>
#include <game/graphics/lightsource.h>
#include <game/graphics/mask/lightmask.h>
#include <game/actor/actormgr.h>
#include <game/direction.h>
#include <sead/random.h>
#include <math.h>

class AngrySun : public Enemy { // Angry Sun miniboss from Newer Wii, written by Bent, ported by Luminyx, for Mixed SMBU
    SEAD_RTTI_OVERRIDE_IMPL(AngrySun, Enemy)

public:
    AngrySun(const ActorBuildInfo* buildInfo);
    virtual ~AngrySun() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void freeze() override;

    void updateModel();

    ModelWrapper* model;

    LightSource lightSource;
    sead::Color4f lightColor;
    LightMask lightMask;
    f32 lightAttenuationRadius;

    f32 baseline;
    u32 timer;

    Vec2f spinCenter;

    Vec2f swoopTarget;
    f32 swoopA;
    f32 swoopB;
    f32 swoopC;

    f32 wiggleX;

    bool isMoon;

    static const HitboxCollider::Info collisionInfo;

    DECLARE_STATE(AngrySun, Stationary);
    DECLARE_STATE(AngrySun, Follow);
    DECLARE_STATE(AngrySun, Swoop);
    DECLARE_STATE(AngrySun, AttackSpin);
    DECLARE_STATE(AngrySun, Spit);
};

CREATE_STATE(AngrySun, Stationary);
CREATE_STATE(AngrySun, Follow);
CREATE_STATE(AngrySun, Swoop);
CREATE_STATE(AngrySun, AttackSpin);
CREATE_STATE(AngrySun, Spit);

const HitboxCollider::Info AngrySun::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(16.0f, 16.0f), HitboxCollider::HitboxShape_Circle, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback
};

const Profile AngrySunProfile(&AngrySun::build, ProfileID::AngrySun);
const Profile AngryMoonProfile(&AngrySun::build, ProfileID::AngryMoon);

PROFILE_RESOURCES(ProfileID::AngrySun, "star_coin");
PROFILE_RESOURCES(ProfileID::AngryMoon, "star_coin");

AngrySun::AngrySun(const ActorBuildInfo* buildInfo)
    : Enemy(buildInfo)
    , model(nullptr)
    , lightSource()
    , lightColor(1.0f, 0.55f, 0.0f, 1.0f)
    , lightMask()
    , lightAttenuationRadius(12.0f)
    , isMoon(false)
{ }

Actor* AngrySun::build(const ActorBuildInfo* buildInfo) {
    return new AngrySun(buildInfo);
}

u32 AngrySun::onCreate() {
    switch (this->profile->id) {
        case ProfileID::AngrySun: this->isMoon = false; break;
        case ProfileID::AngryMoon: this->isMoon = true; this->lightColor.set(0.0f, 0.53f, 1.0f, 1.0f); break;
    }

    EnemyFreezeMgr::Flags flags = { 1, 1, 1 };
    this->freezeMgr.setFlags(flags);

    this->model = this->isMoon ? ModelWrapper::create("star_coin", "star_coinB") : ModelWrapper::create("star_coin", "star_coinA");

    this->lightSource.update(0, &this->position, nullptr, &this->lightAttenuationRadius, nullptr, &this->lightColor);

    this->lightMask.init(nullptr, 2);
    this->lightMask.position = this->position;
    this->lightMask.radius = 350.0f;
    this->lightMask.update();

    this->baseline = this->position.y;

    this->hitboxCollider.init(this, &AngrySun::collisionInfo, nullptr);
    this->addHitboxColliders();

    if (this->nybble12)
        this->doStateChange(&StateID_Stationary);
    else
        this->doStateChange(&StateID_Follow);

    this->updateModel();

    return 1;
}

u32 AngrySun::onExecute() {
    this->states.execute();

    this->lightSource.update(0, &this->position, nullptr, &this->lightAttenuationRadius, nullptr, &this->lightColor);

    this->lightMask.position = this->position;
    this->lightMask.update();

    this->updateModel();

    return 1;
}

u32 AngrySun::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    this->lightMask.draw();

    return 1;
}

void AngrySun::freeze() {
    EnemyFreezeMgr::Info info = { 0 };
    info.position = this->position;
    info.position.y -= 24;
    info.scale.set(0.75f);
    info.settings = 0x00000003;
}

void AngrySun::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->updateAnimations();
    this->model->updateModel();
}

/* STATE: Stationary */

void AngrySun::beginState_Stationary() { }

void AngrySun::executeState_Stationary() { }

void AngrySun::endState_Stationary() { }

/* STATE: Follow */

void AngrySun::beginState_Follow() {
    this->timer = 0;
    this->speed.x = 0.0f;
    this->position.y = this->baseline;
}

void AngrySun::executeState_Follow() {
    // Handle speed

    this->direction = directionToPlayerH(this->position);

    if (this->direction == Direction::Right) {
        this->speed.x += 0.1f;
        if (this->speed.x < 0.0f)  this->speed.x += 0.1f / 2.0f;
        if (this->speed.x < -6.0f) this->speed.x += 0.1f;
    }

    else {
        this->speed.x -= 0.1f;
        if (this->speed.x > 0.0f) this->speed.x -= 0.1f / 2.0f;
        if (this->speed.x > 6.0f) this->speed.x -= 0.1f;
    }

    this->position.x += this->speed.x;
    this->rotation.z = fixDeg(this->speed.x * 2);

    // Handle state switching

    this->timer++;

    if (this->timer > 200) {
        Vec2f distance;
        if (this->distanceToPlayer(distance) < 0) {
            this->timer = 0;
            return;
        }

        if (fabs(distance.x) > 250.0f) {
            this->timer -= 100;
        }

        else {
            if (sead::randBool()) {
                if (distance.y > -48.0f)
                    this->doStateChange(&AngrySun::StateID_Spit);
                else
                    this->doStateChange(&AngrySun::StateID_AttackSpin);
            }

            else {
                this->doStateChange(&AngrySun::StateID_Spit);
            }
        }
    }
}

void AngrySun::endState_Follow() { }

/* STATE: Swoop */

void AngrySun::beginState_Swoop() {
    Vec2f targetOffset;
    if (this->distanceToPlayer(targetOffset) < 0) {
        this->doStateChange(&AngrySun::StateID_Follow);
        return;
    }

    this->swoopTarget = Vec2f(this->position.x, this->position.y) + targetOffset;

    f32 x1, x2, x3;
    f32 y1, y2, y3;

    x1 = -targetOffset.x;
	x2 = 0.0f;
	x3 = -x1;

	y1 = -targetOffset.y;
	y2 = 0.0f;
    y3 = y1;

    f32 denom    = (x1 - x2) * (x1 - x3) * (x2 - x3);
    this->swoopA = (x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2)) / denom;
	this->swoopB = (x3 * x3 * (y1 - y2) + x2 * x2 * (y3 - y1) + x1 * x1 * (y2 - y3)) / denom;
    this->swoopC = (x2 * x3 * (x2 - x3) * y1 + x3 * x1 * (x3 - x1) * y2 + x1 * x2 * (x1 - x2) * y3) / denom;

    this->speed.x = x3 * 0.025f;
}

void AngrySun::executeState_Swoop() {
    this->position.x += this->speed.x;

    this->position.y = (this->swoopA * (this->position.x - this->swoopTarget.x) * (this->position.x - this->swoopTarget.x) + this->swoopB * (this->position.x - this->swoopTarget.x) + this->swoopC) + this->swoopTarget.y;

    if (this->position.y > this->baseline) {
        this->position.y = this->baseline;

        this->doStateChange(&AngrySun::StateID_Follow);
    }
}

void AngrySun::endState_Swoop() { }

/* STATE: AttackSpin */

void AngrySun::beginState_AttackSpin() {
    this->timer = 0;
    this->spinCenter = Vec2f(this->position.x, this->position.y);
    this->direction = this->directionToPlayerH(this->position);
}

void AngrySun::executeState_AttackSpin() {
    f32 dist = (cosf((this->timer * M_PI) / 40.0f + M_PI) + 1.0f) * 7.0f;
    f32 theta = (this->timer / 6.0f) * (direction ? 1.0f : -1.0f);

    this->position.x = this->spinCenter.x + dist * cosf(theta);
    this->position.y = this->spinCenter.y + dist * sinf(theta);

    if (this->timer++ >= 80)
        this->doStateChange(&AngrySun::StateID_Swoop);
}

void AngrySun::endState_AttackSpin() { }

/* STATE: Spit */

void AngrySun::beginState_Spit() {
    this->timer = 0;
    this->wiggleX = position.x;
}

void AngrySun::executeState_Spit() {
    if (this->timer <= 32)
        this->position.x = this->wiggleX + sinf(this->timer * (M_PI / 4.0f)) * 1.5f;

    if (this->timer == 32) {
        Vec2f target;
        this->distanceToPlayer(target);

        f32 angle = atan2f(target.y, target.x);

        StageActor* fireball;

        ActorBuildInfo projectileBuildInfo = { 0 };
        projectileBuildInfo.profile = this->isMoon ? Profile::get(475) : Profile::get(477); // Piranha Plant iceball / fireball
        projectileBuildInfo.position = this->position;
        projectileBuildInfo.parentID = this->id;

        if (sead::randBool()) {
            projectileBuildInfo.rotation = fixRad(angle);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            fireball->speed.x = cosf(angle) * 3.0f;
            fireball->speed.y = sinf(angle) * 3.0f;
        }

        else {
            projectileBuildInfo.rotation = fixRad(angle);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            fireball->speed.x = cosf(angle) * 2.5f;
            fireball->speed.y = sinf(angle) * 2.5f;

            projectileBuildInfo.rotation = fixRad(angle + 0.4f);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            fireball->speed.x = cosf(angle + 0.4f) * 2.5f;
            fireball->speed.y = sinf(angle + 0.4f) * 2.5f;

            projectileBuildInfo.rotation = fixRad(angle - 0.4f);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance()->create(projectileBuildInfo, 0));
            fireball->speed.x = cosf(angle - 0.4f) * 2.5f;
            fireball->speed.y = sinf(angle - 0.4f) * 2.5f;
        }
    }

    this->timer++;

    if (this->timer > 80)
        this->doStateChange(&AngrySun::StateID_Follow);
}

void AngrySun::endState_Spit() { }
