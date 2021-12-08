#pragma once

#include "types.h"

struct ActorInfo {
    enum Flags {
        Flag_IgnoreSpawnRange = 2,
        Flag_Unknown          = 8,
        Flag_Grouped          = 16,
        Flag_Unknown2         = 256
    };

    static ActorInfo sDefault;

    Vec2i spawnOffset;          // 0
    Vec2i spawnRangeOffset;     // 8
    Vec2i spawnRangeSize;       // 10
    u16 _18;                    // 18
    u16 _1A;                    // 1A
    u16 _1C;                    // 1C
    u16 _1E;                    // 1E
    u16 flags;                  // 20
};
