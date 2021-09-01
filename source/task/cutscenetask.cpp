#include <custom/task/cutscenetask.h>
#include <game/task/taskmgr.h>
#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <log.h>

template <>
const char sead::SafeString::sNullChar = '\0';

SEAD_SINGLETON_TASK_IMPL(CutsceneTask)

sead::TaskBase* CutsceneTask::construct(const sead::TaskConstructArg& arg) {
    LOG("cutscene task construct");

    return new(arg.mHeapArray->mHeaps[arg.mHeapArray->mPrimaryIndex], 4) CutsceneTask(arg);
}

CutsceneTask::CutsceneTask(const sead::TaskConstructArg& arg)
    : CalculateTask(arg, "CutsceneTask")
    , drawMethodCutscene()
{
    LOG("cutscene task ctor");
}

void CutsceneTask::prepare() {
    LOG("cutscene task prepare");
    this->adjustHeapAll();
}

void CutsceneTask::enter() {
    LOG("cutscene task enter");

    // Most of this is a copy of GameOverScene's behavior
    this->drawMethodCutscene.name = "Cutscene";

    this->drawMethodCutscene._18 = 1;
    this->drawMethodCutscene._24 = this;
    
    this->drawMethodCutscene.method = static_cast<agl::lyr::DrawMethod::PTMF>(&CutsceneTask::drawLayerCutscene);

    agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.mBuffer[0];
    if (0xE < agl::lyr::Renderer::instance()->layers.mSize)
        layer = agl::lyr::Renderer::instance()->layers.mBuffer[0xE];
    
    layer->pushBackDrawMethod(0, &this->drawMethodCutscene);
}

void CutsceneTask::calc() {
    LOG("cutscene task calc");
}

void CutsceneTask::drawLayerCutscene(const agl::lyr::RenderInfo& renderInfo) {
    LOG("cutscene tasking successfully");
}
