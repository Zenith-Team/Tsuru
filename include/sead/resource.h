#pragma once

#include "sead/tlist.h"
#include "sead/runtimetypeinfo.h"
#include "sead/bitflag.h"
#include "sead/safestring.h"
#include "sead/filedevice.h"
#include "sead/resourcemgr.h"

namespace sead {

class Heap;

class Resource : public TListNode<Resource*> {
    SEAD_RTTI_BASE(Resource);

public:
    Resource();
    virtual ~Resource();

    virtual void doPostCreate_() { }
};

static_assert(sizeof(Resource) == 0x14, "sead::Resource size mismatch");

class DirectResource : public Resource {
    SEAD_RTTI_OVERRIDE(DirectResource, Resource);

public:
    DirectResource();
    virtual ~DirectResource();

    virtual u32 getLoadDataAlignment();
    virtual void doCreate_(u8*, u32, Heap*);

    void create(u8* buffer, u32 bufferSize, u32 allocSize, bool allocated, Heap* heap);

    u8* rawData;
    u32 rawSize;
    u32 bufferSize;
    BitFlag32 settingFlag;
};

static_assert(sizeof(DirectResource) == 0x24, "sead::DirectResource size mismatch");

class ArchiveRes : public DirectResource {
    SEAD_RTTI_OVERRIDE(ArchiveRes, DirectResource);

public:
    class FileInfo {
    public:
        FileInfo()
            : startOffset(0)
            , length(0)
        { }

        u32 getStartOffset() const { return startOffset; }
        u32 getLength() const { return length; }

        u32 startOffset;
        u32 length;
    };

    static_assert(sizeof(FileInfo) == 0x8, "sead::ArchiveRes::FileInfo size mismatch");

public:
    ArchiveRes()
        : DirectResource()
        , enable(false)
    { }

    virtual ~ArchiveRes();

    u32 getLoadDataAlignment() override;

protected:
    void doCreate_(u8* buf, u32, Heap*) override;
    
    virtual void* getFileImpl_(const SafeString& filePath, FileInfo* fileInfo) = 0;
    virtual void* getFileFastImpl_(s32 entryId, FileInfo* fileInfo) = 0;
    virtual s32 convertPathToEntryIDImpl_(const SafeString& filePath) = 0;
    virtual bool setCurrentDirectoryImpl_(const SafeString& filePath) = 0;
    virtual bool openDirectoryImpl_(HandleBuffer* handleBuffer, const SafeString& dirPath) = 0;
    virtual bool closeDirectoryImpl_(HandleBuffer* handleBuffer) = 0;
    virtual u32 readDirectoryImpl_(HandleBuffer* handleBuffer, DirectoryEntry* entry, u32 num) = 0;
    virtual bool prepareArchive_(const void* archive) = 0;

public:
    ResourcePtr load(ResourceMgr::LoadArg& arg);

    u8* getFile(const SafeString& filePath, FileInfo* fileInfo = nullptr) {
        // SEAD_ASSERT(enable);
        return static_cast<u8*>(getFileImpl_(filePath, fileInfo));
    }

    u8* getFileFast(s32 entryId, FileInfo* fileInfo = nullptr) {
        // SEAD_ASSERT(enable);
        return static_cast<u8*>(getFileFastImpl_(entryId, fileInfo));
    }

    s32 convertPathToEntryID(const SafeString& filePath) {
        // SEAD_ASSERT(enable);
        return convertPathToEntryIDImpl_(filePath);
    }

    bool setCurrentDirectory(const SafeString& filePath) {
        // SEAD_ASSERT(enable);
        return setCurrentDirectoryImpl_(filePath);
    }

    bool openDirectory(HandleBuffer* handleBuffer, const SafeString& dirPath) {
        // SEAD_ASSERT(handleBuffer);
        return openDirectoryImpl_(handleBuffer, dirPath);
    }

    bool closeDirectory(HandleBuffer* handleBuffer) {
        // SEAD_ASSERT(handleBuffer);
        return closeDirectoryImpl_(handleBuffer);
    }

    u32 readDirectory(HandleBuffer* handleBuffer, DirectoryEntry* entry, u32 num) {
        // SEAD_ASSERT(handleBuffer);
        // SEAD_ASSERT(entry);
        return readDirectoryImpl_(handleBuffer, entry, num);
    }

protected:
    void setFileInfo(FileInfo* fileInfo, u32 startOffset, u32 length) {
        //SEAD_ASSERT(fileInfo);
        fileInfo->startOffset = startOffset;
        fileInfo->length      = length;
    }

    bool enable;
};

static_assert(sizeof(ArchiveRes) == 0x28, "sead::ArchiveRes size mismatch");

}
