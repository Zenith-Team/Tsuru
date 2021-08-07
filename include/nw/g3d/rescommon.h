#pragma once

#include <types.h>

namespace nw { namespace g3d { namespace res {

struct BinaryFileHeader {
    u8 mSignature[4];   // _0
    u8 mVersion[4];     // _4
    u16 mByteOrder;     // _8
    u16 mHeaderSize;    // _A
    u32 mFileSize;      // _C
};

} } }
