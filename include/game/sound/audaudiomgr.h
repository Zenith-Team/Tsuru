#pragma once

#include "nw/snd.h"

class AudFxSocket;

class AudAudioMgr {
public:
    AudFxSocket* getFxSocket();
};
