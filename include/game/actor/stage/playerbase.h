#pragma once

#include <game/actor/stage/stageactor.h>
#include <game/playerinput.h>

// TODO: finish this

class PlayerBase : public StageActor {
public:
    u8 _27C[0x2A8 - 0x27C];
    PlayerInput mInput;
};
