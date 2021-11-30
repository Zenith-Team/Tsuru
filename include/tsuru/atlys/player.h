#pragma once

#include "log.h"
#include "tsuru/atlys/actor.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "tsuru/gtx.h"
#include "game/states.h"
#include "tsuru/atlys/map.h"
#include "game/direction.h"

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

private:
    void findTargetNode(Direction::DirectionType direction);
    void updateTargetRotation();

public:
    DECLARE_STATE(Player, Idle);
    DECLARE_STATE(Player, Walking);

    MultiStateWrapper<Atlys::Player> states;
    ModelWrapper* model;
    const Map::Node* currentNode;
    const Map::Node* targetNode;
    f32 walkingSpeed;
    f32 targetRotation;

    GTX tex; //! Temp
};

}
