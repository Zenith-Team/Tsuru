#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/lightsource.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/collidermgr.h"
#include "game/graphics/mask/lightmask.h"
#include "game/actor/stage/playerbase.h"
#include "game/effect/effect.h"
#include "game/effect/effectid.h"
#include "math/functions.h"
#include "sead/heapmgr.h"

// SO MUCH MATH :C

#define calcFireOrbit(angleoffs) \
    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + this->helixDelta(j) + angleoffs)); \
    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + this->helixDelta(j) + angleoffs))

static f32 calcFireRadius(const u32 j) {
    f32 result = 0;
    
    for (u32 i = 0; i <= j; i++) {
        result += 16.0f - i;
        
        if (i > 2)
            result += 1.0f - (i - 2);
    }

    return result;
}

class HelicalBar : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(HelicalBar, MultiStateActor);

public:
    enum BarCount {
        BarCount_1,
        BarCount_2,
        BarCount_3
    };

public:
    HelicalBar(const ActorBuildInfo* buildInfo);
    virtual ~HelicalBar() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 beforeCreate() override;
    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    inline f32 helixDelta(const u32 orbitRadius) {
        f32 delta = ((orbitRadius * 10.0f) * orbitRadius) / 10.0f;
        delta *= helixMultiplier;

        return this->animate ? delta * sinf(degToRad(this->time)) : delta;
    }

    static void fireCollision(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    ModelWrapper* centerModel;
    ModelWrapper* fireModel[4][6];
    Vec2f firePositions[4][6];
    LightSource fireLights[4][6];
    HitboxCollider fireHitboxes[4][6];
    HitboxCollider::Info hcInfos[4][6];
    EffectWrapper heatDistorters[4][6];
    RectCollider centerCollider;
    f32 fireRotate;
    f32 time;
    u32 helixMultiplier;
    bool animate;

    static const ShapedCollider::Info colliderInfo;

    DECLARE_STATE(HelicalBar, OneBar);
    DECLARE_STATE(HelicalBar, TwoBars);
    DECLARE_STATE(HelicalBar, ThreeBars);
};

CREATE_STATE(HelicalBar, OneBar);
CREATE_STATE(HelicalBar, TwoBars);
CREATE_STATE(HelicalBar, ThreeBars);

const Profile HelicalBarProfile(&HelicalBar::build, ProfileID::HelicalBar);
PROFILE_RESOURCES(ProfileID::HelicalBar, Profile::LoadResourcesAt::Course, "firebar_L", "center_firebar");

const ShapedCollider::Info HelicalBar::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-8.0f, 8.0f), Vec2f(8.0f, -8.0f), 0
};

HelicalBar::HelicalBar(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , centerModel(nullptr)
    , firePositions()
    , fireLights()
    , fireHitboxes()
    , fireRotate(0)
    , animate(false)
{ }

Actor* HelicalBar::build(const ActorBuildInfo* buildInfo) {
    return new HelicalBar(buildInfo);
}

u32 HelicalBar::beforeCreate() {
    this->centerModel = ModelWrapper::create("center_firebar", "center_firebar");
    this->centerCollider.init(this, colliderInfo);
    ColliderMgr::instance()->add(&this->centerCollider);

    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            this->fireModel[i][j] = ModelWrapper::create("firebar_L", "firebar_L", 0, 0, 1);
            this->fireModel[i][j]->playTexSrtAnim("firebar_L");
        }
    }

    return 1;
}

u32 HelicalBar::onCreate() {
    switch (this->eventID1 >> 0x4 & 0xF) { // Nybble 1
        case BarCount_1: {
            this->doStateChange(&HelicalBar::StateID_OneBar);
            break;
        }

        case BarCount_2: {
            this->doStateChange(&HelicalBar::StateID_TwoBars);
            break;
        }

        case BarCount_3: {
            this->doStateChange(&HelicalBar::StateID_ThreeBars);
            break;
        }
    }

    this->animate = this->eventID1 & 0x1;
    this->helixMultiplier = (this->eventID2 & 0xF) + 1;

    return this->onExecute();
}

u32 HelicalBar::onExecute() {
    if (!(this->eventID2 >> 0x4 & 0xF)) {
        this->fireRotate++;
    }

    this->time++;

    this->states.execute();

    this->updateModel();

    return 1;
}

u32 HelicalBar::onDraw() {
    this->centerModel->draw();

    static f32 lightRadius = 1.25f;
    static sead::Color4f lightcolor = sead::Color4f(0.4f, 0.3f, 0.0f, 0.7f);

    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            Vec3f lfp = Vec3f(fp.x, fp.y, 0.0f);

            this->fireLights[i][j].update(nullptr, &lfp, nullptr, &lightRadius, nullptr, &lightcolor);

            Mtx34 mtx;
            mtx.makeRTIdx(Vec3u(0, 0, fixDeg(-this->fireRotate * 4)), this->firePositions[i][j]);
            this->fireModel[i][j]->setMtx(mtx);
            this->fireModel[i][j]->setScale(Vec3f(0.78f, 0.78f, 0.78f));
            this->fireModel[i][j]->updateModel();
            this->fireModel[i][j]->updateAnimations();
            this->fireModel[i][j]->draw();
        }
    }

    return 1;
}

