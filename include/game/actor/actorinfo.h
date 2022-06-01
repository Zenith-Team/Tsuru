#pragma once

#include "types.h"

struct ActorInfo {
    enum Flags {
        Flag_IgnoreSpawnRange = 1 << 1,
        Flag_Unknown1         = 1 << 3,
        Flag_Grouped          = 1 << 4,
        Flag_Unknown2         = 1 << 8
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
