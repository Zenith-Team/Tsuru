#pragma once

#include "types.h"

namespace nw { namespace snd {

class SoundHandle;

class SoundStartable {
public:
    struct StartInfo;

public:
    virtual ~SoundStartable();
    virtual u32 detail_SetupSound(SoundHandle* handle, u32 soundId, bool holdFlag, const StartInfo* startInfo) = 0;
    virtual u32 detail_GetItemId(const char* string) = 0;
};

} }
