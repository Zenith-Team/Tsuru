#pragma once

#include "nn/types.h"
#include "types.h"

namespace nn { namespace olv {

class DownloadedCommunityData {
public:
    Result GetAppData(u8* appData, u32* appDataSize, const u32 appDataMaxSize) const;
    u32 GetCommunityId() const;
};

} }
