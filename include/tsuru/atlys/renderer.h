#pragma once

#include "game/graphics/layer/renderobjlayer.h"
#include "game/graphics/layer/objlayerrenderer.h"
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
    Renderer();
    ~Renderer();

    void init();

    void makeLayers();
    void makeDrawMethods();

    void loadMapLayers();

    // Draw methods
    void drawLayerMap(const agl::lyr::RenderInfo& renderInfo);
    void drawLayerActors(const agl::lyr::RenderInfo& renderInfo);

    friend class Scene;

    ObjLayerRenderer layerRenderer;
    agl::lyr::DrawMethodImpl<Renderer> drawMethodMap;
    agl::lyr::DrawMethodImpl<Renderer> drawMethodActors;

    //! Temp
    agl::TextureSampler background;
    agl::TextureData backgroundTexture;
    u8* backgroundRaw;
};

}
