#pragma once

#include <types.h>
#include <game/profile/profile.h>

struct ActorBuildInfo {
    union { u32 mSettings1;
        struct {
            u32 nybble12 : 4;
            u32 nybble11 : 4;
            u32 nybble10 : 4;
            u32 nybble9  : 4;
            u32 nybble8  : 4;
            u32 nybble7  : 4;
            u32 nybble6  : 4;
            u32 nybble5  : 4;
        };
    };
    union { u32 mSettings2;
        struct {
            u32 nybble20 : 4;
            u32 nybble19 : 4;
            u32 nybble18 : 4;
            u32 nybble17 : 4;
            u32 nybble16 : 4;
            u32 nybble15 : 4;
            u32 nybble14 : 4;
            u32 nybble13 : 4;
        };
    };
    u32 mParentID;          // _8
    Profile* mProfile;      // _C
    Vec3f mPosition;        // _10
    u32 mRotation;          // _1C
    u8 mLayer;              // _20
    u8 mEventID1;           // _21
    u8 mEventID2;           // _22
    u8 _23;                 // _23
    u8 mMovementID;         // _24
    u8 mLinkID;             // _25
    u8 mInitialStateFlag;   // _26
    u8 _27;                 // _27 //? Maybe padding
    u8* _28;                // _28
};
