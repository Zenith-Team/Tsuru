#pragma once

#include "game/actor/actor.h"
#include "game/graphics/model/model.h"

namespace Atlys {

class Actor : public ::Actor {
    SEAD_RTTI_OVERRIDE_IMPL(Actor, ::Actor)

public:
    Actor(const ActorBuildInfo* buildInfo)
        : ::Actor(buildInfo)
        , position(0.0f)
        , rotation(0)
        , scale(1.0f)
        , model(nullptr)
    { }

    virtual ~Actor() {
        if (this->model)
            delete this->model;

        this->model = nullptr;
    }

    void updateModel() {
        if (!this->model)
            return;

        Mtx34 mtx;
        mtx.makeIdentity();
        mtx.rotateAndTranslate(this->rotation, this->position);
        this->model->setMtx(mtx);
        this->model->setScale(this->scale);
        this->model->updateModel();
    }

    Vec3f position;
    Vec3u rotation;
    Vec3f scale;
    ModelWrapper* model;
};

}
