#pragma once

#include "types.h"

namespace sead {

class Endian {
public:
    enum EndianType {
        EndianType_Big    = 0,
        EndianType_Little = 1
    };

    static inline EndianType markToEndian(u16 bom) {
        u8* bom_ = reinterpret_cast<u8*>(&bom);
        if (*bom_ == 0xFF && *(bom_ + 1) == 0xFE)
            return EndianType_Little;
        else if (*bom_ == 0xFE && *(bom_ + 1) == 0xFF)
            return EndianType_Big;
        return EndianType_Little;
    }

    static inline EndianType getHostEndian() {
        return hostEndian;
    }

    static inline u32 toHost(EndianType from, u32 x) {
        return convFuncTable.conv32[from^hostEndian](x);
    }

private:
    struct ConvFuncTable {
        typedef u8 (*CONV8FUNC)(u8);
        typedef u16 (*CONV16FUNC)(u16);
        typedef u32 (*CONV32FUNC)(u32);
        typedef u64 (*CONV64FUNC)(u64);

        CONV8FUNC conv8[2];
        CONV16FUNC conv16[2];
        CONV32FUNC conv32[2];
        CONV64FUNC conv64[2];
    };

    static const EndianType hostEndian;
    static const ConvFuncTable convFuncTable;
};

}
