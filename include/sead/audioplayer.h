#pragma once

#include "sead/runtimetypeinfo.h"
#include "nw/snd/soundarchiveplayer.h"

namespace sead {

class AudioPlayer {
    SEAD_RTTI_BASE(AudioPlayer);

public:
    virtual ~AudioPlayer();

    virtual void initialize();
    virtual void finalize();
    virtual void calc();
    virtual void vf34(); // deleted
    virtual void vf3C(); // deleted
    virtual void vf44(); // deleted
    virtual void vf4C(); // deleted
    virtual void vf54(); // deleted
    virtual const char* getSoundName(u32 itemID); // deleted
    virtual void vf64(); // deleted
};

static_assert(sizeof(AudioPlayer) == 0x4, "sead::AudioPlayer size mismatch");

class AudioPlayerCafe : public AudioPlayer, public nw::snd::SoundArchivePlayer {
    SEAD_RTTI_OVERRIDE(AudioPlayerCafe, AudioPlayer);

public:
    virtual ~AudioPlayerCafe();

    void initialize() override;
    void finalize() override;
    void calc() override;
    void vf34() override; // deleted
    void vf3C() override; // deleted
    void vf44() override; // deleted
    void vf4C() override; // deleted
    void vf54() override; // deleted
    const char* getSoundName(u32 itemID) override;
    void vf64() override; // deleted
    u32 detail_SetupSound(nw::snd::SoundHandle* handle, u32 soundID, bool holdFlag, const StartInfo* startInfo) override;

    u8 _C8[0x134 - 0xC8];
};

static_assert(sizeof(AudioPlayerCafe) == 0x134, "sead::AudioPlayerCafe size mismatch");

}
