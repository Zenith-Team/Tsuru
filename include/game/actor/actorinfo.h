#pragma once

#include "types.h"
#include "math/seadVector.h"

struct ActorInfo {
    ENUM_CLASS(Flags,
        IgnoreSpawnRange = 1 << 1,
        Unknown1         = 1 << 3,
        Grouped          = 1 << 4,
        Unknown2         = 1 << 8
    );

    static ActorInfo sDefault;

    sead::Vector2i spawnOffset;         // 0
    sead::Vector2i spawnRangeOffset;    // 8
    sead::Vector2i spawnRangeSize;      // 10
    u16 _18;                            // 18
    u16 _1A;                            // 1A
    u16 _1C;                            // 1C
    u16 _1E;                            // 1E
    u16 flags;                          // 20
};
