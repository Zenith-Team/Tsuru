#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <tsuru/tsurusavemgr.h>
#include <sead/camera.h>
#include <log.h>
#include <game/playermgr.h>

u32 makeOrthoWmap() {
    if (!TsuruSaveMgr::sSaveData.orthographicWorldMapEnabled)
        return;

    static sead::OrthoProjection orthoProj;
    orthoProj.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
    orthoProj.nearClip = -10000.0f;
    orthoProj.farClip = 5000000.0f;
    orthoProj.dirty = true;

    agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &orthoProj;

    return 1;
}

void makePerspectiveLevel() {
    if (!TsuruSaveMgr::sSaveData.perspectiveLevelCameraEnabled)
        return;

    static sead::PerspectiveProjection persProj;
    persProj.set(0.00000000000000001f, 3402823466385288598117041834845169240.0000000000000000f, 0.274255f, 1.777778f);

    agl::lyr::Renderer::instance()->layers.buffer[9]->projection = &persProj;

    sead::LookAtCamera* cam = static_cast<sead::LookAtCamera*>(agl::lyr::Renderer::instance()->layers.buffer[9]->camera);

    f32 posz = PlayerMgr::instance()->players[0]->position.z - 100000.0f;
    f32 posx = PlayerMgr::instance()->players[0]->position.x + 500.0f;

    cam->pos = PlayerMgr::instance()->players[0]->position;
    cam->pos.z = posz;
    cam->pos.x = posx;

    cam->doUpdateMatrix(&cam->matrix);

    LOG("x %f", cam->pos.x);
    LOG("z %f", cam->pos.z);
    LOG("y %f", cam->pos.y);
}
