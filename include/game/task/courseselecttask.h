#pragma once

#include "sead/task.h"
#include "game/states.h"
#include "agl/lyr/renderinfo.h"
#include "agl/lyr/drawmethod.h"

class CourseSelectTask : public sead::CalculateTask { // Size: 0xDD0
    SEAD_RTTI_OVERRIDE(CourseSelectTask, sead::CalculateTask);
    SEAD_SINGLETON_TASK(CourseSelectTask);

public:
    virtual ~CourseSelectTask();

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

    void prepare() override;

    void enter() override;
    void exit() override;

    void calc() override;

    // Draws the layer "CourseSelect"
    // @param renderInfo Render info for drawing
    void drawLayerCourseSelect(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "2D"
    // @param renderInfo Render info for drawing
    void drawLayer2D(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "3D"
    // @param renderInfo Render info for drawing
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "3D_World"
    // @param renderInfo Render info for drawing
    void drawLayer3D_World(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "2D_Menu"
    // @param renderInfo Render info for drawing
    void drawLayer2D_Menu(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "2D_TV"
    // @param renderInfo Render info for drawing
    void drawLayer2D_TV(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "2D_Pre3D"
    // @param renderInfo Render info for drawing
    void drawLayer2D_Pre3D(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "CourseSelectDRC"
    // @param renderInfo Render info for drawing
    void drawLayerCourseSelectDRC(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "3D_DRC"
    // @param renderInfo Render info for drawing
    void drawLayer3D_DRC(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "2D_DRC"
    // @param renderInfo Render info for drawing
    void drawLayer2D_DRC(const agl::lyr::RenderInfo& renderInfo);
    // Draws the layer "2D_Pre3D_DRC"
    // @param renderInfo Render info for drawing
    void drawLayer2D_Pre3D_DRC(const agl::lyr::RenderInfo& renderInfo);

    // Spawns the world map camera actor
    void spawnCameraActor();

    // Switches state to a new target state
    // @param state Pointer to target state
    void doStateChange(StateBase* state);

    // Custom function
    void renderCollisions(const agl::lyr::RenderInfo& renderInfo);

    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState1);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState2);
    DECLARE_STATE_VIRTUAL(CourseSelectTask, CourseSelectTaskState3);

    u8 _C8;                                             // C8
    u8 _C9[15];                                         // C9      // Unknown values 1
    StateWrapper<CourseSelectTask> states;              // D8
    agl::lyr::DrawMethod drawMethodCourseSelect;        // FC
    agl::lyr::DrawMethod drawMethod2D;                  // 13C
    agl::lyr::DrawMethod drawMethod3D;                  // 17C
    agl::lyr::DrawMethod drawMethod3D_World;            // 1BC
    agl::lyr::DrawMethod drawMethod2D_Menu;             // 1FC
    agl::lyr::DrawMethod drawMethod2D_TV;               // 23C
    agl::lyr::DrawMethod drawMethod2D_Pre3D;            // 27C
    agl::lyr::DrawMethod drawMethodCourseSelectDRC;     // 2BC
    agl::lyr::DrawMethod drawMethod3D_DRC;              // 2FC
    agl::lyr::DrawMethod drawMethod2D_DRC;              // 33C
    agl::lyr::DrawMethod drawMethod2D_Pre3D_DRC;        // 37C
    u8 _3BC[88];                                        // 3BC     // Is class
    u8 _414[172];                                       // 414     // Is class
    u8 _4C0[88];                                        // 4C0     // Is class
    u8 _518[172];                                       // 518     // Is class
    u8 _5C4[404][4];                                    // 5C4     // Is struct
    u8 _C14[404];                                       // C14     // Is class
    u32 cameraActorID;                                  // DA8
    char* _DAC;                                         // DAC
    u8 _DB0[16];                                        // DB0     // Unknown values 2
    u32 _DC0;                                           // DC0
    u8 _DC4[4];                                         // DC4     // Unknown values 3
    u8 _DC8;                                            // DC8
    u8 _DC9;                                            // DC9
    u8 _DCA;                                            // DCA
    u8 _DCB;                                            // DCB     // Unknown value 4
    u8 _DCC;                                            // DCC
    u8 _DCD;                                            // DCD
    u8 _DCE;                                            // DCE
    u8 _DCF;                                            // DCF
};

//static_assert(sizeof(CourseSelectTask) == 0xDD0, "CourseSelectTask size mismatch");
