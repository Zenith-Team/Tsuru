#include "game/actor/courseselect/courseselectactor.h"
#include "game/actor/actormgr.h"
#include "log.h"

u32 createRootSpawner() {
    ActorBuildInfo buildInfo = { 0 };
    buildInfo.profile = Profile::get(ProfileID::CSRootSpawner);

    ActorMgr::instance()->create(buildInfo);

    return 1;
}

class CSRootSpawner : public CourseSelectActor {
    SEAD_RTTI_OVERRIDE(CSRootSpawner, CourseSelectActor);

public:
    CSRootSpawner(const ActorBuildInfo* buildInfo);
    virtual ~CSRootSpawner() { }

    CourseSelectActor* spawn(ProfileID::__type__ profile) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(profile);

        CourseSelectActor* a = static_cast<CourseSelectActor*>(ActorMgr::instance()->create(buildInfo));
        a->parent = this;
        return a;
    }

    // Timed spawn
    void ts(ProfileID::__type__ profile, u32 time, const sead::Vector3f& position) {
        if (this->timer == time) {
            this->spawn(profile)->position = position;
        }
    }

    u32 onCreate() override { return 1; }
    u32 onExecute() override;
    u32 onDraw() override { return 1; }

    u32 timer;
};

REGISTER_PROFILE(CSRootSpawner, ProfileID::CSRootSpawner);

CSRootSpawner::CSRootSpawner(const ActorBuildInfo* buildInfo)
    : CourseSelectActor(buildInfo)
    , timer(0)
{ }

u32 CSRootSpawner::onExecute() {
#ifdef TARGET_TRICKY
    // Worldmap fire
    ts(ProfileID::CSFlames, 0,   sead::Vector3f(-5840.0f, 170.0f, 2530.0f));
    ts(ProfileID::CSFlames, 70,  sead::Vector3f(-5840.0f, 170.0f, 2530.0f + 100));
    ts(ProfileID::CSFlames, 140, sead::Vector3f(-5840.0f - 190, 170.0f, 2530.0f));
    ts(ProfileID::CSFlames, 70,  sead::Vector3f(-5840.0f, 170.0f, 2530.0f));
    ts(ProfileID::CSFlames, 140, sead::Vector3f(-5840.0f, 170.0f, 2530.0f + 100));
    ts(ProfileID::CSFlames, 70,  sead::Vector3f(-5840.0f - 190, 170.0f, 2530.0f));
#endif

    this->timer++;

    return 1;
}
