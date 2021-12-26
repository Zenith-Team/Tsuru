#include "tsuru/atlys/camera.h"
#include "tsuru/atlys/scene.h"
#include "math/functions.h"

const Profile AtlysCameraProfile(&Atlys::Camera::build, ProfileID::AtlysCamera);

Atlys::Camera::Camera(const ActorBuildInfo* buildInfo)
    : Atlys::Actor(buildInfo)
{
    this->camera.pos = Vec3f(0.0f, 0.0f, 30.0f);
}

Actor* Atlys::Camera::build(const ActorBuildInfo* buildInfo) {
    return new Atlys::Camera(buildInfo);
}

u32 Atlys::Camera::onCreate() {
    this->projection.setNearFarClip(0.001f, 100000.0f);
    this->projection.setTBLR(180.0f, -180.0f, -320.0f, 320.0f);

    return 1;
}

u32 Atlys::Camera::onExecute() {
    Vec3f playerPos(Atlys::Scene::instance()->player->position.x, 0.0f, Atlys::Scene::instance()->player->position.y);

    this->position = playerPos;
    this->camera.at = playerPos;

    this->position.z += 100.0f;
    this->position.y += 150.0f;

    this->camera.pos = this->position;
    this->camera.doUpdateMatrix(&this->camera.matrix);

    return 1;
}

u32 Atlys::Camera::onDraw() {
    return 1;
}
