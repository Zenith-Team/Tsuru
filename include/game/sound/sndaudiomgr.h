#pragma once

#include "game/sound/audaudiomgr.h"
#include "heap/seadDisposer.h"
#include "nw/snd/soundhandle.h"
#include "nw/snd/snd_SoundArchive.h"

class SndAudioMgr : public AudAudioMgr {
    SEAD_SINGLETON_DISPOSER(SndAudioMgr);

public:
    class InitializeArg {
    public:
        InitializeArg();

        sead::Heap* heap;
        u8 _4[0x30 - 0x4];
    };

    static_assert(sizeof(InitializeArg) == 0x30, "SndAudioMgr::InitializeArg size mismatch");

public:
    SndAudioMgr();
    ~SndAudioMgr();

    virtual void initialize(const InitializeArg& arg);
    virtual void calc();
    virtual bool startSound(nw::snd::SoundHandle* handle, u32 soundID); // deleted
    virtual bool startSound(nw::snd::SoundHandle* handle, const char* soundName);
    virtual bool holdSound(nw::snd::SoundHandle* handle, u32 soundID); // deleted
    virtual bool holdSound(nw::snd::SoundHandle* handle, const char* soundName);
    virtual bool prepareSound(nw::snd::SoundHandle* handle, u32 soundID);
    virtual bool prepareSound(nw::snd::SoundHandle* handle, const char* soundName);
    // ...

    AudAudioPlayer* getAudioPlayer() const;
    nw::snd::SoundArchive* getSoundArchive() const;

    const char* getSoundName(u32 id) const;
    u32 getSoundID(const char* label) const;

    nw::snd::SoundArchive::SoundType getSoundType(const char* label) const;

    bool isSndPlaying(const char* label);

    u8 getBeatTrigger() const;

    bool bgmStartFlag;
    bool streamStartFlag;
    bool starBgmStartFlag;
    bool streamWithControlStartPreparedFlag;
    nw::snd::SoundHandle startSystemSeSoundHandle;
    nw::snd::SoundHandle holdSystemSeSoundHandle;
    nw::snd::SoundHandle holdSystemSeVSoundHandle;
    nw::snd::SoundHandle fanfareSoundHandle;
    nw::snd::SoundHandle bgmSoundHandle;
    nw::snd::SoundHandle starBgmSoundHandle;
    nw::snd::SoundHandle controlBgmSoundHandle;
    nw::snd::SoundHandle streamSoundHandle;
    nw::snd::SoundHandle startSystemSeDrcSoundHandle;
    nw::snd::SoundHandle starDrcSoundHandle;
    u8 _54[0x7C - 0x54];
    u8 currentBeat;
    u8 _7D[0x3D0 - 0x7D];
};

static_assert(sizeof(SndAudioMgr) == 0x3D4, "SndAudioMgr size mismatch");
