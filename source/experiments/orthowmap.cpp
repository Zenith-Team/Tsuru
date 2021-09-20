#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <tsuru/tsurusavemgr.h>

u32 makeOrthoWmap() {
    static sead::OrthoProjection orthoProj;
    orthoProj.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
    orthoProj._94 = -10000.0f;
    orthoProj._98 = 5000000.0f;
    orthoProj.dirty = true;

    if (TsuruSaveMgr::sSaveData.orthographicWorldMapEnabled)
        agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &orthoProj;

    return 1;
}
