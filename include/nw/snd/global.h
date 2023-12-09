#pragma once

#include "types.h"

namespace nw { namespace snd {

enum WaveType {
    WaveType_NwWav,
    WaveType_DspAdpcm,
    WaveType_Invalid = -1
};

} }
