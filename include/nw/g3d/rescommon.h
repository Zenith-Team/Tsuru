#pragma once

#include "types.h"

namespace nw { namespace g3d { namespace res {

struct BinaryFileHeader {
    u8  signature[4];  // 0
    u8  version[4];    // 4
    u16 byteOrder;     // 8
    u16 headerSize;    // A
    u32 fileSize;      // C
};

} } }
