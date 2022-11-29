#include "tsuru/debug/debugscene.h"
#include "agl/lyr/renderer.h" 
#include "agl/utl/devtools.h"
#include "sead/graphicscontext.h"
#include "tsuru/fonts.h"

SEAD_SINGLETON_TASK_IMPL(DebugScene);

DebugScene::DebugScene(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "DebugScene")
{
    DebugScene::setInstance(this);
}

DebugScene::~DebugScene() { }

sead::TaskBase* DebugScene::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) DebugScene(arg);
}

void DebugScene::prepare() {
    this->font.load("tsuru/font.gtx", 10, 24, 40, Fonts::TestFont);
}

void DebugScene::enter() {
    void (DebugScene::*drawFunc)(const agl::lyr::RenderInfo&) = &DebugScene::draw;

    BIND_DRAW_METHOD(this->drawMethod, "DebugMain", *((agl::lyr::DrawMethod::PTMF*)&drawFunc), 0xE, this);
}

void DebugScene::calc() {
    
}

void DebugScene::draw(const agl::lyr::RenderInfo& renderInfo) {
    renderInfo.frameBuffer->clear(1, sead::Color4f(0x1F2424FF), 1, 0);

    Mtx44 vp;
    sead::Matrix44CalcCommon<f32>::multiply(vp, renderInfo.projection->getDeviceProjectionMatrix(), renderInfo.camera->matrix);

    this->font.renderBitmap(vp, Vec2f(-550.0f, 320.0f));
    this->font.renderText(vp, "Hello World!", Vec2f(-200.0f, 320.0f));
    this->font.newline(-200.0f);
    this->font.renderText(vp, "Goodbye...");
    this->font.renderText(vp, " world.");
    this->font.newline(-200.0f);
    this->font.newline(-200.0f);
    this->font.renderText(vp, "2 + 2 = Fish");
}
