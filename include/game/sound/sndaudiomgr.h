#pragma once

#include "game/sound/audaudiomgr.h"
#include "sead/idisposer.h"

class SndAudioMgr : public AudAudioMgr {
    SEAD_SINGLETON_DISPOSER(SndAudioMgr);

public:
    nw::snd::SoundArchive* getSoundArchive();

    inline const char* getItemLabel(u32 id) { return getSoundArchive()->GetItemLabel(id); }
    inline u32 getItemID(const char* label) { return getSoundArchive()->GetItemID(label); }
};
