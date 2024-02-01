#include "agl/lyr/renderer.h"
#include "agl/lyr/layer.h"
#include "sead/projection.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "sead/camera.h"
#include "tsuru/log.h"
#include "game/playermgr.h"
#include "math/functions.h"
#include "game/level/levelinfo.h"
#include "imgui/imgui.h"

#include "sdk/gx2/functions.h"

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

sead::Matrix44<f32>* getIdentMtx44() {
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

void lerpMtx44(sead::Matrix44f* out, const sead::Matrix44f& mtx1, const sead::Matrix44f& mtx2, f32 c) {
    if (!out)
        return;

    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 4; j++) {
            f32 a = mtx1.m[i][j];
            f32 b = mtx2.m[i][j];

            f32 d = a - b;

            if (d < 0)
                d = b - a;

            if (a < b)
                out->m[i][j] = a + ((d / 100) * c * 100);
            else
                out->m[i][j] = a - ((d / 100) * c * 100);
        }
    }
}

void mtx34ImGui(sead::Matrix34f& mtx, const char* str) {
    ImGui::Text(str);
    ImGui::DragFloat4("[0]", &mtx.m[0][0], 0.05f, -500.0f, 500.0f);
    ImGui::DragFloat4("[1]", &mtx.m[1][0], 0.05f, -500.0f, 500.0f);
    ImGui::DragFloat4("[2]", &mtx.m[2][0], 0.05f, -500.0f, 500.0f);
}

void mtx44ImGui(sead::Matrix44f& mtx, const char* str) {
    ImGui::Text(str);
    ImGui::DragFloat4("[0]", &mtx.m[0][0], 1.1f, -500.0f, 500.0f);
    ImGui::DragFloat4("[1]", &mtx.m[1][0], 1.1f, -500.0f, 500.0f);
    ImGui::DragFloat4("[2]", &mtx.m[2][0], 1.1f, -500.0f, 500.0f);
    ImGui::DragFloat4("[3]", &mtx.m[3][0], 1.1f, -500.0f, 500.0f);
}

void projThing(u32 offset, u32 count, sead::Matrix44f* projMtx) {
    const sead::Matrix44f& perspProj = agl::lyr::Renderer::instance()->layers[5]->projection->getDeviceProjectionMatrix();

    static f32 slider = 0.0f;
    static sead::Matrix44f mtx;

    ImGui::Begin("proj"); {
        static f32 f = -1.0f;
        ImGui::DragFloat("a", &f);
        ImGui::SliderFloat("slider", &slider, 0.0f, 1.0f);
        lerpMtx44(&mtx, *projMtx, perspProj, slider);
        mtx44ImGui(*projMtx, "projMtx");
        mtx44ImGui(const_cast<sead::Matrix44f&>(perspProj), "perspProj");
        mtx44ImGui(mtx, "mtx");
        ImGui::ShowDemoWindow();
    }
    ImGui::End();

    GX2SetVertexUniformReg(offset, count, (void*)&mtx);
}
