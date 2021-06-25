#include "actor/enemy.h"

#include "math.h"
#include "mask.h"
#include "model.h"
#include "drawmgr.h"
#include "actormgr.h"
#include "eventmgr.h"
#include "lightsource.h"

class AngrySun : public Enemy {
public:
    AngrySun(const ActorBuildInfo* buildInfo);
    virtual ~AngrySun() { }

    static BaseActor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void freeze() override;

    void updateModel();

    ModelWrapper* model;
    ModelWrapper* glowModel;

    LightSource lightSource;
    sead::Color4f lightColor;
    LightMask lightMask;

    bool isMoon;

    bool glowAnimation;
    u32 glowTimer;

    u32 timer;

    f32 baseline;

    Vec2 swoopTarget;
    f32 swoopA;
    f32 swoopB;
    f32 swoopC;

    f32 wiggleX;

    Vec2 spinCenter;

    static const HitboxCollider::Info colliderInfo;

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

const Profile AngrySunProfile(&AngrySun::build, ProfileId::Sprite521, "AngrySun", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite521, "star_coin");

const HitboxCollider::Info AngrySun::colliderInfo = { Vec2(0.0f, 0.0f), Vec2(16.0f, 16.0f), 1, 3, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0, &Enemy::collisionCallback };

AngrySun::AngrySun(const ActorBuildInfo* buildInfo) : Enemy(buildInfo) { }

BaseActor* AngrySun::build(const ActorBuildInfo* buildInfo) {
    return new AngrySun(buildInfo);
}

u32 AngrySun::onCreate() {
    EnemyFreezeMgr::Flags flags = { 1, 1, 1 };
    freezeMgr.setFlags(flags);

    isMoon = settings1 & 0x1;
    glowTimer = 0;

    if (!isMoon) { ;
        //model = ModelWrapper::create("star_coin", "star_coinA");
        //glowModel = ModelWrapper::create("star_coin", "star_coinA");
        //lightColor = sead::Color4f(1.0f, 0.55f, 0.0f, 1.0f);
    } else {
        model = ModelWrapper::create("star_coin", "star_coinA");
        glowModel = nullptr;
        lightColor = sead::Color4f(0.0f, 0.53f, 1.0f, 1.0f);
    }

    f32 lightAttenuationRadius = 12.0f;
    //lightSource.update(0, &position, nullptr, &lightAttenuationRadius, nullptr, &lightColor, nullptr, nullptr);
    
    lightMask.init(nullptr, 2);
    lightMask.position = position;
    lightMask.radius = 350.0f;
    lightMask.update();

    baseline = position.y;

    aCollider.init(this, &colliderInfo, 0);
    addHitboxColliders();

    if (settings1 & 0x10) {
        doStateChange(&StateID_Stationary);
    } else {
        doStateChange(&StateID_Follow);
    }

    updateModel();

    return 1;

}

u32 AngrySun::onExecute() {
    states.execute();

    f32 lightAttenuationRadius = 12.0f;
    //lightSource.update(0, &position, nullptr, &lightAttenuationRadius, nullptr, &lightColor, nullptr, nullptr);
    
    lightMask.position = position;
    lightMask.update();

    updateModel();

    return 1;
}

u32 AngrySun::onDraw() {
    DrawMgr::instance->drawModel(model);
    if (glowModel) DrawMgr::instance->drawModel(glowModel);

    lightMask.draw();

    return 1;
}

void AngrySun::freeze() {
    EnemyFreezeMgr::Info info = { 0 };
    info.position = position;
    info.position.y -= 24;
    info.scale.set(0.75f);
    info.settings = 0x00000003;

    freezeMgr.freeze(info, 1);
}

void AngrySun::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, position);

    model->setMtx(mtx);
    model->updateModel();

    if (glowModel) {
        Vec3u glowRotation = rotation;
        glowRotation.z = fix_deg(cos(glowTimer*M_PI / 60.0f) * 15.0f);

        mtx.rotateAndTranslate(glowRotation, position);

        glowModel->setMtx(mtx);
        glowModel->updateModel();
    }

    if (glowAnimation) {
        if (++glowTimer > 120)
            glowTimer = 0;
    }
}


//* Stationary state

void AngrySun::beginState_Stationary() { glowAnimation = true; }

void AngrySun::executeState_Stationary() { }

void AngrySun::endState_Stationary() { }


//* Follow state

void AngrySun::beginState_Follow() {
    glowAnimation = true;
    timer = 0;
    speed.x = 0.0f;
    position.y = baseline;
}

