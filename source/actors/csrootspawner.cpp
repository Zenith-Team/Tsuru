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
    SEAD_RTTI_OVERRIDE_IMPL(CSRootSpawner, CourseSelectActor);

public:
    CSRootSpawner(const ActorBuildInfo* buildInfo);
    virtual ~CSRootSpawner() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    CourseSelectActor* spawn(ProfileID::__type__ profile) {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(profile);

        CourseSelectActor* a = static_cast<CourseSelectActor*>(ActorMgr::instance()->create(buildInfo));
        a->parent = this;
        return a;
    }

    // Timed spawn
    void ts(ProfileID::__type__ profile, u32 time, const Vec3f& position) {
        if (this->timer == time) {
            this->spawn(profile)->position = position;
        }
    }

    u32 onCreate() override { return 1; }
    u32 onExecute() override;
    u32 onDraw() override { return 1; }

    u32 timer;
};

const Profile CSRootSpawnerProfile(&CSRootSpawner::build, ProfileID::CSRootSpawner);

CSRootSpawner::CSRootSpawner(const ActorBuildInfo* buildInfo)
    : CourseSelectActor(buildInfo)
    , timer(0)
{ }

Actor* CSRootSpawner::build(const ActorBuildInfo* buildInfo) {
    return new CSRootSpawner(buildInfo);
}

u32 CSRootSpawner::onExecute() {
    //ts(ProfileID::CSFlames, 0,   Vec3f(-5840.0f, 170.0f, 2530.0f));
    //ts(ProfileID::CSFlames, 70,  Vec3f(-5840.0f, 170.0f, 2530.0f + 100));
    //ts(ProfileID::CSFlames, 140, Vec3f(-5840.0f - 190, 170.0f, 2530.0f));
    //ts(ProfileID::CSFlames, 70,  Vec3f(-5840.0f, 170.0f, 2530.0f));
    //ts(ProfileID::CSFlames, 140, Vec3f(-5840.0f, 170.0f, 2530.0f + 100));
    //ts(ProfileID::CSFlames, 70,  Vec3f(-5840.0f - 190, 170.0f, 2530.0f));


    this->timer++;

    return 1;
}
