#pragma once

#include "types.h"
#include "util/vec2i.h"

struct ActorInfo {
    enum Flags {
        FlagIgnoreSpawnRange = 0x002,
        FlagUnknown          = 0x008,
        FlagGrouped          = 0x010,
        FlagUnknown2         = 0x100
    };

    static ActorInfo Default;

    Vec2i spawnOffset;            // 0
    Vec2i spawnRangeOffset;       // 8
    Vec2i spawnRangeSize;         // 10
    u16 _18;                      // 18
    u16 _1A;                      // 1A
    u16 _1C;                      // 1C
    u16 _1E;                      // 1E
    u16 flags;                    // 20
};
