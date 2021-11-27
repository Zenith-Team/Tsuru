#pragma once

#include "texturedata.h"

namespace agl {

class TextureDataInitializerGTX
{
public:
    static void initialize(agl::TextureData* textureData, void* pFile, u32 imageIdx);
};

}
