#pragma once

#include "sead/audioplayer.h"

class AudAudioPlayer : public sead::AudioPlayerCafe {
    // Doesn't override RTTI bruh

public:
    AudAudioPlayer();
    virtual ~AudAudioPlayer();

    void initialize() override;
    void finalize() override;
    void calc() override;
};
