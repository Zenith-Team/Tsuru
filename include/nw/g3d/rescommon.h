#pragma once

#include <types.h>

namespace nw { namespace g3d { namespace res {

struct BinaryFileHeader {
    u8  signature[4];  // _0
    u8  version[4];    // _4
    u16 byteOrder;     // _8
    u16 headerSize;    // _A
    u32 fileSize;      // _C
};

} } }
