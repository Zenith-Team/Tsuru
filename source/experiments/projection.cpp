#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <tsuru/tsurusavemgr.h>
#include <sead/camera.h>
#include <log.h>
#include <game/playermgr.h>
#include <math.h>

u32 makeOrthoWmap() {
    if (!TsuruSaveMgr::sSaveData.orthographicWorldMapEnabled)
        return;

    static sead::OrthoProjection orthoProj;

    orthoProj.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
    orthoProj.setNearFarClip(-1000.0f, 5000000.0f);

    agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &orthoProj;

    return 1;
}

void makePerspectiveLevel() {
    if (!TsuruSaveMgr::sSaveData.perspectiveLevelCameraEnabled)
        return;

    static sead::PerspectiveProjection persProj;
    persProj.set(0.1f, 5000000.0f, degToRad(16), 1280.0f / 720.0f);

    agl::lyr::Renderer::instance()->layers.buffer[9]->projection = &persProj;

    sead::LookAtCamera* cam = static_cast<sead::LookAtCamera*>(agl::lyr::Renderer::instance()->layers.buffer[9]->camera);

    cam->pos = PlayerMgr::instance()->players[0]->position;
    cam->pos.x += 500.0f;
    cam->pos.z += 10000.0f;

    cam->doUpdateMatrix(&cam->matrix);

    LOG("x %f", cam->pos.x);
    LOG("y %f", cam->pos.y);
    LOG("z %f", cam->pos.z);
}
