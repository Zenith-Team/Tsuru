#pragma once

#include "types.h"
#include "profile.h"

struct ActorBuildInfo {
    u32 settings1;                // 0
    u32 settings2;                // 4
    u32 parentId;                 // 8
    Profile* profile;             // C
    Vec3 position;                // 10
    u32 rotation;                 // 1C
    u8 layer;                     // 20
    u8 eventId1;                  // 21
    u8 eventId2;                  // 22
    u8 pad1;                      // 23
    u8 movementId;                // 24
    u8 linkId;                    // 25
    u8 initStateFlag;             // 26
    u8 pad2;                      // 27
    u8* _28;                      // 28
};
