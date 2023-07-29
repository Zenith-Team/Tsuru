#pragma once

#include "sead/idisposer.h"
#include "sead/tlist.h"
#include "sead/resourcemgr.h"

namespace sead {

class Decompressor : public TListNode<Decompressor*>, public IDisposer {
public:
    Decompressor(const SafeString& defaultExt)
        : TListNode<Decompressor*>(this)
        , IDisposer()
        , ext(defaultExt)
    { }

    virtual ~Decompressor() {
        if (ResourceMgr::instance() != nullptr)
            ResourceMgr::instance()->unregisterDecompressor(this);
    }

    virtual u8* tryDecompFromDevice(const ResourceMgr::LoadArg& arg, Resource* res, u32* outSize, u32* outBufferSize, bool* outNeedDelete) = 0;

    FixedSafeString<32> ext;
};

static_assert(sizeof(Decompressor) == 0x50, "sead::Decompressor size mismatch");

class SZSDecompressor : public Decompressor {
public:
    enum Step {
        Step_Normal = 0,
        Step_Short = 1,
        Step_Long = 2,
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

    static_assert(sizeof(DecompContext) == 0x18, "sead::SZSDecompressor::DecompContext size mismatch");

public:
    SZSDecompressor(u32 workSize, u8* workBuffer);
    virtual ~SZSDecompressor() { }

    u8* tryDecompFromDevice(const ResourceMgr::LoadArg& arg, Resource* res, u32* outSize, u32* outBufferSize, bool* outNeedDelete) override;

    static inline u32 getHeaderSize() { return 0x10; }
    void setWorkSize(u32 workSize);

    u32 workSize;
    u8* workBuffer;
};

static_assert(sizeof(SZSDecompressor) == 0x58, "sead::SZSDecompressor size mismatch");

}
