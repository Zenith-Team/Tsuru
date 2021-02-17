#include "dynamic_libs/zlib_functions.h"
#include "sead.h"
#include "log.h"

namespace sead {

u8*
SZSDecompressor::tryDecompFromDevice(
    const ResourceMgr::LoadArg& loadArg, Resource* resource,
    u32* outSize, u32* outAllocSize, bool* outAllocated
)
{
    Heap* heap = loadArg.load_data_heap;
    if (heap == NULL)
        heap = HeapMgr::sInstancePtr->getCurrentHeap();

    FileHandle handle;
    FileDevice* device;
    u8* src;

    if (loadArg.device != NULL)
        device = loadArg.device->tryOpen(&handle, loadArg.path, FileDevice::cFileOpenFlag_ReadOnly, loadArg.div_size);
    else
        device = FileDeviceMgr::sInstance->tryOpen(&handle, loadArg.path, FileDevice::cFileOpenFlag_ReadOnly, loadArg.div_size);

    if (device != NULL &&
       ((src = mWorkBuffer, src != NULL) ||
        (src = new(heap, -FileDevice::cBufferMinAlignment) u8[mWorkSize], src != NULL)))
    {
        u32 bytesRead = handle.read(src, mWorkSize);
        if (bytesRead >= 0x10)
        {
            u32 decompSize = getDecompSize(src);
            s32 decompAlignment = getDecompAlignment(src);

            u32 allocSize = loadArg.load_data_buffer_size;
            u8* dst = loadArg.load_data_buffer;

            if (decompSize > allocSize && allocSize != 0)
                decompSize = allocSize;

            bool allocated = false;
            allocSize = decompSize + 0x1F & 0xFFFFFFE0;

            if (dst == NULL)
            {
                DirectResource* directResource = DynamicCast<DirectResource, Resource>(resource);
                if (directResource != NULL)
                {
                    s32 alignment = loadArg.load_data_alignment;
                    if (alignment != 0)
                        decompAlignment = (alignment < 0x20) ? 0x20 : alignment;

                    else
                    {
                        if (decompAlignment == 0)
                            decompAlignment = directResource->getLoadDataAlignment();

                        decompAlignment = ((loadArg.instance_alignment < 0) ? -1 : 1) * ((decompAlignment < 0x20) ? 0x20 : decompAlignment);
                    }
                }

                else
                    decompAlignment = -(((loadArg.instance_alignment < 0) ? -1 : 1) << 5);

                dst = new(heap, decompAlignment) u8[allocSize];

                if (dst != NULL)
                    allocated = true;
            }


            if (dst != NULL)
            {
                s32 error;
                if (Endian::readU32(src) == 0x5A6C6962) // Zlib
                {
                    z_stream strm;

                    strm.zalloc = Z_NULL;
                    strm.zfree = Z_NULL;
                    strm.opaque = Z_NULL;
                    strm.avail_in = 0;
                    strm.next_in = Z_NULL;

                    s32 ret = inflateInit(&strm);
                    if (ret != Z_OK)
                        error = -1;

                    else
                    {
                        bytesRead -= 0x10;
                        u8* in = src + 0x10;

                        do
                        {
                            strm.avail_in = bytesRead;
                            strm.next_in = in;

                            strm.avail_out = allocSize - strm.total_out;
                            strm.next_out = dst + strm.total_out;
                            ret = inflate(&strm, Z_NO_FLUSH);

                            if (ret == Z_STREAM_ERROR || ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
                                break;

                            in = src;
                        }
                        while (ret != Z_STREAM_END && (bytesRead = handle.read(in, mWorkSize), bytesRead != 0));

                        (void)inflateEnd(&strm);
                        error = ret == Z_STREAM_END ? 0 : -2;
                    }
                }

                else
                {
                    if (bytesRead < mWorkSize)
                    error = decomp(dst, allocSize, src, mWorkSize);

                    else
                    {
                        DecompContext context(dst);
                        context.forceDestCount = decompSize;

                        do
                        {
                            error = streamDecomp(&context, src, bytesRead);
                            if (error <= 0)
                                break;
                        }
                        while ((bytesRead = handle.read(src, mWorkSize), bytesRead != 0));
                    }
                }

                if (!(error < 0))
                {
                    if (mWorkBuffer == NULL)
                        delete[] src;

                    if (outSize != NULL)
                        *outSize = decompSize;

                    if (outAllocSize != NULL)
                        *outAllocSize = allocSize;

                    if (outAllocated != NULL)
                        *outAllocated = allocated;

                    return dst;
                }

                if (allocated)
                    delete[] dst;
            }
        }

        if (mWorkBuffer == NULL)
            delete[] src;
    }

    return NULL;
}

}
