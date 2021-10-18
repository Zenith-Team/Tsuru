#pragma once

#include <nn/types.h>

namespace nn { namespace olv {

class UploadParamBase {
public:
    ~UploadParamBase();

    Result SetAppData(const u8* appData, const u32 appDataSize);
    Result SetBodyText(const wchar_t* bodyText);
    Result SetSearchKey(const wchar_t* searchKey, const u8 index);
    Result SetTopicTag(const wchar_t* topicTag);
};

} }
