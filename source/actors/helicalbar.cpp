#include "game/actor/stage/stageactor.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/lightsource.h"
#include "game/graphics/mask/lightmask.h"
#include "math/functions.h"

class HelicalBar : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(HelicalBar, StageActor);

public:
    HelicalBar(const ActorBuildInfo* buildInfo);
    virtual ~HelicalBar() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    ModelWrapper* centerModel;
    ModelWrapper* fireModel;
    Vec2f firePositions[4][6];
    LightSource fireLights[4][6];
    HitboxCollider fireHitboxes[4][6];
    f32 fireRotate;
};

const Profile HelicalBarProfile(&HelicalBar::build, ProfileID::HelicalBar);
PROFILE_RESOURCES(ProfileID::HelicalBar, Profile::LoadResourcesAt_Course, "firebar_L");

HelicalBar::HelicalBar(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , centerModel(nullptr)
    , fireModel(nullptr)
    , firePositions()
    , fireRotate(0)
{ }

Actor* HelicalBar::build(const ActorBuildInfo* buildInfo) {
    return new HelicalBar(buildInfo);
}

u32 HelicalBar::onCreate() {
    this->centerModel = ModelWrapper::create("firebar_L", "firebar_L_base");
    this->fireModel = ModelWrapper::create("firebar_L", "firebar_L");

    return this->onExecute();
}

u32 HelicalBar::onExecute() {
    this->fireRotate++;

    // Orbit
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            static const f32 helixDelta = 10.0f;

            const f32 finalHelixDelta = ((j * helixDelta) * j) / helixDelta;

            switch (i) {
                case Direction::Right: {
                    fp.x = this->position.x + ((j+1) * (1.f * 16.0f)) * cosf(degToRad(this->fireRotate + 0.0f + finalHelixDelta));
                    fp.y = this->position.y + ((j+1) * (1.f * 16.0f)) * sinf(degToRad(this->fireRotate + 0.0f + finalHelixDelta));
                    break;
                }

                case Direction::Left: {
                    fp.x = this->position.x + ((j+1) * (1.f * 16.0f)) * cosf(degToRad(this->fireRotate + 180.0f + finalHelixDelta));
                    fp.y = this->position.y + ((j+1) * (1.f * 16.0f)) * sinf(degToRad(this->fireRotate + 180.0f + finalHelixDelta));
                    break;
                }

                case Direction::Up: {
                    fp.x = this->position.x + ((j+1) * (1.f * 16.0f)) * cosf(degToRad(this->fireRotate + 90.0f + finalHelixDelta));
                    fp.y = this->position.y + ((j+1) * (1.f * 16.0f)) * sinf(degToRad(this->fireRotate + 90.0f + finalHelixDelta));
                    break;
                }

                case Direction::Down: {
                    fp.x = this->position.x + ((j+1) * (1.f * 16.0f)) * cosf(degToRad(this->fireRotate + 270.0f + finalHelixDelta));
                    fp.y = this->position.y + ((j+1) * (1.f * 16.0f)) * sinf(degToRad(this->fireRotate + 270.0f + finalHelixDelta));
                    break;
                }
            }
        }
    }

    this->updateModel();

    return 1;
}

u32 HelicalBar::onDraw() {
    DrawMgr::instance()->drawModel(this->centerModel);

    static f32 lightradius = 3.f;
    static sead::Color4f lightcolor = sead::Color4f(0.5f, 0.25f, 0.0f, 0.5f);

    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 6; j++) {
            Vec2f& fp = this->firePositions[i][j];

            Vec3f lfp = Vec3f(fp.x, fp.y, 0.0f);

            this->fireLights[i][j].update(nullptr, &lfp, nullptr, &lightradius, nullptr, &lightcolor);

            Mtx34 mtx;
            mtx.rotateAndTranslate(Vec3u(0, 0, fixDeg(this->fireRotate * 2)), this->firePositions[i][j]);
            this->fireModel->setMtx(mtx);
            this->fireModel->updateModel();
            DrawMgr::instance()->drawModel(this->fireModel);
        }
    }

    return 1;
}

void HelicalBar::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->centerModel->setMtx(mtx);
    this->centerModel->updateModel();
}
