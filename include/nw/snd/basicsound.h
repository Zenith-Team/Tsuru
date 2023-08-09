#pragma once

#include "types.h"

namespace nw { namespace snd {

namespace internal {

struct SoundActorParam {
    f32 volume;
    f32 pitch;
    f32 tvVolume;
    f32 tvPan;
    f32 drcVolume;
    f32 drcPan;
};

static_assert(sizeof(SoundActorParam) == 0x18, "nw::snd::internal::SoundActorParam size mismatch");

class BasicSound {
public:
    struct AmbientInfo { };
};

} } }
