#pragma once

#include "log.h"
#include "tsuru/atlys/actor.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "tsuru/graphics/gtx.h"
#include "game/states.h"
#include "tsuru/atlys/map.h"
#include "game/direction.h"

namespace Atlys {

class Player : public Atlys::Actor {
    SEAD_RTTI_OVERRIDE_IMPL(Player, Atlys::Actor)

public:
    Player(const ActorBuildInfo* buildInfo);
    virtual ~Player();

    static ::Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

private:
    // Sets the target node from the current node's connections based on the direction
    // @param direction The direction to search
    void findTargetNode(Direction::DirectionType direction);

    // Sets the target rotation based on the target node's position to make the player face towards it
    void updateTargetRotation();

public:
    DECLARE_STATE(Player, Idle);
    DECLARE_STATE(Player, Walking);

    MultiStateWrapper<Atlys::Player> states;
    const Map::Node* currentNode;
    const Map::Node* targetNode;
    f32 walkingSpeed;
    u32 targetRotation; // Y rotation in idx
    Direction::DirectionType direction;
};

}
