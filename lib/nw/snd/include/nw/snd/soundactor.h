#pragma once

#include "nw/snd/soundstartable.h"
#include "nw/snd/basicsound.h"
#include "nw/snd/externalsoundplayer.h"

namespace nw { namespace snd {

class SoundArchivePlayer;

class SoundActor : public SoundStartable {
public:
    SoundActor(SoundArchivePlayer& soundArchivePlayer);
    virtual ~SoundActor();

    StartResult detail_SetupSound(SoundHandle* handle, u32 soundID, bool holdFlag, const StartInfo* startInfo) override;
    u32 detail_GetItemID(const char* string) override;

    virtual u32 SetupSound(SoundHandle* handle, u32 soundID, const SoundStartable::StartInfo* startInfo, void* setupArg);
    virtual u32 detail_SetupSoundWithAmbientInfo(SoundHandle* handle, u32 soundID, const SoundStartable::StartInfo* startInfo, internal::BasicSound::AmbientInfo* ambientInfo, void* setupArg); // deleted

    SoundArchivePlayer* soundArchivePlayer;
    internal::ExternalSoundPlayer actorPlayer[4];
    internal::SoundActorParam actorParam;
    bool isInitialized;
    bool isFinalized;
};

static_assert(sizeof(SoundActor) == 0x64, "nw::snd::SoundActor size mismatch");

} }
