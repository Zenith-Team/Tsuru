#pragma once

#include "nw/snd/soundstartable.h"

namespace nw { namespace snd {

namespace internal {

class BasicSound {
public:
    struct AmbientInfo { };
};

}

class SoundActor : public SoundStartable {
public:
    virtual ~SoundActor();

    virtual u32 SetupSound(SoundHandle* handle, u32 soundID, const SoundStartable::StartInfo* startInfo, void* setupArg);
    virtual u32 detail_SetupSoundWithAmbientInfo(SoundHandle* handle, u32 soundID, const SoundStartable::StartInfo* startInfo, internal::BasicSound::AmbientInfo* ambientInfo, void* setupArg); // deleted

    void* _4;
    u8 _8[0x40];
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    f32 _58;
    f32 _5C;
    bool isInitialized;
    bool isFinalized;
};

} }
