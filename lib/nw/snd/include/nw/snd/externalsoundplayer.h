#pragma once

#include "nw/ut/ut_LinkList.h"

namespace nw { namespace snd {

namespace internal {

class ExternalSoundPlayer {
public:
    //typedef ut::LinkList<BasicSound, offsetof(BasicSound, extSoundPlayerPlayLink)> SoundList;
    typedef ut::internal::LinkListImpl SoundList; // is actually this ^

public:
    ExternalSoundPlayer();
    ~ExternalSoundPlayer();

    SoundList soundList;
    s32 playableCount;
};

static_assert(sizeof(ExternalSoundPlayer) == 0x10, "nw::snd::internal::ExternalSoundPlayer size mismatch");

} } }