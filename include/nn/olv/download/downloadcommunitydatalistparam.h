#pragma once

#include <nn/types.h>

namespace nn { namespace olv {

class DownloadCommunityDataListParam {
public:
    DownloadCommunityDataListParam();

    Result SetCommunityDataMaxNum(const u32 communityDataMaxNum);
    Result SetFlags(const u32 flags);
};

} }
