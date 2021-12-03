#pragma once

#include <types.h>
#include <game/profile/profile.h>

struct ActorBuildInfo {
    union { u32 settings1;      // 0
        struct {                // 0
            u32 nybble12 : 4;   // 0
            u32 nybble11 : 4;   // 0
            u32 nybble10 : 4;   // 0
            u32 nybble9  : 4;   // 0
            u32 nybble8  : 4;   // 0
            u32 nybble7  : 4;   // 0
            u32 nybble6  : 4;   // 0
            u32 nybble5  : 4;   // 0
        };                      // 0
    };                          // 0
    union { u32 settings2;      // 4
        struct {                // 4
            u32 nybble20 : 4;   // 4
            u32 nybble19 : 4;   // 4
            u32 nybble18 : 4;   // 4
            u32 nybble17 : 4;   // 4
            u32 nybble16 : 4;   // 4
            u32 nybble15 : 4;   // 4
            u32 nybble14 : 4;   // 4
            u32 nybble13 : 4;   // 4
        };                      // 4
    };                          // 4
    u32 parentID;               // 8
    Profile* profile;           // C
    Vec3f position;             // 10
    u32 rotation;               // 1C
    u8 layer;                   // 20
    u8 eventID1;                // 21
    u8 eventID2;                // 22
    u8 _23;                     // 23
    u8 movementID;              // 24
    u8 linkID;                  // 25
    u8 initialStateFlag;        // 26
    u8 _27;                     // 27 //? Maybe padding
    u8* _28;                    // 28
};
