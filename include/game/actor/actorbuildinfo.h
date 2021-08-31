#pragma once

#include <types.h>
#include <game/profile/profile.h>

struct ActorBuildInfo {
    u32 mSettings1;      // _0
    u32 mSettings2;      // _4
    u32 mParentID;       // _8
    Profile* mProfile;   // _C
    Vec3f mPosition;     // _10
    u32 mRotation;       // _1C
    u8 mLayer;           // _20
    u8 mEventID1;        // _21
    u8 mEventID2;        // _22
    u8 _23;              // _23
    u8 mMovementID;      // _24
    u8 mLinkID;          // _25
    u8 mInitStateFlag;   // _26
    u8 _27;              // _27 Padding?
    u8* _28;             // _28
};
