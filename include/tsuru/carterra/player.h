#pragma once

#include "tsuru/carterra/mapactor.h"
#include "tsuru/carterra/map.h"
#include "game/graphics/model/charactermodelmgr.h"
#include "game/states.h"

namespace crt {

    class Player : public MapActor {
        SEAD_RTTI_OVERRIDE_IMPL(Player, MapActor);

    public:
        Player(const ActorBuildInfo* buildInfo);
        virtual ~Player() { }

        u32 onCreate() override;
        u32 onExecute() override;
        u32 onDraw() override;

        PlayerModelMgr modelMario;
        MapData::Node* currentNode;
        MapData::Path* currentPath;
        MultiStateWrapper<crt::Player> states;
        f32 targetRotation;

        DECLARE_STATE(Player, Idle);
        DECLARE_STATE(Player, Walk);
        DECLARE_STATE(Player, EnterLevel);
        DECLARE_STATE(Player, ExitLevel);
    };

}
