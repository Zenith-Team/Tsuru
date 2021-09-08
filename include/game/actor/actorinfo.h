#pragma once

#include <types.h>

struct ActorInfo {
    enum Flags {
        FlagIgnoreSpawnRange = 0x002,
        FlagUnknown          = 0x008,
        FlagGrouped          = 0x010,
        FlagUnknown2         = 0x100
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
