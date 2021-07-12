#pragma once

#include "sead.h"

namespace nw { namespace eft {

class System;

} }

class PtclMgr {
public:
    u8 getEmitterSetGroupID(s32 emitterSetID, u32 resourceID) const;

    static PtclMgr* instance;

    sead::IDisposer disposer;  // 0
    nw::eft::System* system;   // 10, sead::ptcl::PtclSystem*
    // ...
};
