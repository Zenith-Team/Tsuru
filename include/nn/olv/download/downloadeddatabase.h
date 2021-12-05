#pragma once

#include "ffl.h"
#include "nn/types.h"

namespace nn { namespace olv {

class DownloadedDataBase {
public:
    Result GetAppData(u8* appData, u32* appDataSize, const u32 appDataMaxSize) const;
    Result GetBodyMemo(u8* bodyMemo, u32* bodyMemoSize, const u32 bodyMemoMaxSize) const;
    Result GetBodyText(wchar_t* bodyText, const u32 bodyTextBufferLength) const;
    s8 GetFeeling() const;
    Result GetMiiData(FFL::StoreData* storeData) const;
};

} }
