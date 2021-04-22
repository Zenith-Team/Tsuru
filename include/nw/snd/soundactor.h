#pragma once

#include "soundstartable.h"

namespace nw { namespace snd {

namespace internal {

class BasicSound {
public:
    struct AmbientInfo { };
};

} // namespace nw::snd::internal

class SoundActor : public SoundStartable {
public:
    virtual ~SoundActor();

    u32 detail_SetupSound(SoundHandle* handle, u32 soundId, bool holdFlag, const SoundStartable::StartInfo* startInfo) override;
    u32 detail_GetItemId(const char* string) override;

    virtual u32 SetupSound(SoundHandle* handle, u32 soundId, const SoundStartable::StartInfo* startInfo, void* setupArg);
    virtual u32 detail_SetupSoundWithAmbientInfo(SoundHandle* handle, u32 soundId, const SoundStartable::StartInfo* startInfo, internal::BasicSound::AmbientInfo* ambientInfo, void* setupArg);    // deleted

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
