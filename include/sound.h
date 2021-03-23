#pragma once

#include "nw/snd.h"


class AudioFx {
public:
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam& getDelayParam();
};

class SoundSystemBase {
public:
    AudioFx* getAudioFx();
};

class SoundSystem : public SoundSystemBase {
public:
    static SoundSystem* instance;
};
