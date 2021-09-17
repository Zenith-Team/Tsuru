#pragma once

#include <game/actor/courseselect/courseselectactorbase.h>

class CourseSelectActor : public CourseSelectActorBase {
    SEAD_RTTI_OVERRIDE(CourseSelectActor, CourseSelectActor)

public:
    CourseSelectActor(const ActorBuildInfo* buildInfo);
    virtual ~CourseSelectActor();

    u32 onCreate() override = 0;

    u32 beforeExecute() override;
    u32 onExecute() override = 0;

    u32 beforeDraw() override;
    u32 onDraw() override = 0;

    void updateCSScriptInteractions(); // TODO: Verify this name
    bool FUN_21d4dbc(); // Checks some members on CSScriptMgr and the profile ID

    virtual bool vf8C();
    virtual void vf94();
    virtual void vf9C();
    virtual void onCSScriptCommandUpdate(); // nullsub, name may be inaccurate // TODO: Verify this name

    f32 _DC;             // Inited to 1.0
    f32 _E0;             // Inited to 1.0
    f32 _E4;             // Inited to 1.0
    u32 _E8;             // Inited to 0
    u32 _EC;             // Inited to 0
    u32 eventID2;        // Inited to buildInfo->eventID2
    u32 layer;           // Inited to buildInfo->layer
    u32 movementID;      // Inited to buildInfo->movementID
    u32 eventID1;        // Inited to buildInfo->eventID1
    u32 _100;            // Inited to 0
    bool _104;           // Inited to false
};