void HelicalBar::updateModel() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, Vec3f(this->position.x, this->position.y, -1000.0f));
    this->centerModel->setMtx(mtx);
    this->centerModel->updateModel();
}

void HelicalBar::fireCollision(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type == StageActor::Type::Player) {
        PlayerBase* player = static_cast<PlayerBase*>(hcOther->owner);
        player->trySpecialDamage(hcSelf->owner, PlayerBase::DamageType::LavaNoInstaKill);
    }
}

/** STATE: OneBar */

void HelicalBar::beginState_OneBar() {
    this->executeState_OneBar();

    for (u32 i = 0; i < 1; i++) {
        for (u32 j = 0; j < 6; j++) {
            const Vec2f& fp = this->firePositions[i][j];

            this->hcInfos[i][j].set(
                Vec2f(this->position.x - fp.x, this->position.y - fp.y), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Circle, 5, 0, 0x824F, 0x20208, 0, &HelicalBar::fireCollision
            );

            this->fireHitboxes[i][j].init(this, &this->hcInfos[i][j]);

            HitboxColliderMgr::instance()->safeAddToCreateList(&this->fireHitboxes[i][j]);
        }
    }
}

void HelicalBar::executeState_OneBar() {
    for (u32 i = 0; i < 1; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            this->fireHitboxes[i][j].colliderInfo.distToCenter = Vec2f(this->position.x - fp.x, this->position.y - fp.y);

            switch (i) {
                case Direction::Right: {
                    calcFireOrbit(0.0f);
                    break;
                }
            }

            Vec3f efp(fp.x, fp.y, 4000.0f);
            this->heatDistorters[i][j].update(RP_Firebar, &efp, &this->rotation, &this->scale);
        }
    }
}

void HelicalBar::endState_OneBar() { }

/** STATE: TwoBars */

void HelicalBar::beginState_TwoBars() {
    this->executeState_TwoBars();

    for (u32 i = 0; i < 2; i++) {
        for (u32 j = 0; j < 6; j++) {
            const Vec2f& fp = this->firePositions[i][j];

            this->hcInfos[i][j].set(
                Vec2f(this->position.x - fp.x, this->position.y - fp.y), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Circle, 5, 0, 0x824F, 0x20208, 0, &HelicalBar::fireCollision
            );

            this->fireHitboxes[i][j].init(this, &this->hcInfos[i][j]);
            HitboxColliderMgr::instance()->safeAddToCreateList(&this->fireHitboxes[i][j]);
        }
    }
}

void HelicalBar::executeState_TwoBars() {
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            this->fireHitboxes[i][j].colliderInfo.distToCenter = Vec2f(this->position.x - fp.x, this->position.y - fp.y);

            switch (i) {
                case Direction::Right: {
                    calcFireOrbit(0.0f);
                    break;
                }

                case Direction::Left: {
                    calcFireOrbit(180.0f);
                    break;
                }
            }

            Vec3f efp(fp.x, fp.y, 4000.0f);
            this->heatDistorters[i][j].update(RP_Firebar, &efp, &this->rotation, &this->scale);
        }
    }
}

void HelicalBar::endState_TwoBars() { }

/** STATE: ThreeBars */

void HelicalBar::beginState_ThreeBars() {
    this->executeState_ThreeBars();

    for (u32 i = 0; i < 3; i++) {
        for (u32 j = 0; j < 6; j++) {
            const Vec2f& fp = this->firePositions[i][j];

            this->hcInfos[i][j].set(
                Vec2f(this->position.x - fp.x, this->position.y - fp.y), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Circle, 5, 0, 0x824F, 0x20208, 0, &HelicalBar::fireCollision
            );

            this->fireHitboxes[i][j].init(this, &this->hcInfos[i][j]);
            HitboxColliderMgr::instance()->safeAddToCreateList(&this->fireHitboxes[i][j]);
        }
    }
}

void HelicalBar::executeState_ThreeBars() {
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            switch (i) {
                case Direction::Right: {
                    calcFireOrbit(0.0f);
                    break;
                }

                case Direction::Left: {
                    calcFireOrbit(120.0f);
                    break;
                }

                case Direction::Up: {
                    calcFireOrbit(240.0f);
                    break;
                }
            }

            this->fireHitboxes[i][j].colliderInfo.distToCenter = Vec2f(this->position.x - fp.x, this->position.y - fp.y);
        
            Vec3f efp(fp.x, fp.y, 4000.0f);
            this->heatDistorters[i][j].update(RP_Firebar, &efp, &this->rotation, &this->scale);
        }
    }
}

void HelicalBar::endState_ThreeBars() { }
