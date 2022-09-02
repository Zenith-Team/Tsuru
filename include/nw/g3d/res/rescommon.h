#pragma once

#include "types.h"

namespace nw { namespace g3d { namespace res {

typedef s32 Offset;
typedef Offset BinString;

struct BinaryFileHeader {
    union {
        u8 magic[4];
        u32 magicWord;
    };
    union {
        u8 version[4];
        u32 versionWord;
    };
    u16 byteOrder;
    u16 headerSize;
    u32 fileSize;
};

union BinaryBlockHeader {
    u8 magic[4];
    u32 magicWord;
};

struct ResExternalFileData {
    s32 offset;
    u32 size;
};

class ResExternalFile;


class BinPtr {
public:
    union {
        u32 addr;
        void* ptr;
    };
};

} } }
