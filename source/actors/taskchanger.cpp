#include "game/task/coursetask.h"
#include "game/actor/stage/stageactor.h"
#include "game/task/taskmgr.h"
#include "log.h"

class TaskChanger : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(TaskChanger, StageActor);

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

#define DISABLE // Remove this line to use

u32 TaskChanger::onCreate() {
#ifndef DISABLE
    sead::TaskClassID taskClassID;
    taskClassID.type = sead::TaskClassID::Type_Factory;
    taskClassID.id.factory = nullptr; //! Set a target task!

    bool t = TaskMgr::instance()->changeTask(CourseTask::instance(), taskClassID, 0, 0);

    PRINT("TaskMgr says: ", t);

    return 0;
#else
    return 2;
#endif
}
