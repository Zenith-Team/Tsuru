#pragma once

#include <types.h>

namespace nw { namespace snd {

class SoundHandle;

class SoundStartable {
public:
    struct StartInfo;

public:
    virtual ~SoundStartable();
    virtual u32 detailSetupSound(SoundHandle* handle, u32 soundID, bool holdFlag, const StartInfo* startInfo) = 0;
    virtual u32 detailGetItemID(const char* string) = 0;
};

} }
