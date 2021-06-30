#pragma once

#include "types.h"

struct ChallengeMgrData {
    void* mDataPtr;         // 0
    u8 _4[0x1E18 - 0x4];    // 4
};

class ChallengeMgr {
public:
    u32 _0;                       // 0
    u32 _4;                       // 4
    u32 _8;                       // 8
    u32 _C;                       // C
    ChallengeMgrData mMgrData;    // 10
    u32 mChallenge;               // 1E28
    u8 mChallengeType;            // 1E2C
    u8 _1E2D;                     // 1E2D
    u32 _1E2E;                    // 1E2E
    u8 _1E32;                     // 1E32
    u8 _1E33;                     // 1E33
    u32 _1E34;                    // 1E34
    u32 mActorID;                 // 1E38
    u32 _1E3C;                    // 1E3C
    u32 _1E40;                    // 1E40
    u32 _1E44;                    // 1E44
    u32 mChallengeTime;           // 1E48
    u32 _1E4C;                    // 1E4C
    u8 _1E50;                     // 1E50
    u8 _1E51;                     // 1E51
    u8 _1E52;                     // 1E52
    u8 _1E53;                     // 1E53
    u8 _1E54;                     // 1E54
    u8 _1E55;                     // 1E55
    u8 _1E56;                     // 1E56
    u8 _1E57;                     // 1E57
    u8 _1E58;                     // 1E58
    u8 _1E59;                     // 1E59
    u8 _1E5A;                     // 1E5A
    u8 _1E5B;                     // 1E5B
    u8 _1E5C[0x1E84 - 0x1E5C];    // 1E5C
};
