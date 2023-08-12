#pragma once

#include "types.h"

namespace nw { namespace snd {

// BFRES class
class SoundArchive {
public:
    enum SoundType {
        SoundType_Invalid = 0,

        SoundType_Seq,
        SoundType_Strm,
        SoundType_Wave
    };

public:
    const char* GetItemLabel(u32 id) const;
    u32 GetItemID(const char* label) const;
};

} }
