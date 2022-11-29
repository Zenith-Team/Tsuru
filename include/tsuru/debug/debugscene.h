#pragma once

#include "sead/task.h"
#include "agl/lyr/renderinfo.h"
#include "agl/lyr/drawmethod.h"
#include "tsuru/gtx.h"

class DebugScene : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE_IMPL(DebugScene, sead::CalculateTask);
    SEAD_SINGLETON_TASK(DebugScene);

public:
    DebugScene(const sead::TaskConstructArg& arg);
    virtual ~DebugScene();

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

    void prepare() override;
    void enter() override;
    void calc() override;

    void draw(const agl::lyr::RenderInfo& renderInfo);

    agl::lyr::DrawMethod drawMethod;
    GTX texture;
};
