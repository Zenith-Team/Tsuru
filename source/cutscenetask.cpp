#include <tsuru/task/cutscenetask.h>
#include <game/task/taskmgr.h>
#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <log.h>
#include <sead/filedevice.h>
#include <sead/filedevicemgr.h>

SEAD_SINGLETON_TASK_IMPL(CutsceneTask)

sead::TaskBase* CutsceneTask::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) CutsceneTask(arg);
}

CutsceneTask::CutsceneTask(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "CutsceneTask")
    , drawMethodCutscene()
    , frame(0)
{ }

void CutsceneTask::prepare() {
    this->adjustHeapAll();
}

void CutsceneTask::enter() {
    LOG("cutscene task enter");

    BIND_DRAW_METHOD(drawMethodCutscene, "Cutscene", &CutsceneTask::drawLayerCutscene, 0xE);
}

void CutsceneTask::calc() {
    LOG("cutscene task calc");
}

void CutsceneTask::drawLayerCutscene(const agl::lyr::RenderInfo& renderInfo) {
    LOG("Drawing frame %u", this->frame); frame++;

    
}
