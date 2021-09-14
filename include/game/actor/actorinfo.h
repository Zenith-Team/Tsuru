#pragma once

#include <types.h>

struct ActorInfo {
    enum Flags {
        Flag_IgnoreSpawnRange = 2,
        Flag_Unknown          = 8,
        Flag_Grouped          = 16,
        Flag_Unknown2         = 256
    };

    static ActorInfo sDefault;

    Vec2i spawnOffset;          // _0
    Vec2i spawnRangeOffset;     // _8
    Vec2i spawnRangeSize;       // _10
    u16 _18;                    // _18
    u16 _1A;                    // _1A
    u16 _1C;                    // _1C
    u16 _1E;                    // _1E
    u16 flags;                  // _20
};
