#pragma once

#include <game/actor/courseselect/courseselectactorbase.h>

class CourseSelectActor : public CourseSelectActorBase {
    SEAD_RTTI_OVERRIDE(CourseSelectActor, CourseSelectActorBase)

public:
    CourseSelectActor(const ActorBuildInfo* buildInfo);
    virtual ~CourseSelectActor();

    u32 onCreate() override = 0;

    u32 beforeExecute() override;
    u32 onExecute() override = 0;

    u32 beforeDraw() override;
    u32 onDraw() override = 0;


    virtual bool vf8C();
    virtual void vf94();
    virtual void vf9C();
    virtual void vfA4(); // nullsub

    f32 _DC;            // Inited to 1.0
    f32 _E0;            // Inited to 1.0
    f32 _E4;            // Inited to 1.0
    u32 _E8;            // Inited to 0
    u32 _EC;            // Inited to 0
    u32 mEventID2;      // Inited to buildInfo->mEventID2
    u32 mLayer;         // Inited to buildInfo->mLayer
    u32 mMovementID;    // Inited to buildInfo->mMovementID
    u32 mEventID1;      // Inited to buildInfo->mEventID1
    u32 _100;           // Inited to 0
    u8 _104;            // Inited to false
};
