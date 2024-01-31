#pragma once

#include "game/sound/audaudiocomponents.h"
#include "audio/seadAudioSettingParameter.h"

class AudAudioMgr {
public:
    AudAudioMgr();
    ~AudAudioMgr();

    void setupAudioSetting();

    AudAudioSystem* getAudioSystem() const;
    AudAudioPlayer* getAudioPlayer() const;
    AudAudioResourceLoader* getResourceLoader() const;
    AudFxSocket* getFxSocket() const;
    sead::AudioRmtSpeakerMgrCafe* getRmtSpeakerMgr() const;

    u8 _0[0x10 - 0x0];
    AudAudioComponents* audioComponents;
    sead::AudioSettingParameter* audioSetting;
};

static_assert(sizeof(AudAudioMgr) == 0x18, "AudAudioMgr size mismatch");
