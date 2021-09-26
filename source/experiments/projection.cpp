#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <tsuru/tsurusavemgr.h>
#include <sead/camera.h>
#include <log.h>
#include <game/playermgr.h>
#include <math.h>

u32 worldMapProjection() {
    switch (TsuruSaveMgr::sSaveData.worldMapPerspective) {
        case 1: {
            static sead::OrthoProjection projection;

            projection.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
            projection.setNearFarClip(-1000.0f, 5000000.0f);

            agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &projection;

            break;
        }

        case 2: {
            static sead::FrustumProjection projection(0.1f, 5000000.0f, 360.0f / 2400.0f, -360.0f / 2400.0f, -640.0f / 2400.0f, 640.0f / 2400.0f);

            agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &projection;

            break;
        }

        default: {
            break;
        }
    }

    return 1;
}

void makePerspectiveLevel() {
    if (!TsuruSaveMgr::sSaveData.perspectiveLevelCameraEnabled)
        ;//return;

    sead::OrthoProjection* oldProj = static_cast<sead::OrthoProjection*>(agl::lyr::Renderer::instance()->layers.buffer[9]->projection);

    static sead::FrustumProjection frustumProj(0.1f, 5000000000.0f, 360.0f / 24000.0f, -360.0f / 24000.0f, -640.0f / 24000.0f, 640.0f / 24000.0f);

    agl::lyr::Renderer::instance()->layers.buffer[9]->projection = &frustumProj;

    //sead::LookAtCamera* cam = static_cast<sead::LookAtCamera*>(agl::lyr::Renderer::instance()->layers.buffer[9]->camera);
    //static f32 zPos = 6000.0f;
    //zPos += 50.0f;
    //cam->pos.z = zPos;
    //cam->doUpdateMatrix(&cam->matrix);
}
