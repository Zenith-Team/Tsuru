#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
#include "log.h"
#include "game/actor/actormgr.h"
#include "game/graphics/drawmgr.h"
#include "agl/utl/imagefilter2d.h"
#include "agl/lyr/renderinfo.h"
#include "sead/filedevicemgr.h"
#include "sead/filedevice.h"
#include "sead/new.h"
#include "sead/primitiverenderer.h"

Atlys::Renderer::Renderer()
    : layerRenderer("Atlys")
    , drawMethodMap()
    , drawMethodActors()
    , bgsampler()
    , bgsurface()
    , bgtexture()
    , bgtexdata(nullptr)
    , bgtexsize(245760) 
{ }

Atlys::Renderer::~Renderer() {
    delete this->bgtexdata; this->bgtexdata = nullptr;
}

void Atlys::Renderer::makeLayers() {
    this->layerRenderer.init(2, 512, 5, 5, nullptr);

    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Map, "Map", agl::lyr::DisplayType_TopTV, nullptr);
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Actor, "Actors", agl::lyr::DisplayType_TopTV, nullptr);
}

void Atlys::Renderer::loadbg() {
    //! --- Surface ---
    sead::FileHandle handle;
    sead::FileDeviceMgr::instance()->tryOpen(&handle, "tsuru/tex.bin", sead::FileDevice::FileOpenFlag_ReadOnly, 0);
    this->bgtexdata = new(nullptr, 2048) u8[this->bgtexsize];
    u32 bytesread = handle.read(this->bgtexdata, this->bgtexsize);
    if (bytesread != this->bgtexsize)
        LOG("no");

    bgsurface.dimension = GX2_SURFACE_DIM_2D;
    bgsurface.width = 225;
    bgsurface.height = 225;
    bgsurface.depth = 1;
    bgsurface.numMips = 1;
    bgsurface.format = GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM;
    bgsurface.aa = GX2_AA_MODE_1X;
    bgsurface.use = GX2_SURFACE_USE_TEXTURE;
    bgsurface.imageSize = this->bgtexsize;
    bgsurface.imageData = this->bgtexdata;
    bgsurface.mipSize = 0;
    bgsurface.mipData = nullptr;
    bgsurface.tile = GX2_TILE_MODE_2D_THIN1;
    bgsurface.swizzle = 0xD0000;
    bgsurface.align = 2048;
    bgsurface.pitch = 256;

    //! --- TextureData ---
    this->bgtexture.initializeFromSurface(this->bgsurface);
    
    //! --- TextureSampler ---
    this->bgsampler.applyTextureData_(this->bgtexture);
}

void Atlys::Renderer::init() {
    this->makeDrawMethods();
}

void Atlys::Renderer::makeDrawMethods() {
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
    sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
    sead::PrimitiveRenderer::instance()->begin();
    sead::PrimitiveRenderer::instance()->drawCube(Vec3f(0.0f), 0.25, sead::colorMagenta);
    sead::PrimitiveRenderer::instance()->end();
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    ActorMgr::instance()->drawActors();
}
