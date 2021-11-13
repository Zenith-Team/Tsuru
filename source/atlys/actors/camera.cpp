#include "tsuru/atlys.h"
#include "dynlibs/os/functions.h"

Atlys::Camera::Camera(const ActorBuildInfo* buildInfo) 
    : Atlys::Actor(buildInfo)
    , viewport(0.0f, 0.0f, 640.0f, 480.0f)
    , camera()
    , projection()
{ }

Actor* Atlys::Camera::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Camera(buildInfo);
}

u32 Atlys::Camera::onExecute() {
    this->camera.doUpdateMatrix(&this->camera.matrix);

    return 1;
}

const Profile AtlysCameraProfile(&Atlys::Camera::build, ProfileID::AtlysCamera);
