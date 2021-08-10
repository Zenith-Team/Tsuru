#pragma once

#include <sead/task.h>
#include <game/states.h>
#include <agl/renderinfo.h>

class CourseSelectTask : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE(CourseSelectTask, sead::CalculateTask)

public:
    virtual ~CourseSelectTask();

    void prepare() override;
    
    void enter() override;
    void exit() override;

    void calc() override;

    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);

    void spawnCameraActor();
    void doStateChange(StateBase* state);

    // Custom functions
    void debugDraw(const agl::lyr::RenderInfo& renderInfo);

    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState1);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState2);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState3);

    static CourseSelectTask* sInstance;
};
