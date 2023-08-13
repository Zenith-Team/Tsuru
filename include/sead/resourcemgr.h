#pragma once

#include "sead/idisposer.h"
#include "sead/safestring.h"
#include "sead/tlist.h"

namespace sead {

class Resource;

class ResourcePtr {
public:
    ResourcePtr(Resource* ptrV)
        : ptr(ptrV)
    { }

    operator Resource*() { return ptr; }
    operator const Resource*() const { return ptr; }

    Resource& operator*() { return *ptr; }
    Resource* operator->() { return ptr; }

    const Resource& operator*() const { return *ptr; }
    const Resource* operator->() const { return ptr; }

private:
    Resource* ptr;
};

class ResourceFactory;
class Decompressor;
class FileDevice;

class ResourceMgr {
    SEAD_SINGLETON_DISPOSER(ResourceMgr);

public:
    struct CreateArg {
        CreateArg()
            : buffer(nullptr)
            , fileSize(0)
            , bufferSize(0)
            , needUnload(false)
            , factory(nullptr)
            , ext()
            , heap(nullptr)
            , alignment(0x20)
        { }

        u8* buffer;
        u32 fileSize;
        u32 bufferSize;
        bool needUnload;
        ResourceFactory* factory;
        SafeString ext;
        Heap* heap;
        s32 alignment;
    };

    static_assert(sizeof(CreateArg) == 0x24, "sead::ResourceMgr::CreateArg size mismatch");

    struct LoadArg {
        LoadArg()
            : path()
            , instanceHeap(nullptr)
            , loadDataHeap(nullptr)
            , instanceAlignment(0x20)
            , loadDataAlignment(0)
            , loadDataBuffer(nullptr)
            , loadDataBufferSize(0)
            , factory(nullptr)
            , device(nullptr)
            , divSize(0)
        { }

        SafeString path;
        Heap* instanceHeap;
        Heap* loadDataHeap;
        s32 instanceAlignment;
        s32 loadDataAlignment;
        u8* loadDataBuffer;
        u32 loadDataBufferSize;
        ResourceFactory* factory;
        FileDevice* device;
        u32 divSize;
    };

    static_assert(sizeof(LoadArg) == 0x2C, "sead::ResourceMgr::LoadArg size mismatch");

    typedef TList<ResourceFactory*> FactoryList;
    typedef TList<Resource*> ResourceList;
    typedef TList<Decompressor*> DecompressorList;

public:
    ResourceMgr();
    ~ResourceMgr();

    void postCreate();

    void registerFactory(ResourceFactory* factory, const SafeString& name);
    void registerDecompressor(Decompressor* decompressor, const SafeString& name);

    void unregisterFactory(ResourceFactory* factory);
    void unregisterDecompressor(Decompressor* decompressor);

    ResourcePtr tryLoadWithoutDecomp(const LoadArg& arg);
    ResourcePtr tryLoad(const LoadArg& arg, const SafeString& convertExt, Decompressor* decomp);

    ResourceFactory* findFactory(const SafeString& ext);
    Decompressor* findDecompressor(const SafeString& ext);

    FactoryList factoryList;
    ResourceList postCreateResourceList;
    DecompressorList decompList;
    ResourceFactory* nullResourceFactory;
};

static_assert(sizeof(ResourceMgr) == 0x38, "sead::ResourceMgr size mismatch");

}
