#include <game/task/coursetask.h>
#include <game/task/courseselecttask.h>
#include <game/actor/stage/stageactor.h>
#include <game/task/taskmgr.h>
#include <tsuru/task/cutscenetask.h>
#include <log.h>

class TaskChanger : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(TaskChanger, StageActor)

public:
    TaskChanger(const ActorBuildInfo* buildInfo);
    virtual ~TaskChanger() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
};

const Profile TaskChangerProfile(&TaskChanger::build, ProfileID::TaskChanger);

TaskChanger::TaskChanger(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
{ }

Actor* TaskChanger::build(const ActorBuildInfo* buildInfo) {
    return new TaskChanger(buildInfo);
}

u32 TaskChanger::onCreate() {
    LOG("Changing task... %x", sizeof(CourseSelectTask));

    sead::TaskClassID taskClassID;
    taskClassID.type = sead::TaskClassID::Type_Factory;
    taskClassID.id.factory = &CourseSelectTask::construct;

    TaskMgr::instance()->changeTask(CourseTask::instance(), taskClassID, 0, 0);

    return 0;
}
