#pragma once

#include <nn/types.h>

namespace nn { namespace olv {

class DownloadPostDataListParam {
public:
    DownloadPostDataListParam();

    Result SetCommunityId(const u32 communityID);
    Result SetFlags(const u32 flags);
    Result SetLanguageId(const u8 languageID);
    Result SetPostDataMaxNum(const u32 postDataMaxNum);
    Result SetSearchKey(const wchar_t* searchKey, const u8 index);
};

} }
