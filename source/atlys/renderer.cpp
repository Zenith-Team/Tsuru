#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
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
    , bgsampler()
    , bgtexture()
    , bgtexdata(nullptr)
    , bgtexsize(0)
{ }

Atlys::Renderer::~Renderer() {
    delete[] this->bgtexdata;
    this->bgtexdata = nullptr;
}

void Atlys::Renderer::makeLayers() {
    this->layerRenderer.init(2, 512, 5, 5, nullptr);

    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Map, "Map", agl::lyr::DisplayType_TopTV, nullptr);
    agl::lyr::Renderer::instance()->createLayer<RenderObjLayer>(Atlys::Renderer::LayerID_Actor, "Actors", agl::lyr::DisplayType_TopTV, nullptr);
}

void Atlys::Renderer::loadbg() {
    //! --- File Data ---
    sead::FileHandle handle;
    if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, "tsuru/tex.gtx", sead::FileDevice::FileOpenFlag_ReadOnly, 0)) {
        LOG("File does not exist?");
    }

    this->bgtexsize = handle.getFileSize();
    if (this->bgtexsize == 0) {
        LOG("Filesize is 0");
    }

    //! --- Surface ---
    this->bgtexdata = new(nullptr, 0x2000) u8[this->bgtexsize];
    u32 bytesread = handle.read(this->bgtexdata, this->bgtexsize);
    if (bytesread != this->bgtexsize) {
        LOG("no");
    }

    //! --- TextureData ---
    agl::TextureDataInitializerGTX::initialize(&this->bgtexture, this->bgtexdata, 0);
    this->bgtexture.invalidateGPUCache();

    //! --- TextureSampler ---
    this->bgsampler.applyTextureData(this->bgtexture);
}

void Atlys::Renderer::init() {
    this->makeDrawMethods();
}

void Atlys::Renderer::makeDrawMethods() {
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    if (this->bgsampler.isTexValid)
        agl::utl::ImageFilter2D::drawTextureMSAA(this->bgsampler, *renderInfo.viewport, Vec2f(1.0f), Vec2f(0.0f), 3);
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    ActorMgr::instance()->drawActors();
}
