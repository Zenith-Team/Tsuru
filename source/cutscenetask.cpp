#include "tsuru/task/cutscenetask.h"
#include "game/task/taskmgr.h"
#include "agl/lyr/renderer.h"
#include "agl/lyr/layer.h"
#include "log.h"
#include "sead/filedevice.h"
#include "sead/filedevicemgr.h"
#include "agl/lyr/renderinfo.h"

SEAD_SINGLETON_TASK_IMPL(CutsceneTask)

sead::TaskBase* CutsceneTask::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) CutsceneTask(arg);
}

CutsceneTask::CutsceneTask(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "CutsceneTask")
    , drawMethodCutscene()
{ }

void CutsceneTask::prepare() {
    this->lyt.init();
    this->lyt.getArchive("Common");
    this->lyt.loadBFLYT("PaBattery.bflyt");

    this->adjustHeapAll();
}

void CutsceneTask::enter() {
    BIND_DRAW_METHOD(drawMethodCutscene, "Cutscene", &CutsceneTask::drawLayerCutscene, 0xE);
}

void CutsceneTask::calc() {
    this->lyt.update(0xE);
}

void CutsceneTask::drawLayerCutscene(const agl::lyr::RenderInfo& renderInfo) {
    this->lyt.draw(renderInfo.projection->getDeviceProjectionMatrix());
}
