#pragma once

#include "types.h"

inline void* AddOffset(void* ptr, size_t offset)
{
    return static_cast<char*>(ptr) + offset;
}

template <typename ResultT>
inline ResultT* AddOffset(void* ptr, size_t offset)
{
    return static_cast<ResultT*>(AddOffset(ptr, offset));
}

namespace nw { namespace g3d { namespace res {

class Offset
{
public:
    s32 offset;

    template<typename T>
    T* to_ptr() { return (offset == 0) ? NULL : AddOffset<T>(this, offset); }
};

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
