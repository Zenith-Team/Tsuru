#pragma once

#include <types.h>
#include <game/profile/profile.h>

struct ActorBuildInfo {
    u32 settings1;          // _0
    u32 settings2;          // _4
    u32 parentID;           // _8
    Profile* profile;       // _C
    Vec3f position;         // _10
    u32 rotation;           // _1C
    u8 layer;               // _20
    u8 eventID1;            // _21
    u8 eventID2;            // _22
    u8 _23;                 // _23
    u8 movementID;          // _24
    u8 linkID;              // _25
    u8 initialStateFlag;    // _26
    u8 _27;                 // _27  Padding?
    u8* _28;                // _28
};