void AngrySun::executeState_Follow() {
    direction = directionToPlayerH(position);

    const f32 speedDelta = 0.1f;

    if (direction == Direction::Right) {
        speed.x += speedDelta;
        if (speed.x <  0.0f) speed.x += speedDelta / 2.0f;
        if (speed.x < -6.0f) speed.x += speedDelta; 
    } else {
        speed.x -= speedDelta;
        if (speed.x >  0.0f) speed.x -= speedDelta / 2.0f;
        if (speed.x >  6.0f) speed.x -= speedDelta;
    }

    position.x += speed.x;

    timer++;

    if (timer > 200) {
        Vec2 dist;
        if (distanceToPlayer(dist) < 0) {
            timer = 0;
            return;
        }

        if (fabs(dist.x) > 250.0f)
            timer -= 100;
        else {
            if (randBool()) {
                if (dist.y > -48.0f)
                    doStateChange(&StateID_Spit);
                else
                    doStateChange(&StateID_AttackSpin);
            }

            else
                doStateChange(&StateID_Spit);
        }
    }
}

void AngrySun::endState_Follow() { }


//* Swoop state

void AngrySun::beginState_Swoop() {
    glowAnimation = false;

    Vec2 targetOffset;
    if (distanceToPlayer(targetOffset) < 0) {
        doStateChange(&StateID_Follow);
        return;
    }

    swoopTarget = Vec2(position.x, position.y) + targetOffset;

    f32 x1, x2, x3, y1, y2, y3;

    x1 = -targetOffset.x;
    x2 = 0.0f;
    x3 = -x1;

    y1 = -targetOffset.y;
    y2 = 0.0f;
    y3 = -y1;

    f32 denom = (x1 - x2) * (x1 - x3) * (x2 - x3);
    swoopA    = (x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2)) / denom;
	swoopB    = (x3*x3 * (y1 - y2) + x2*x2 * (y3 - y1) + x1*x1 * (y2 - y3)) / denom;
    swoopC    = (x2 * x3 * (x2 - x3) * y1 + x3 * x1 * (x3 - x1) * y2 + x1 * x2 * (x1 - x2) * y3) / denom;

    speed.x = x3 * 0.025f;
}

void AngrySun::executeState_Swoop() {
    position.x += speed.x;

    position.y = ( swoopA*(position.x - swoopTarget.x)*(position.x - swoopTarget.x) + swoopB*(position.x - swoopTarget.x) + swoopC ) + swoopTarget.y;

    if (position.y > baseline) {
        position.y = baseline;
        doStateChange(&StateID_Follow);
    }
}

void AngrySun::endState_Swoop() { }


//* AttackSpin state

void AngrySun::beginState_AttackSpin() {
    glowAnimation = false;
    timer = 0;
    spinCenter = Vec2(position.x, position.y);
    direction = directionToPlayerH(position);
}

void AngrySun::executeState_AttackSpin() {
    f32 dist = (cos((timer * M_PI) / 40.0f + M_PI) + 1.0f) * 7.0f;

    f32 theta = (timer / 6.0f) * (direction ? 1.0f : -1.0f);
    position.x = spinCenter.x + dist*cos(theta);
    position.y = spinCenter.y + dist*sin(theta);

    if (timer++ >= 80)
        doStateChange(&StateID_Swoop);
}

void AngrySun::endState_AttackSpin() { }


//* Spit state

void AngrySun::beginState_Spit() {
    glowAnimation = true;
    timer = 0;
    wiggleX = position.x;
}

void AngrySun::executeState_Spit() {
    if (timer <= 32)
        position.x = wiggleX + sin(timer * M_PI) * 1.5f;

    if (timer == 32) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(!isMoon ? ProfileId::Sprite0 : ProfileId::Sprite0);
        buildInfo.position = position;
        buildInfo.parentId = id;

        StageActor* fireball;

        Vec2 target;
        distanceToPlayer(target);

        f32 angle = atan2(target.y, target.x);

        if (randBool()) {
            const f32 shootSpeedSingle = 3.0f;

            buildInfo.rotation = fix_rad(angle);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance->create(&buildInfo, 0));
            fireball->speed.x = cos(angle) * shootSpeedSingle;
            fireball->speed.y = sin(angle) * shootSpeedSingle;
        } else {
            const f32 shootSpeedTriple = 2.5;

            buildInfo.rotation = fix_rad(angle);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance->create(&buildInfo, 0));
            fireball->speed.x = cos(angle) * shootSpeedTriple;
            fireball->speed.y = sin(angle) * shootSpeedTriple;

            buildInfo.rotation = fix_rad(angle + 0.4f);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance->create(&buildInfo, 0));
            fireball->speed.x = cos(angle + 0.4f) * shootSpeedTriple;
            fireball->speed.y = sin(angle + 0.4f) * shootSpeedTriple;

            buildInfo.rotation = fix_rad(angle - 0.4f);
            fireball = reinterpret_cast<StageActor*>(ActorMgr::instance->create(&buildInfo, 0));
            fireball->speed.x = cos(angle - 0.4f) * shootSpeedTriple;
            fireball->speed.y = sin(angle - 0.4f) * shootSpeedTriple;
        }
    }

    timer++;

    if (timer > 80)
        doStateChange(&StateID_Follow);  
}

void AngrySun::endState_Spit() { }
