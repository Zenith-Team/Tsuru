#pragma once

#include "types.h"

namespace nw { namespace snd {

// BFRES class
class SoundArchive {
public:
    enum SoundType {
        SoundType_Invalid = 0,

        SoundType_Seq = 1,
        SoundType_Strm = 2,
        SoundType_Wave = 3
    };

public:
    const char* GetItemLabel(u32 id) const;
    u32 GetItemID(const char* label) const;
};

} }
