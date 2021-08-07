#pragma once

#include <sead/task.h>
#include <game/states.h>

class CourseSelectTask : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE(CourseSelectTask, sead::CalculateTask)

public:
    virtual ~CourseSelectTask();

    void prepare() override;
    
    void enter() override;
    void exit() override;

    void calc() override;

    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState1);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState2);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState3);

    void spawnCameraActor();
    void doStateChange(StateBase* state);

    static CourseSelectTask* sInstance;
};
