#pragma once

#include <nw/eft/heap.h>
#include <dynlibs/os/functions.h>

#ifdef __cplusplus
extern "C" {
#endif

void __DCBZ(void*, int);
#define __dcbz __DCBZ

#ifdef __cplusplus
}
#endif

namespace nw { namespace eft{

struct TemporaryBuffer { // Size: 0x18
    inline void Initialize(Heap* heap, u32 size) {
        this->mCurrentBufferIdx = 0;
        this->mBufferSize = size;
        this->mBufferUsedSize = 0;
        this->mBufferFlushedSize = 0;
        this->mBuffer[0] = heap->Alloc(mBufferSize, 0x100);
        this->mBuffer[1] = heap->Alloc(mBufferSize, 0x100);
    }

    inline void Swap() {
        this->mCurrentBufferIdx = !this->mCurrentBufferIdx;
        this->mBufferUsedSize = 0;
        this->mBufferFlushedSize = 0;
    }

    inline void* Alloc(u32 size) {
        if (size == 0)
            return NULL;

        u32 sizeAligned = (size & ~0xFFU) + 0x100;
        if (this->mBufferUsedSize + sizeAligned > this->mBufferSize)
            return NULL;

        u8* ret = static_cast<u8*>(mBuffer[mCurrentBufferIdx]) + mBufferUsedSize;
        mBufferUsedSize += sizeAligned;

        // DCZeroRange(ret, sizeAligned)
        for (u32 i = 0; i < sizeAligned >> 8; i++) {
            u32 block0 = i * 0x100 + 0x00;
            u32 block1 = i * 0x100 + 0x20;
            u32 block2 = i * 0x100 + 0x40;
            u32 block3 = i * 0x100 + 0x60;
            u32 block4 = i * 0x100 + 0x80;
            u32 block5 = i * 0x100 + 0xA0;
            u32 block6 = i * 0x100 + 0xC0;
            u32 block7 = i * 0x100 + 0xE0;

            __dcbz(ret, block0);
            __dcbz(ret, block1);
            __dcbz(ret, block2);
            __dcbz(ret, block3);
            __dcbz(ret, block4);
            __dcbz(ret, block5);
            __dcbz(ret, block6);
            __dcbz(ret, block7);
        }

        return ret;
    }

    inline void FlushCache() {
        if (this->mBufferFlushedSize != this->mBufferUsedSize) {
            DCFlushRange(static_cast<u8*>(this->mBuffer[mCurrentBufferIdx]) + this->mBufferFlushedSize, this->mBufferUsedSize - this->mBufferFlushedSize);
            this->mBufferFlushedSize = this->mBufferUsedSize;
        }
    }

    u32 mCurrentBufferIdx;
    u32 mBufferSize;
    u32 mBufferUsedSize;
    u32 mBufferFlushedSize;
    void* mBuffer[2];
};

static_assert(sizeof(TemporaryBuffer) == 0x18, "TemporaryBuffer size mismatch");

} }
