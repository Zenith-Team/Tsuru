#pragma once

#include "game/actor/stage/playerbase.h"

// TODO: finish this

class Player : public PlayerBase { // Size: 0x34D8
public:
    enum DamageType { //? This may or may not be part of PlayerBase instead
                      // TODO: Figure out all these types
        DamageType_SingleHit,
        DamageType_SingleHit_2,
        DamageType_SingleHitBounce,
        DamageType_SingleHit_3,
        DamageType_Bounce,
        DamageType_Bounce_2,
        DamageType_Unk1,
        DamageType_Unk2,
        DamageType_Unk3,
        DamageType_LavaNoInstaKill,
        DamageType_Lava,
        DamageType_Ice,
        DamageType_Ice_2,
        DamageType_Unk4,
        DamageType_Poison,
        DamageType_InstaKill,
        DamageType_InstaKill_2
    };

    enum TallType {
        TallType_Mini,
        TallType_Small,
        TallType_Normal
    };

public:
    void damage(u32, u32 damageType);   //! This is a pure virtual override
};
