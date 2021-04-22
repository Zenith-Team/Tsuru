#pragma once

#include "list.h"
#include "idisposer.h"
#include "string.h"
#include "resourcemgr.h"

namespace sead {

class Resource;

class Decompressor : public TListNode<Decompressor*>, public IDisposer {
public:
    Decompressor(const SafeString& name);
    virtual ~Decompressor();

    virtual u8* tryDecompFromDevice(const ResourceMgr::LoadArg& loadArg, Resource* resource, u32* outSize, u32* outAllocSize, bool* outAllocated) = 0;

    FixedSafeString<32> mExt;
};

class SZSDecompressor : public Decompressor {
public:
    enum Step {
        cStepNormal = 0,
        cStepShort = 1,
        cStepLong = 2,
    };

    struct DecompContext {
        DecompContext();
        DecompContext(void* dst);

        void initialize(void* dst);

        u8* destp;
        s32 destCount;
        s32 forceDestCount;
        u8 flagMask;
        u8 flags;
        u8 packHigh;
        Step step;
        u16 lzOffset;
        u8 headerSize;
    };

public:
    SZSDecompressor(u32 workSize, u8* workBuffer);
    virtual ~SZSDecompressor();

    virtual u8* tryDecompFromDevice(const ResourceMgr::LoadArg& loadArg, Resource* resource, u32* outSize, u32* outAllocSize, bool* outAllocated);

    static u32 getDecompAlignment(const void* src);
    static u32 getDecompSize(const void* src);
    static s32 readHeader_(DecompContext* context, const u8* src, u32 srcSize);
    static s32 streamDecomp(DecompContext* context, const void* src, u32 srcSize);
    static s32 decomp(void* dst, u32 dstSize, const void* src, u32 srcSize);

    u32 mWorkSize;
    u8* mWorkBuffer;
};

}
