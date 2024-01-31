#pragma once

#include "nw/snd/basicsound.h"

namespace nw { namespace snd {

namespace internal {

class SequenceSound : public BasicSound {
public:
    bool ReadVariable(s32 varNo, s16* var);
    void WriteVariable(s32 varNo, s16 var);
};

} } }
