#pragma once

#include "string.h"

namespace sead {

class Heap;
class FileDevice;
class ResourceFactory;
class Decompressor;


class ResourceMgr
{
public:
    struct LoadArg
    {
        LoadArg()
            : path()
            , instance_heap(NULL)
            , load_data_heap(NULL)
            , instance_alignment(0x20)
            , load_data_alignment(0)
            , load_data_buffer(NULL)
            , load_data_buffer_size(0)
            , factory(NULL)
            , device(NULL)
            , div_size(0)
        {
        }

        SafeString path;
        Heap* instance_heap;
        Heap* load_data_heap;
        s32 instance_alignment;
        s32 load_data_alignment;
        u8* load_data_buffer;
        u32 load_data_buffer_size;
        ResourceFactory* factory;
        FileDevice* device;
        u32 div_size;
    };

public:
    void unregisterDecompressor(Decompressor* decompressor);

    static ResourceMgr* sInstance;

    // ...
};

}
