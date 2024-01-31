#pragma once

#include "game/actor/stage/enemy.h"

class CutsceneKamek : public Enemy {
    SEAD_RTTI_OVERRIDE_DECL(CutsceneKamek, Enemy);

public:
    DECLARE_STATE(CutsceneKamek, CutsceneKamekState1);
    DECLARE_STATE(CutsceneKamek, CutsceneKamekState2);
    DECLARE_STATE(CutsceneKamek, CutsceneKamekState3);
    DECLARE_STATE(CutsceneKamek, CutsceneKamekState4);
};
