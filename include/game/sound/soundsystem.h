#pragma once

#include <sead.h>
#include <game/sound/audiofx.h>

class SoundSystemBase {
public:
    AudioFx* getAudioFx();
};

class SoundSystem : public SoundSystemBase {
    SEAD_SINGLETON_DISPOSER(SoundSystem)

public:
    nw::snd::SoundArchive* getSoundArchive();

    inline const char* getItemLabel(u32 id) {
        return getSoundArchive()->GetItemLabel(id);
    }

    inline u32 getItemID(const char* label) {
        return getSoundArchive()->GetItemID(label);
    }
};
