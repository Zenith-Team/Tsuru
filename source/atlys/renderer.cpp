#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
#include "tsuru/atlys/map.h"
#include "log.h"
#include "game/actor/actormgr.h"
#include "game/graphics/drawmgr.h"
#include "agl/utl/imagefilter2d.h"
#include "agl/lyr/renderinfo.h"
#include "agl/texturedatainitializer.h"
#include "sead/filedevicemgr.h"
#include "sead/filedevice.h"
#include "sead/new.h"

Atlys::Renderer::Renderer()
    : layerRenderer("Atlys")
    , drawMethodMap()
    , drawMethodActors()
    , nodeTex("tsuru/uhhuh.gtx")
{ }

void Atlys::Renderer::makeLayers() {
    this->layerRenderer.init(2, 512, 5, 5, nullptr);

    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Map, "Map", agl::lyr::DisplayType_TopTV, nullptr);
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Actor, "Actors", agl::lyr::DisplayType_TopTV, nullptr)->setParentRenderer(&this->layerRenderer);
}
#include "tringle.hpp"
#include "dynlibs/gx2/functions.h"
    const f32 pos_data[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GX2FetchShader triangle_FSH;
void Atlys::Renderer::init(Atlys::Camera* camera) {
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        Atlys::Scene::instance()->map->layers[i].gtx.load(Atlys::Scene::instance()->map->layers[i].gtxName);
    }

    agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Map]->camera = &camera->camera;
    agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Map]->projection = &camera->projection;

    GX2Invalidate(GX2_INVALIDATE_CPU, triangle_VSH.shaderData, triangle_VSH.shaderSize);
    GX2Invalidate(GX2_INVALIDATE_CPU, triangle_PSH.shaderData, triangle_PSH.shaderSize);



    GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, (void*)pos_data, sizeof(pos_data));

    u32 VBO = 0;
    GX2SetAttribBuffer(VBO, sizeof(pos_data), 3 * sizeof(f32), pos_data);

    GX2AttribStream pos_stream;
    pos_stream.location = 0;
    pos_stream.buffer = VBO;
    pos_stream.format = GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT;
    pos_stream.destinationSelector = 0x00010205;
    pos_stream.endianSwap = GX2_ENDIANSWAP_DEFAULT;
    pos_stream.indexType = GX2_ATTRIB_INDEX_PER_VERTEX;
    pos_stream.divisor = 0;

    u32 triangle_FSH_size = GX2CalcFetchShaderSizeEx(1, GX2_FETCH_SHADER_TESSELATION_NONE, GX2_TESSELLATION_MODE_DISCRETE);
    void* triangle_FSH_program = new(nullptr, GX2_SHADER_ALIGNMENT) u8[triangle_FSH_size];

    GX2InitFetchShaderEx(&triangle_FSH, (u8*)triangle_FSH_program, 1, &pos_stream, GX2_FETCH_SHADER_TESSELATION_NONE, GX2_TESSELLATION_MODE_DISCRETE);

    GX2Invalidate(GX2_INVALIDATE_CPU, triangle_FSH.shaderProgram, triangle_FSH.shaderSize);
    GX2SetDepthOnlyControl(false, false, GX2_COMPARE_EQUAL);
}

void Atlys::Renderer::activate() {
    this->bindDrawMethods();
}

void Atlys::Renderer::bindDrawMethods() {
    BIND_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    BIND_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {/*
    //* Render layers
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->layerCount; i++) {
        agl::utl::ImageFilter2D::drawTextureMSAA(Atlys::Scene::instance()->map->layers[i].gtx.texture, *renderInfo.viewport, Vec2f(1.0f), Vec2f(0.0f));
    }

    //* Render nodes
    for (u32 i = 0; i < Atlys::Scene::instance()->map->info->nodeCount; i++) {
        Vec2f nodePos2D(0.0f); nodePos2D.x = Atlys::Scene::instance()->map->nodes[i].position.x; nodePos2D.y = Atlys::Scene::instance()->map->nodes[i].position.y;
        agl::utl::ImageFilter2D::drawTextureMSAA(this->nodeTex.texture, *renderInfo.viewport, Vec2f(0.5f), nodePos2D);
    }
    

    //* Render player
    Vec2f playerPos2D(0.0f); playerPos2D.x = Atlys::Scene::instance()->player->position.x; playerPos2D.y = Atlys::Scene::instance()->player->position.y;
    agl::utl::ImageFilter2D::drawTextureMSAA(Atlys::Scene::instance()->player->tex.texture, *renderInfo.viewport, Vec2f(0.05f), playerPos2D);*/

    
    GX2SetShaderModeEx(GX2_SHADER_MODE_UNIFORM_REGISTER, 48, 64, 0, 0, 200, 192);
    GX2SetFetchShader(&triangle_FSH);
    GX2SetVertexShader(&triangle_VSH);
    GX2SetPixelShader(&triangle_PSH);
    GX2DrawEx(GX2_PRIMITIVE_TRIANGLES, 3, 0, 1);
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];
    if (Atlys::Renderer::LayerID_Actor < agl::lyr::Renderer::instance()->layers.size)
        layer = agl::lyr::Renderer::instance()->layers.buffer[Atlys::Renderer::LayerID_Actor];

    DrawMgr::instance()->setTargetLayer(layer, 1);

    ActorMgr::instance()->drawActors();

    DrawMgr::instance()->resetTargetLayer();
}
