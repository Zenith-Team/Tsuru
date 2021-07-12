#ifndef EFT_TEMPORARY_BUFFER_H_
#define EFT_TEMPORARY_BUFFER_H_

#include "nw/eft/heap.h"

#include "dynamic_libs/os_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

void __DCBZ(void *, int);
#define __dcbz __DCBZ

#ifdef __cplusplus
}
#endif

namespace nw { namespace eft {

struct TemporaryBuffer {
    inline void Initialize(Heap* heap, u32 size);
    inline void Swap();
    inline void* Alloc(u32 size);
    inline void FlushCache();

    u32 currentBufferIdx;
    u32 bufferSize;
    u32 bufferUsedSize;
    u32 bufferFlushedSize;
    void* buffer[2];
};
static_assert(sizeof(TemporaryBuffer) == 0x18, "TemporaryBuffer size mismatch");

void TemporaryBuffer::Initialize(Heap* heap, u32 size) {
    currentBufferIdx = 0;
    bufferSize = size;
    bufferUsedSize = 0;
    bufferFlushedSize = 0;
    buffer[0] = heap->Alloc(bufferSize, 0x100);
    buffer[1] = heap->Alloc(bufferSize, 0x100);
}

void TemporaryBuffer::Swap() {
    currentBufferIdx = !currentBufferIdx;
    bufferUsedSize = 0;
    bufferFlushedSize = 0;
}

void* TemporaryBuffer::Alloc(u32 size) {
    if (size == 0)
        return NULL;

    u32 sizeAligned = (size & ~0xFFU) + 0x100;
    if (bufferUsedSize + sizeAligned > bufferSize)
        return NULL;

    u8* ret = static_cast<u8*>(buffer[currentBufferIdx]) + bufferUsedSize;
    bufferUsedSize += sizeAligned;

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

void TemporaryBuffer::FlushCache() {
    if (bufferFlushedSize != bufferUsedSize) {
        DCFlushRange(static_cast<u8*>(buffer[currentBufferIdx]) + bufferFlushedSize, bufferUsedSize - bufferFlushedSize);
        bufferFlushedSize = bufferUsedSize;
    }
}

} } // namespace nw::eft

#endif // EFT_TEMPORARY_BUFFER_H_
