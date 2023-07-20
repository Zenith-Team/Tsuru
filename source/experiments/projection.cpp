#include "agl/lyr/renderer.h"
#include "agl/lyr/layer.h"
#include "sead/projection.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "sead/camera.h"
#include "log.h"
#include "game/playermgr.h"
#include "math/functions.h"
#include "game/level/levelinfo.h"

#include "dynlibs/gx2/functions.h"

#define ORTHO

u32 worldMapProjection() {
#ifdef ORTHO
    {   // Orthographic projection
        static sead::OrthoProjection projection;

        projection.setTBLR(360.0f, -360.0f, -640.0f, 640.0f);
        projection.setNearFarClip(-1000.0f, 5000000.0f);

        agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &projection;

        return 1;
    }
#else
    {   // Frustum projection
        static sead::FrustumProjection projection(0.1f, 5000000.0f, 360.0f / 2400.0f, -360.0f / 2400.0f, -640.0f / 2400.0f, 640.0f / 2400.0f);

        agl::lyr::Renderer::instance()->layers.buffer[7]->projection = &projection;

        return 1;
    }
#endif
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

sead::Matrix44<f32>* getIdentMtx44()
{
    static sead::Matrix44<f32> mtx;
    mtx.m[0][0] = 1.0f;
    mtx.m[0][1] = 0.0f;
    mtx.m[0][2] = 0.0f;
    mtx.m[0][3] = 0.0f;

    mtx.m[1][0] = 0.0f;
    mtx.m[1][1] = 1.0f;
    mtx.m[1][2] = 0.0f;
    mtx.m[1][3] = 0.0f;
    
    mtx.m[2][0] = 0.0f;
    mtx.m[2][1] = 0.0f;
    mtx.m[2][2] = 1.0f;
    mtx.m[2][3] = 0.0f;
    
    mtx.m[3][0] = 0.0f;
    mtx.m[3][1] = 0.0f;
    mtx.m[3][2] = 0.0f;
    mtx.m[3][3] = 1.0f;

    return &mtx;
}

void projThingV(u32 r3, u32 r4, u32 r5)
{
    static sead::FrustumProjection frustumProj(0.1f, 5000000000.0f, 360.0f / 24000.0f, -360.0f / 24000.0f, -640.0f / 24000.0f, 640.0f / 24000.0f);

    agl::lyr::Renderer::instance()->layers.buffer[9]->projection = &frustumProj;

    const Mtx44& mtx = agl::lyr::Renderer::instance()->layers[9]->projection->getDeviceProjectionMatrix();
    GX2SetVertexUniformReg(r3, r4, (void*)r5);
}

void projThingF(u32 r3, u32 r4, u32 r5)
{
    const Mtx44& mtx = agl::lyr::Renderer::instance()->layers[9]->projection->getDeviceProjectionMatrix();
    GX2SetPixelUniformReg(r3, r4, (void*)r5);
}
