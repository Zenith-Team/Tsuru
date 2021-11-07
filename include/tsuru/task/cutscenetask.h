#pragma once

#include "log.h"
#include "dynlibs/h264/functions.h"
#include "dynlibs/os/functions.h"
#include <agl/lyr/drawmethod.h>
#include <sead.h>

class CutsceneTask : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE_IMPL(CutsceneTask, sead::CalculateTask)
    SEAD_SINGLETON_TASK(CutsceneTask)

public:
    CutsceneTask(const sead::TaskConstructArg& arg);
    virtual ~CutsceneTask() { }

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

    void prepare() override;
    void enter() override;
    void calc() override;

    void drawLayerCutscene(const agl::lyr::RenderInfo& renderInfo);

    agl::lyr::DrawMethod drawMethodCutscene;
    u32 frame;
    const char* videoFile;
};
