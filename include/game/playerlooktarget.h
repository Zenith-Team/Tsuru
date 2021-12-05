#pragma once

#include "sead/idisposer.h"

class PlayerLookTarget : public sead::IDisposer { // Size: 0x2C
    PlayerLookTarget(u32* ownerID);
    virtual ~PlayerLookTarget();

    u32 ownerID;    // Actor ID of owner
    Vec2f _14;
    u32 _1C;
    u32 _20;
    u32 _24;
    u32 _28;
};

static_assert(sizeof(PlayerLookTarget) == 0x2C, "PlayerLookTarget size mismatch");
