#include "tsuru/atlys/camera.h"
#include "tsuru/atlys/scene.h"
#include "cafe/math/mtx.h"
#include "math/functions.h"

const Profile AtlysCameraProfile(&Atlys::Camera::build, ProfileID::AtlysCamera);

Atlys::Camera::Camera(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
{
    ASM_MTXScale(&this->scaleMtx, 1.0f, 1.0f, 1.0f);

    this->camera.pos = Vec3f(0.0f, 0.0f, 30.0f);
}

Actor* Atlys::Camera::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Camera(buildInfo);
}

u32 Atlys::Camera::onCreate() {
    this->projection.set(0.001f, 1000000.0f, degToRad(75), 1280.0f / 720.0f);

    return 1;
}

u32 Atlys::Camera::onExecute() {
    this->position = Atlys::Scene::instance()->map->findNodeByID(0)->position;
    this->position.z += 256.0f;

    this->camera.at = Atlys::Scene::instance()->player->position;
    this->camera.pos = this->position;

    this->camera.doUpdateMatrix(&this->camera.matrix);

    return 1;
}

u32 Atlys::Camera::onDraw() {
    return 1;
}
