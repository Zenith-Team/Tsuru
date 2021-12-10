#pragma once

#include "game/graphics/layer/renderobjlayer.h"
#include "game/graphics/layer/objlayerrenderer.h"
#include "agl/lyr/drawmethod.h"
#include "agl/lyr/renderer.h"
#include "agl/renderbuffer.h"
#include "sead/graphicscontext.h"
#include "tsuru/gtx.h"
#include "tsuru/atlys/camera.h"
#include "tsuru/graphics/shader.h"
#include "tsuru/graphics/vbo.h"

namespace Atlys {

class Renderer {
public:
    enum LayerID {
        LayerID_Map = 0x9,
        LayerID_Actor = 0x7
    };

private:
    Renderer();
    ~Renderer() { }

    void init(Atlys::Camera* camera);
    void activate();

// Don't call anything below here

    void makeLayers();
    void bindDrawMethods();

    // Draw methods
    void drawLayerMap(const agl::lyr::RenderInfo& renderInfo);
    void drawLayerActors(const agl::lyr::RenderInfo& renderInfo);

    friend class Scene;

    ObjLayerRenderer layerRenderer;
    agl::lyr::DrawMethodImpl<Renderer> drawMethodMap;
    agl::lyr::DrawMethodImpl<Renderer> drawMethodActors;
    GTX nodeTex;
};

}
