#pragma once

#include "agl/lyr/renderinfo.h"
#include "game/graphics/rendermgr.h"
#include "agl/lyr/drawmethod.h"

namespace crt {

    class Camera;

    class Renderer {
    private:
        friend class Scene;
    
        Renderer();

        void init(Camera* cam);
        void start();
        
        void drawLayerActors(const agl::lyr::RenderInfo& renderInfo);
    
        RenderMgr renderer;
        agl::lyr::DrawMethodImpl<Renderer> drawMethod;
    };

}
