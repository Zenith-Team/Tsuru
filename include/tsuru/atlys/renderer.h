#pragma once

#include "game/graphics/layer/renderobjlayer.h"
#include "agl/lyr/drawmethod.h"
#include "agl/lyr/renderer.h"
#include "agl/renderbuffer.h"
#include "sead/graphicscontext.h"

namespace Atlys {

class Renderer {
public:
    enum LayerID {
        LayerID_Map = 0x7,
        LayerID_Actor = 0x9
    };

private:
    class Layer : public RenderObjLayer {
        SEAD_RTTI_OVERRIDE_IMPL(Layer, RenderObjLayer)

    private:
        inline Layer()
            : RenderObjLayer()
        { }

        friend class agl::lyr::Renderer;
    };

private:
    Renderer();
    ~Renderer();

    void makeLayers();
    void makeDrawMethods();

    void initRendering();

    void initBackgroundBuffer();

    // Draw methods
    void drawLayerMap(const agl::lyr::RenderInfo& renderInfo);
    void drawLayerActors(const agl::lyr::RenderInfo& renderInfo);

    friend class Scene;

    agl::lyr::DrawMethodImpl<Renderer> drawMethodMap;
    agl::lyr::DrawMethodImpl<Renderer> drawMethodActors;

    // Background
    agl::RenderBuffer backgroundBuffer;
    agl::RenderTargetColor backgroundColor;
    sead::GraphicsContext backgroundContext;
    void* backgroundImageData;
};

}
