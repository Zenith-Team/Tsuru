#include "tsuru/atlys/renderer.h"
#include "tsuru/atlys/scene.h"
#include "log.h"
#include "game/actor/actormgr.h"
#include "dynlibs/gx2/functions.h"
#include "agl/driver/gx2resource.h"

Atlys::Renderer::Renderer()
    : drawMethodMap()
    , drawMethodActors()
    // Background
    , backgroundBuffer()
    , backgroundColor()
    , backgroundContext()
    , backgroundImageData(nullptr)
{
    backgroundBuffer.initialize();
}

Atlys::Renderer::~Renderer() {
    delete[] this->backgroundImageData; this->backgroundImageData = nullptr;
}

void Atlys::Renderer::makeLayers() {
    // These are also required for levels because it will crash when it tries to access layers with these IDs, since it assumes CourseSelectTask made them
    agl::lyr::Renderer::instance()->createLayer<Atlys::Renderer::Layer>(Atlys::Renderer::LayerID_Map, "Map", 0, nullptr);
    agl::lyr::Renderer::instance()->createLayer<Atlys::Renderer::Layer>(Atlys::Renderer::LayerID_Actor, "Actors", 0, nullptr);
}

void Atlys::Renderer::makeDrawMethods() {
    MAKE_DRAW_METHOD(drawMethodMap, "Map", &Atlys::Renderer::drawLayerMap, Atlys::Renderer::LayerID_Map);
    MAKE_DRAW_METHOD(drawMethodActors, "Actors", &Atlys::Renderer::drawLayerActors, Atlys::Renderer::LayerID_Actor);
}

void Atlys::Renderer::initRendering() {
    this->initBackgroundBuffer();
}

void Atlys::Renderer::initBackgroundBuffer() {
    LOG("Initializing background buffer...");

    this->backgroundColor.colorBuffer.surface.dimension = GX2_SURFACE_DIM_2D;
    this->backgroundColor.colorBuffer.surface.width = 1280;
    this->backgroundColor.colorBuffer.surface.height = 720;
    this->backgroundColor.colorBuffer.surface.depth = 1;
    this->backgroundColor.colorBuffer.surface.mipSize = 1;
    this->backgroundColor.colorBuffer.surface.format = GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM;
    this->backgroundColor.colorBuffer.surface.aa = GX2_AA_MODE_1X;
    this->backgroundColor.colorBuffer.surface.use = GX2_SURFACE_USE_COLOR_BUFFER_TEXTURE_FTV;
    this->backgroundColor.colorBuffer.surface.mipData = nullptr;
    this->backgroundColor.colorBuffer.surface.tile = GX2_TILE_MODE_DEFAULT;
    this->backgroundColor.colorBuffer.surface.swizzle = 0;
    this->backgroundColor.colorBuffer.viewMip = 0;
    this->backgroundColor.colorBuffer.viewFirstSlice = 0;
    this->backgroundColor.colorBuffer.viewSlicesCount = 1;

    this->backgroundBuffer.targetColors[0] = &this->backgroundColor;
    this->backgroundContext.depthWriteEnable = false;
    this->backgroundContext.depthEnable = false;
    this->backgroundContext.apply();

    GX2CalcSurfaceSizeAndAlignment(&this->backgroundColor.colorBuffer.surface);
    this->backgroundImageData = new(nullptr, this->backgroundColor.colorBuffer.surface.align) u8[this->backgroundColor.colorBuffer.surface.imageSize];

    if (!this->backgroundImageData) {
        LOG("It's null");
    } else {
        LOG("It's not null");
    }
}

void Atlys::Renderer::drawLayerMap(const agl::lyr::RenderInfo& renderInfo) {
    sead::Color4f clearColor(1.0f, 0.5f, 0.25f, 1.0f);

    LOG("Rendering...");

    this->backgroundBuffer.clear(0, 0, clearColor, 0.0f, 0);
    this->backgroundBuffer.bind();

    GX2CopyColorBufferToScanBuffer(&this->backgroundBuffer.targetColors[0]->colorBuffer, 1);

    agl::driver::GX2Resource::instance()->restoreContextState();
}

void Atlys::Renderer::drawLayerActors(const agl::lyr::RenderInfo& renderInfo) {
    ActorMgr::instance()->drawActors();
}
