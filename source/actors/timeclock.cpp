#include "game/effect/effect.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/stage/stageactor.h"
#include "game/level/leveltimer.h"
#include "game/sound/sound.h"
#include "log.h"

class TimeClock : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(TimeClock, StageActor);

public:
    TimeClock(const ActorBuildInfo* buildInfo);
    virtual ~TimeClock() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);
    static const HitboxCollider::Info collisionInfo;
};

const Profile TimeClockProfile(&TimeClock::build, ProfileID::TimeClock);
PROFILE_RESOURCES(ProfileID::TimeClock, Profile::LoadResourcesAt::Course, "timeclock");

TimeClock::TimeClock(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , model(nullptr)
{ }

Actor* TimeClock::build(const ActorBuildInfo* buildInfo) {
    return new TimeClock(buildInfo);
}

const HitboxCollider::Info TimeClock::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(12.0f, 12.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &TimeClock::collisionCallback
};

u32 TimeClock::onCreate() {
    this->model = ModelWrapper::create("timeclock", "timeclockA", 0);
    this->hitboxCollider.init(this, &TimeClock::collisionInfo, nullptr);
    this->addHitboxColliders();

    return this->onExecute();
}

u32 TimeClock::onExecute() {
    this->rotation.y -= 0x3FD27D2;

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->model->setMtx(mtx);
    this->model->updateModel();

    return 1;
}

u32 TimeClock::onDraw() {
    this->model->draw();

    return 1;
}

void TimeClock::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    TimeClock* self = static_cast<TimeClock*>(hcSelf->owner);
    if (hcOther->owner->type == StageActor::Type::Player || hcOther->owner->type == StageActor::Type::Yoshi) {
        Vec3f effectPos(self->position.x, self->position.y - 12.0f, 4500.0f);
        Effect::spawn(RP_FlagPass_1, &effectPos);

        playSound(SoundEffects::SE_SYS_CONTINUE_DONE, self->position);

        s16 time = self->settings1 & 0xFFF; // Nybbles 10-12
        if (self->settings1 >> 0x1C & 0xF /* Nybble 5 */)
            time = -time;

        if (LevelTimer::instance()->timeLimit + time <= 0) {
            LevelTimer::instance()->addTime(-LevelTimer::instance()->timeLimit + 3);
        } else {
            LevelTimer::instance()->addTime(time);
        }

        self->isDeleted = true;
    }
}
