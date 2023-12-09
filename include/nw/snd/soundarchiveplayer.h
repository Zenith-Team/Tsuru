#pragma once

#include "nw/snd/soundstartable.h"

namespace nw { namespace snd {

class SoundArchivePlayer : public SoundStartable {
public:
    SoundArchivePlayer();
    virtual ~SoundArchivePlayer();

    u32 detail_SetupSound(SoundHandle* handle, u32 soundID, bool holdFlag, const StartInfo* startInfo) override;
    u32 detail_GetItemID(const char* string) override;
    
    SoundArchive* soundArchive;
    u8 _8[0xC4 - 0x8];
};

static_assert(sizeof(SoundArchivePlayer) == 0xC4, "nw::snd::SoundArchivePlayer size mismatch");

} }
