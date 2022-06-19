#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/lightsource.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/collidermgr.h"
#include "game/graphics/mask/lightmask.h"
#include "math/functions.h"
#include "sead/heapmgr.h"

// SO MUCH MATH :C

#define finalHelixDelta (((j * 10.0f) * j) / 10.0f)

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

    ModelWrapper* centerModel;
    ModelWrapper* fireModel[4][6];
    Vec2f firePositions[4][6];
    LightSource fireLights[4][6];
    HitboxCollider fireHitboxes[4][6];
    RectCollider centerCollider;
    f32 fireRotate;
    bool reverse;

    static const ShapedCollider::Info colliderInfo;

    DECLARE_STATE(HelicalBar, OneBar);
    DECLARE_STATE(HelicalBar, TwoBars);
    DECLARE_STATE(HelicalBar, ThreeBars);
};

CREATE_STATE(HelicalBar, OneBar);
CREATE_STATE(HelicalBar, TwoBars);
CREATE_STATE(HelicalBar, ThreeBars);

const Profile HelicalBarProfile(&HelicalBar::build, ProfileID::HelicalBar);
PROFILE_RESOURCES(ProfileID::HelicalBar, Profile::LoadResourcesAt_Course, "firebar_L", "center_firebar");

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
    , reverse(false)
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

    return this->onExecute();
}

u32 HelicalBar::onExecute() {
    this->fireRotate++;

    this->states.execute();

    this->updateModel();

    return 1;
}

u32 HelicalBar::onDraw() {
    DrawMgr::instance()->drawModel(this->centerModel);

    static f32 lightRadius = 1.25f;
    static sead::Color4f lightcolor = sead::Color4f(0.4f, 0.3f, 0.0f, 0.7f);

    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            Vec3f lfp = Vec3f(fp.x, fp.y, 0.0f);

            this->fireLights[i][j].update(nullptr, &lfp, nullptr, &lightRadius, nullptr, &lightcolor);

            Mtx34 mtx;
            mtx.rotateAndTranslate(Vec3u(0, 0, fixDeg(-this->fireRotate * 4)), this->firePositions[i][j]);
            this->fireModel[i][j]->setMtx(mtx);
            this->fireModel[i][j]->setScale(Vec3f(0.78f, 0.78f, 0.78f));
            this->fireModel[i][j]->updateModel();
            this->fireModel[i][j]->updateAnimations();
            DrawMgr::instance()->drawModel(this->fireModel[i][j]);
        }
    }

    return 1;
}

void HelicalBar::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, Vec3f(this->position.x, this->position.y, -1000.0f));
    this->centerModel->setMtx(mtx);
    this->centerModel->updateModel();
}

/** STATE: OneBar */

void HelicalBar::beginState_OneBar() { }

void HelicalBar::executeState_OneBar() {
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            switch (i) {
                case Direction::Right: {
                    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + finalHelixDelta));
                    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + finalHelixDelta));
                    break;
                }
            }
        }
    }
}

void HelicalBar::endState_OneBar() { }

/** STATE: TwoBars */

void HelicalBar::beginState_TwoBars() { }

void HelicalBar::executeState_TwoBars() {
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            switch (i) {
                case Direction::Right: {
                    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + finalHelixDelta));
                    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + finalHelixDelta));
                    break;
                }

                case Direction::Left: {
                    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + 180.0f + finalHelixDelta));
                    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + 180.0f + finalHelixDelta));
                    break;
                }
            }
        }
    }
}

void HelicalBar::endState_TwoBars() { }

/** STATE: ThreeBars */

void HelicalBar::beginState_ThreeBars() { }

void HelicalBar::executeState_ThreeBars() {
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            switch (i) {
                case Direction::Right: {
                    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + finalHelixDelta));
                    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + finalHelixDelta));
                    break;
                }

                case Direction::Left: {
                    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + 120.0f + finalHelixDelta));
                    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + 120.0f + finalHelixDelta));
                    break;
                }

                case Direction::Up: {
                    fp.x = this->position.x + calcFireRadius(j) * cosf(degToRad(this->fireRotate + 240.0f + finalHelixDelta));
                    fp.y = this->position.y + calcFireRadius(j) * sinf(degToRad(this->fireRotate + 240.0f + finalHelixDelta));
                    break;
                }
            }
        }
    }
}

void HelicalBar::endState_ThreeBars() { }
