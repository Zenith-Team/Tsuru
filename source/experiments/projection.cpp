#include <agl/lyr/renderer.h>
#include <agl/lyr/layer.h>
#include <sead/projection.h>
#include <tsuru/save/managers/tsurusavemgr.h>
#include <sead/camera.h>
#include <log.h>
#include <game/playermgr.h>
#include <math/functions.h>
#include <game/level/levelinfo.h>

u32 worldMapProjection() {
    {   // Orthographic projection
        static sead::OrthoProjection projection;

        projection.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
        projection.setNearFarClip(-1000.0f, 5000000.0f);

        agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &projection;

        return 1;   // Remove this if you wanna use frustum instead
    }

    {   // Frustum projection
        static sead::FrustumProjection projection(0.1f, 5000000.0f, 360.0f / 2400.0f, -360.0f / 2400.0f, -640.0f / 2400.0f, 640.0f / 2400.0f);

        agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &projection;

        return 1;
    }
}

void makePerspectiveLevel() {
/*
    if (LevelInfo::instance()->world == 0 && LevelInfo::instance()->level == 0) {
        sead::OrthoProjection* oldProj = static_cast<sead::OrthoProjection*>(agl::lyr::Renderer::instance()->layers.buffer[9]->projection);

        static sead::FrustumProjection frustumProj(0.1f, 5000000000.0f, 360.0f / 24000.0f, -360.0f / 24000.0f, -640.0f / 24000.0f, 640.0f / 24000.0f);

        agl::lyr::Renderer::instance()->layers.buffer[9]->projection = &frustumProj;

        static u32 timer = 0;
        timer++;

        if (timer < 60 * 5)
            return;

        sead::LookAtCamera* cam = static_cast<sead::LookAtCamera*>(agl::lyr::Renderer::instance()->layers.buffer[9]->camera);

        static f32 zPos = 10000.0f;
        zPos -= 50.0f;

        cam->pos.z = zPos;
        cam->at.z = -999999.0f;

        cam->doUpdateMatrix(&cam->matrix);
    }
*/

    sead::LookAtCamera* cam = static_cast<sead::LookAtCamera*>(agl::lyr::Renderer::instance()->layers.buffer[9]->camera);

    static f32 timer = 0.0f;
    timer += 0.003f;

    const f32 radius = 10000.0f;
    cam->pos.x = sinf(timer) * radius;
    cam->pos.z = cosf(timer) * radius;

    cam->doUpdateMatrix(&cam->matrix);
}
