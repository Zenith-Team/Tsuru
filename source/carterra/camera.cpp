#include "tsuru/carterra/camera.h"
#include "tsuru/carterra/scene.h"
#include "tsuru/carterra/map.h"
#include "tsuru/carterra/player.h"
#include "log.h"
#include "imgui/imgui.h"

static const Vec3f cameraOffset(0.0f, 120.0f, 200.0f);

namespace crt {
    REGISTER_PROFILE(Camera, ProfileID::CarterraCamera);
}

crt::Camera::Camera(const ActorBuildInfo* buildInfo)
    : crt::MapActor(buildInfo)
    , camera()
    , projection(10.0f, 1000.0f, 0.27f, 1.777778f)
{
    this->camera.pos = crt::Scene::instance()->player->position + cameraOffset;
    this->camera.at = crt::Scene::instance()->player->position;
}

u32 crt::Camera::onExecute() {
    this->targetPos = crt::Scene::instance()->player->position + cameraOffset;
    this->targetAt = crt::Scene::instance()->player->position;

    Vec3f targetDelta = this->targetPos - this->camera.pos; targetDelta.normalize();
    Vec3f targetAtDelta = this->targetAt - this->camera.at; targetAtDelta.normalize();

    if (this->camera.pos.distanceTo(this->targetPos) < 0.15f) {
        targetDelta = Vec3f(0.0f, 0.0f, 0.0f);
    }

    if (this->camera.at.distanceTo(this->targetAt) < 0.15f) {
        targetAtDelta = Vec3f(0.0f, 0.0f, 0.0f);
    }

    f32 speed = this->camera.pos.distanceTo(this->targetPos) / 8.0f;
    speed = speed < 0.2f ? 0.2f : speed;
    speed = speed > 0.8f ? 0.8f : speed;

    this->camera.pos += targetDelta * speed;
    this->camera.at += targetAtDelta * speed;

    this->camera.doUpdateMatrix(&this->camera.matrix);

    return 1;
}
