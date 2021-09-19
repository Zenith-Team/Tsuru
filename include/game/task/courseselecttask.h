#pragma once

#include <sead/task.h>
#include <game/states.h>
#include <agl/lyr/renderinfo.h>
#include <agl/lyr/drawmethod.h>

class CourseSelectTask : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE(CourseSelectTask, sead::CalculateTask)
    SEAD_SINGLETON_TASK(CourseSelectTask)

public:
    virtual ~CourseSelectTask();

    void prepare() override;

    void enter() override;
    void exit() override;

    void calc() override;

    void drawLayerCourseSelect(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer2D(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer3D_World(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer2D_Menu(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer2D_TV(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer2D_Pre3D(const agl::lyr::RenderInfo& renderInfo);
    void drawLayerCourseSelectDRC(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer3D_DRC(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer2D_DRC(const agl::lyr::RenderInfo& renderInfo);
    void drawLayer2D_Pre3D_DRC(const agl::lyr::RenderInfo& renderInfo);

    void spawnCameraActor();
    void doStateChange(StateBase* state);

    // Custom function
    void renderCollisions(const agl::lyr::RenderInfo& renderInfo);

    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState1);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState2);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState3);

    u8 _C8;                                             // _C8
    u8 _C9[15];                                         // _C9      // Unknown values 1
    StateWrapper<CourseSelectTask> states;              // _D8
    agl::lyr::DrawMethod drawMethodCourseSelect;        // _FC
    agl::lyr::DrawMethod drawMethod2D;                  // _13C
    agl::lyr::DrawMethod drawMethod3D;                  // _17C
    agl::lyr::DrawMethod drawMethod3D_World;            // _1BC
    agl::lyr::DrawMethod drawMethod2D_Menu;             // _1FC
    agl::lyr::DrawMethod drawMethod2D_TV;               // _23C
    agl::lyr::DrawMethod drawMethod2D_Pre3D;            // _27C
    agl::lyr::DrawMethod drawMethodCourseSelectDRC;     // _2BC
    agl::lyr::DrawMethod drawMethod3D_DRC;              // _2FC
    agl::lyr::DrawMethod drawMethod2D_DRC;              // _33C
    agl::lyr::DrawMethod drawMethod2D_Pre3D_DRC;        // _37C
    u8 _3BC[88];                                        // _3BC     // Is class
    u8 _414[172];                                       // _414     // Is class
    u8 _4C0[88];                                        // _4C0     // Is class
    u8 _518[172];                                       // _518     // Is class
    u8 _5C4[404][4];                                    // _5C4     // Is struct
    u8 _C14[404];                                       // _C14     // Is class
    u32 cameraActorID;                                  // _DA8
    char* _DAC;                                         // _DAC
    u8 _DB0[16];                                        // _DB0     // Unknown values 2
    u32 _DC0;                                           // _DC0
    u8 _DC4[4];                                         // _DC4     // Unknown values 3
    u8 _DC8;                                            // _DC8
    u8 _DC9;                                            // _DC9
    u8 _DCA;                                            // _DCA
    u8 _DCB;                                            // _DCB     // Unknown value 4
    u8 _DCC;                                            // _DCC
    u8 _DCD;                                            // _DCD
    u8 _DCE;                                            // _DCE
    u8 _DCF;                                            // _DCF
};
