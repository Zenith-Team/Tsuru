#pragma once

#include "types.h"

namespace nw { namespace g3d { namespace res {

struct BinaryFileHeader {
    u8 signature[4];
    u8 version[4];
    u16 byteOrder;
    u16 headerSize;
    u32 fileSize;
};

} } }
