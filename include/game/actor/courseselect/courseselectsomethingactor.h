#pragma once

#include "game/actor/courseselect/courseselectactor.h"

class CourseSelectSomethingActor : public CourseSelectActor {
    SEAD_RTTI_OVERRIDE(CourseSelectSomethingActor, CourseSelectActor)

public:
    CourseSelectSomethingActor(const ActorBuildInfo* buildInfo);
    virtual ~CourseSelectSomethingActor();

    bool vf8C() override;
    void vf94() override;
    void vf9C() override;
    void vfA4() override;

    s32 _108;   // Inited to -1
};
