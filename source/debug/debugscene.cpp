#include "tsuru/debug/debugscene.h"
#include "agl/lyr/renderer.h" 
#include "agl/utl/devtools.h"
#include "sead/graphicscontext.h"

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
    this->texture.load("tsuru/font.gtx");
}

void DebugScene::enter() {
    void (DebugScene::*drawFunc)(const agl::lyr::RenderInfo&) = &DebugScene::draw;

    BIND_DRAW_METHOD(this->drawMethod, "DebugMain", *((agl::lyr::DrawMethod::PTMF*)&drawFunc), 0xE, this);
}

void DebugScene::calc() {
    
}

void DebugScene::draw(const agl::lyr::RenderInfo& renderInfo) {
    Mtx44 vp;
    sead::Matrix44CalcCommon<f32>::multiply(vp, renderInfo.projection->getDeviceProjectionMatrix(), renderInfo.camera->matrix);

    Mtx34 qmtx;
    qmtx.makeSRT(Vec2f(56, 46), 0, 0);

    agl::utl::DevTools::drawTextureTexCoord(this->texture.texture, qmtx, vp, 0.125f, 0, Vec2f(0,0.5f));
}
