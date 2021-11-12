#pragma once

/*
 * Tsuru
 * World Maps
 * 
 * Wish me luck. That's all I'm saying. --Luminyx
 * Started: 11/11/2021; 4:12pm
 */

// Bases
#include "sead/task.h"
#include "game/actor/actor.h"
#include "game/graphics/layer/renderobjlayer.h"

// Usage
#include "sead/camera.h"
#include "sead/viewport.h"
#include "sead/projection.h"
#include "agl/lyr/renderinfo.h"
#include "agl/lyr/drawmethod.h"
#include "agl/lyr/renderer.h"
#include "agl/texturedata.h"
#include "agl/rendertargetcolor.h"
#include "agl/renderbuffer.h"
#include "agl/shaderprogram.h"
#include "agl/shaderprogramarchive.h"
#include "tsuru/inputcontrollers.h"

class Atlys { // Holder class for all Atlys components
private:
    // Don't instanciate this class :)
    Atlys() { }

public:
    class Actor : public ::Actor { // Base class for all Atlys actors
    public:
        Actor(const ActorBuildInfo* buildInfo)
            : ::Actor(buildInfo)
            , position(0.0f)
            , rotation(0.0f)
            , layer(0)
        { }
    
        Vec3f position;
        Vec3f rotation;
        u8 layer;
    };

    class Camera : public Atlys::Actor {
    public:
        Camera(const ActorBuildInfo* buildInfo);

        static ::Actor* build(const ActorBuildInfo* buildInfo);

        u32 onExecute() override;

        sead::Viewport viewport;
        sead::OrthoCamera camera;
        sead::OrthoProjection projection;
    };

public:
    class Scene : public sead::CalculateTask { // Main map scene
        SEAD_RTTI_OVERRIDE_IMPL(Scene, sead::CalculateTask)
        SEAD_SINGLETON_TASK(Scene)

    public:
        enum LayerID {
            LayerID_Map = 0x7,
            LayerID_Actors = 0x9
        };

    private:
        class RenderLayer : public RenderObjLayer {
            SEAD_RTTI_OVERRIDE_IMPL(RenderLayer, ObjLayer)
        
        private:
            inline RenderLayer()
                : RenderObjLayer()
            { }

            friend class agl::lyr::Renderer;
        };

        class Renderer {
        private:
            Renderer();
            ~Renderer();

        public:
            void init();

            friend class Scene;

            agl::TextureData backgroundTextureData;
            agl::RenderTargetColor backgroundTargetColor;
            agl::RenderBuffer backgroundRenderBuffer;
        };
    
    public:
        Scene(const sead::TaskConstructArg& arg);
        virtual ~Scene() { }

        static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

        void prepare() override;
        void enter() override;
        void calc() override;

        void drawLayerMap(const agl::lyr::RenderInfo& renderInfo);
        void drawLayerActors(const agl::lyr::RenderInfo& renderInfo);

        agl::lyr::DrawMethod drawMethodMap;
        agl::lyr::DrawMethod drawMethodActors;
        InputControllers controllers;
        Atlys::Camera* camera;
        Renderer renderer;
    };
};
