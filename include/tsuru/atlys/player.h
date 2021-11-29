#pragma once

#include "log.h"
#include "tsuru/atlys/actor.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "tsuru/gtx.h"
#include "game/states.h"

namespace Atlys {

class Player : public Atlys::Actor {
    SEAD_RTTI_OVERRIDE_IMPL(Player, Atlys::Actor)

public:
    Player(const ActorBuildInfo* buildInfo);
    virtual ~Player() { }

    static ::Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    MultiStateWrapper<Atlys::Player> states;
    ModelWrapper* model;
    GTX tex; //! Temp
};

}
