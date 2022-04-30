#pragma once

#include "types.h"
#include "game/profile/profile.h"

struct ActorBuildInfo {
    u32 settings1;          // 0
    u32 settings2;          // 4
    u32 parentID;           // 8
    Profile* profile;       // C
    Vec3f position;         // 10
    u32 rotation;           // 1C
    u8 layer;               // 20
    u8 eventID2;            // 21
    u8 eventID1;            // 22
    u8 _23;                 // 23
    u8 movementID;          // 24
    u8 linkID;              // 25
    u8 initialStateFlag;    // 26
    u8 _27;                 // 27 //? Maybe padding
    u8* _28;                // 28
};
