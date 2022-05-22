#pragma once

#include "nn/types.h"
#include "types.h"

namespace nn { namespace olv {

class UploadPostDataByPostAppParam {
public:
    UploadPostDataByPostAppParam();

    Result SetBodyTextMaxLength(const u32 bodyTextMaxLength);
};

} }
