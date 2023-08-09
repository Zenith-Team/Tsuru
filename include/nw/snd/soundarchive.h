#pragma once

#include "types.h"

namespace nw { namespace snd {

// BFRES class
class SoundArchive {
public:
    const char* GetItemLabel(u32 id) const;
    u32 GetItemID(const char* label) const;
};

} }
