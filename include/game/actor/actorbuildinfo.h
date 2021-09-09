#pragma once

#include <types.h>
#include <game/profile/profile.h>

struct ActorBuildInfo {
    union { u32 settings1;      // _0
        struct {                // _0
            u32 nybble12 : 4;   // _0
            u32 nybble11 : 4;   // _0
            u32 nybble10 : 4;   // _0
            u32 nybble9  : 4;   // _0
            u32 nybble8  : 4;   // _0
            u32 nybble7  : 4;   // _0
            u32 nybble6  : 4;   // _0
            u32 nybble5  : 4;   // _0
        };                      // _0
    };                          // _0
    union { u32 settings2;      // _4
        struct {                // _4
            u32 nybble20 : 4;   // _4
            u32 nybble19 : 4;   // _4
            u32 nybble18 : 4;   // _4
            u32 nybble17 : 4;   // _4
            u32 nybble16 : 4;   // _4
            u32 nybble15 : 4;   // _4
            u32 nybble14 : 4;   // _4
            u32 nybble13 : 4;   // _4
        };                      // _4
    };                          // _4
    u32 parentID;               // _8
    Profile* profile;           // _C
    Vec3f position;             // _10
    u32 rotation;               // _1C
    u8 layer;                   // _20
    u8 eventID1;                // _21
    u8 eventID2;                // _22
    u8 _23;                     // _23
    u8 movementID;              // _24
    u8 linkID;                  // _25
    u8 initialStateFlag;        // _26
    u8 _27;                     // _27 //? Maybe padding
    u8* _28;                    // _28
};
