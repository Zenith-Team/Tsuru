#include "game/actor/stage/stageactor.h"
#include "game/graphics/model/model.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/lightsource.h"
#include "tsuru/heatdistorter.h"
#include "tsuru/heap.h"
#include "log.h"

class HelicalBar : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(HelicalBar, StageActor);

private:
    class Fireball {
    public:
        Fireball()
            : model(nullptr)
            , heatDistorter()
            , position(0.0f, 0.0f, 0.0f)
            , hitbox()
            , hitboxInfo()
            , light()
            , parent(nullptr)
        {
            this->model = ModelWrapper::create("firebar_L", "firebar_L", 0, 0, 1);
            this->model->playTexSrtAnim("firebar_L");
        }

        ~Fireball() {
            delete this->model;
        }

        void execute() {
            static f32 lightintensity = 1.5f;
            static sead::Color4f lightcolor(0.4f, 0.3f, 0.0f, 0.7f);
            this->light.update(0, this->position, nullptr, lightintensity, nullptr, lightcolor);

            this->heatDistorter.execute(this->position, Vec3f(1.0f, 1.0f, 1.0f));
        
            Mtx34 mtx;
            mtx.rotateAndTranslate(Vec3u(0, 0, fixDeg(-parent->fireRotate * 4)), this->position);
            this->model->setMtx(mtx);
            this->model->updateModel();
            this->model->updateAnimations();
        }

        void draw() {
            DrawMgr::instance()->drawModel(this->model);
        }

        ModelWrapper* model;
        HeatDistorter heatDistorter;
        Vec3f position;
        HitboxCollider hitbox;
        HitboxCollider::Info hitboxInfo;
        LightSource light;
        HelicalBar* parent;
    };

public:
    HelicalBar(const ActorBuildInfo* buildInfo);
    virtual ~HelicalBar() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    f32 helixDelta(const u32 radius) {
        return ((radius * 10.0f) * radius) / 10.0f;
    }

    u32 barCount, fireCount;
    ModelWrapper* centerModel;
    Fireball* fireballs;
    f32 fireRotate;
};

const Profile HelicalBarProfile(&HelicalBar::build, ProfileID::HelicalBar);
PROFILE_RESOURCES(ProfileID::HelicalBar, Profile::LoadResourcesAt_Course, "firebar_L", "center_firebar");

HelicalBar::HelicalBar(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo) 
    , barCount(0)
    , fireCount(0)
    , centerModel(nullptr)
    , fireballs(nullptr)
    , fireRotate(0.0f)
{ }

Actor* HelicalBar::build(const ActorBuildInfo* buildInfo) {
    return new HelicalBar(buildInfo);
}

u32 HelicalBar::onCreate() {
    this->barCount = this->eventID1 >> 0x4 & 0xF;
    this->fireCount = this->eventID1 & 0xF;

    if (this->barCount == 0 || this->fireCount == 0) {
        LOG("%sWarning: HelicalBar has zero barCount or fireCount", LogColor::Yellow);
        
        this->barCount = 1;
        this->fireCount = 1;
    }

    {
        ScopedHeapSetter setter(TsuruHeap);

        this->centerModel = ModelWrapper::create("center_firebar", "center_firebar");

        this->fireballs = new Fireball[this->fireCount * this->barCount];

        for (u32 i = 0; i < this->fireCount * this->barCount; i++) {
            this->fireballs[i].parent = this;
        }
    }

    return this->onExecute();
}

u32 HelicalBar::onExecute() {
    this->fireRotate++;

    for (u32 i = 0; i < this->barCount; i++) {
        for (u32 j = 0; j < this->fireCount; j++) {
            Fireball& fireball = this->fireballs[i * this->fireCount + j];

            fireball.position.x = this->position.x + ((j+1) * 16.0f) * cosf(degToRad(this->fireRotate + this->helixDelta(j) + (360.0f / this->barCount * i)));
            fireball.position.y = this->position.y + ((j+1) * 16.0f) * sinf(degToRad(this->fireRotate + this->helixDelta(j) + (360.0f / this->barCount * i)));

            fireball.execute();
        }
    }

    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);
    this->centerModel->setMtx(mtx);
    this->centerModel->updateModel();

    return 1;
}

u32 HelicalBar::onDraw() {
    DrawMgr::instance()->drawModel(this->centerModel);

    for (u32 i = 0; i < this->fireCount; i++) {
        this->fireballs[i].draw();
    }

    return 1;
}

u32 HelicalBar::onDelete() {
    delete[] this->fireballs;
    delete this->centerModel;

    return 1;
}
