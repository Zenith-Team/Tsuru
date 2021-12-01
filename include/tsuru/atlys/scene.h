#pragma once

#include "sead/task.h"
#include "tsuru/atlys/renderer.h"
#include "tsuru/inputcontrollers.h"
#include "game/profile/profileid.h"
#include "tsuru/atlys/actor.h"
#include "tsuru/atlys/map.h"
#include "tsuru/atlys/player.h"
#include "game/states.h"
#include "tsuru/atlys/camera.h"

namespace Atlys {

class Scene : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE_IMPL(Scene, sead::CalculateTask)
    SEAD_SINGLETON_TASK(Scene)

public:
    Scene(const sead::TaskConstructArg& arg);
    virtual ~Scene();

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

    void prepare() override;
    void enter() override;
    void calc() override;

private:
    static inline Atlys::Actor* spawnSystemActor(ProfileID::ProfileIDType id);

    friend class Renderer;

    DECLARE_STATE(Scene, Active);
    DECLARE_STATE(Scene, Paused);

    MultiStateWrapper<Scene> states;
    Renderer renderer;

public:
    InputControllers controllers;
    InputControllers::ControllerID activeController;

    Map* map;
    Player* player;
    Camera* camera;
};

}
