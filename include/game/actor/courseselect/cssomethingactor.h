#pragma once

#include "game/actor/courseselect/courseselectactor.h"

// TODO: Figure out a better name for this class (what does it do?)
class CSSomethingActor : public CourseSelectActor {
    SEAD_RTTI_OVERRIDE(CSSomethingActor, CourseSelectActor)

public:
    CSSomethingActor(const ActorBuildInfo* buildInfo);
    virtual ~CSSomethingActor();

    bool vf8C() override;
    void vf94() override;
    void vf9C() override;
    void vfA4() override;

    s32 _108;   // Inited to -1
};
