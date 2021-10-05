#include <game/actor/stage/stageactor.h>
#include <game/graphics/model/model.h>
#include <game/effect/effect.h>
#include <game/sound.h>
#include <game/level/leveltimer.h>
#include <game/graphics/drawmgr.h>

class TimeClock : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(TimeClock, StageActor)

public:
    TimeClock(const ActorBuildInfo* buildInfo);
    virtual ~TimeClock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void updateModel();

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    ModelWrapper* model;
    u8 timeAmount;

    static const HitboxCollider::Info collisionInfo;
};

const Profile TimeClockProfile(&TimeClock::build, ProfileID::TimeClock);

const HitboxCollider::Info TimeClock::collisionInfo = {
    Vec2f(0.0f, -3.0f), Vec2f(12.0f, 15.0f), HitboxCollider::HitboxShape_Rectangle, 0, 0, 0x824F, 0x20208, 0, &TimeClock::collisionCallback
};

TimeClock::TimeClock(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* TimeClock::build(const ActorBuildInfo* buildInfo) {
    return new TimeClock(buildInfo);
}

u32 TimeClock::onCreate() {
    this->model = ModelWrapper::create("star_coin", "star_coinA");

    this->hitboxCollider.init(this, &TimeClock::collisionInfo, 0);
    this->addHitboxColliders();

    this->updateModel();

    return 1;
}

u32 TimeClock::onExecute() {
    this->rotation.y -= 0x3FD27D2;

    this->updateModel();

    return 1;
}

u32 TimeClock::onDraw() {
    DrawMgr::instance()->drawModel(this->model);

    return 1;
}

void TimeClock::updateModel() {
    Mtx34 mtx;
    mtx.rotateAndTranslate(this->rotation, this->position);

    this->model->setMtx(mtx);
    this->model->updateModel();
    this->model->setScale(this->scale);
}

void TimeClock::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type == 1) {
        TimeClock* self = reinterpret_cast<TimeClock*>(hcSelf->owner);

        Vec3f effectPos(self->position.x, self->position.y - 18.0f, 4500.0f);
        Effect::spawn(RP_FlagPass_1, &effectPos, nullptr, nullptr);
        LevelTimer::instance()->addTime(self->timeAmount);

        self->isDeleted = true;
    }
}
