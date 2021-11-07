#include <tsuru/task/cutscenetask.h>
#include <game/task/taskmgr.h>
#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <log.h>
#include <sead/filedevice.h>
#include <sead/filedevicemgr.h>

template <>
const char sead::SafeString::sNullChar = '\0';

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

    // TODO: Make a macro for this
    this->drawMethodCutscene.name = "Cutscene";

    this->drawMethodCutscene._18 = 1;
    this->drawMethodCutscene._20 = 0x10177234;
    this->drawMethodCutscene._24 = this;

    this->drawMethodCutscene.method = static_cast<agl::lyr::DrawMethod::PTMF>(&CutsceneTask::drawLayerCutscene);

    agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];
    if (0xE < agl::lyr::Renderer::instance()->layers.size)
        layer = agl::lyr::Renderer::instance()->layers.buffer[0xE];

    layer->pushBackDrawMethod(0, &this->drawMethodCutscene);
}

void CutsceneTask::calc() {
    LOG("cutscene task calc");
}

void CutsceneTask::drawLayerCutscene(const agl::lyr::RenderInfo& renderInfo) {
    LOG("Drawing frame %u", this->frame); frame++;

    
}
