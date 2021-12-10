#include "tsuru/atlys/camera.h"
#include "tsuru/atlys/scene.h"

const Profile AtlysCameraProfile(&Atlys::Camera::build, ProfileID::AtlysCamera);

Atlys::Camera::Camera(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
    , camera()
    , projection(0.01f, 1000.0f, agl::lyr::Renderer::instance()->layers[Atlys::Renderer::LayerID_Map]->scissor)
{ }

Actor* Atlys::Camera::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Camera(buildInfo);
}

u32 Atlys::Camera::onCreate() {
    return 1;
}

u32 Atlys::Camera::onExecute() {
    return 1;
}

u32 Atlys::Camera::onDraw() {
    return 1;
}
