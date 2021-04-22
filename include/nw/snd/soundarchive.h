#pragma once

#include "types.h"

namespace nw { namespace snd {

class SoundArchive {
public:
    const char* GetItemLabel(u32 id) const;
    u32 GetItemId(char const* label) const;
};

} }
