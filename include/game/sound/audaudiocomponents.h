#pragma once

#include "sead/heap.h"
#include "sead/audiormtspeakermgr.h"

class AudAudioSystem;
class AudAudioPlayer;
class AudAudioResourceLoader;
class Aud3DSoundMgr;
class AudFxSocket;

class AudAudioComponents {
public:
    AudAudioComponents(sead::Heap* heap);
    ~AudAudioComponents();

    AudAudioSystem* getAudioSystem() const;
    AudAudioPlayer* getAudioPlayer() const;
    AudAudioResourceLoader* getResourceLoader() const;
    Aud3DSoundMgr* get3DSoundMgr() const;
    AudFxSocket* getFxSocket() const;
    //void* get1C() const;

    AudAudioSystem* audioSystem;
    AudAudioPlayer* audioPlayer;
    AudAudioResourceLoader* resourceLoader;
    Aud3DSoundMgr* soundMgr3D;
    void* _10;
    AudFxSocket* fxSocket;
    void* _18;
    void* _1C;
    sead::AudioRmtSpeakerMgrCafe* rmtSpeakerMgr;
};

static_assert(sizeof(AudAudioComponents) == 0x24, "AudAudioComponents size mismatch");
