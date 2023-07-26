#pragma once

#include "sead/idisposer.h"
#include "sead/safestring.h"
#include "sead/tlist.h"
#include "sead/runtimetypeinfo.h"

namespace sead {

class FileHandle;
class DirectoryHandle;
struct DirectoryEntry;

class BufferedSafeString;

class FileDevice : public TListNode<FileDevice*>, public IDisposer {
    SEAD_RTTI_BASE(FileDevice);

public:
    enum FileOpenFlag {
        FileOpenFlag_ReadOnly   = 0,
        FileOpenFlag_WriteOnly  = 1,
        FileOpenFlag_ReadWrite  = 2,
        FileOpenFlag_Create     = 3
    };

    enum SeekOrigin {
        SeekOrigin_Begin = 0,
        SeekOrigin_Current = 1,
        SeekOrigin_End = 2
    };

public:
    struct LoadArg {
        LoadArg()
            : path("")
            , buffer(NULL)
            , bufferSize(0)
            , heap(NULL)
            , alignment(0)
            , divSize(0)
            , readSize(0)
            , roundupSize(0)
            , needUnload(false)
        { }

        LoadArg(const LoadArg& arg)
            : path(arg.path)
            , buffer(arg.buffer)
            , bufferSize(arg.bufferSize)
            , heap(arg.heap)
            , alignment(arg.alignment)
            , divSize(arg.divSize)
            , readSize(arg.readSize)
            , roundupSize(arg.roundupSize)
            , needUnload(arg.needUnload)
        { }

        SafeString path;
        u8* buffer;
        u32 bufferSize;
        Heap* heap;
        s32 alignment;
        u32 divSize;
        u32 readSize;
        u32 roundupSize;
        bool needUnload;
    };

public:
    virtual ~FileDevice();

    virtual bool doIsAvailable_() const = 0;
    virtual u8* doLoad_(LoadArg& arg);
    virtual FileDevice* doOpen_(FileHandle* handle, const SafeString& filename, FileOpenFlag flag) = 0;
    virtual bool doClose_(FileHandle* handle) = 0;
    virtual bool doRead_(u32* readSize, FileHandle* handle, u8* buf, u32 size) = 0;
    virtual bool doWrite_(u32* writeSize, FileHandle* handle, const u8* buf, u32 size) = 0;
    virtual bool doSeek_(FileHandle* handle, s32 offset, SeekOrigin origin) = 0;
    virtual bool doGetCurrentSeekPos_(u32* pos, FileHandle* handle) = 0;
    virtual bool doGetFileSize_(u32* size, const SafeString& path) = 0;
    virtual bool doGetFileSize_(u32* size, FileHandle* handle) = 0;
    virtual bool doIsExistFile_(bool* isExist, const SafeString& path) = 0;
    virtual bool doIsExistDirectory_(bool* isExist, const SafeString& path) = 0;
    virtual FileDevice* doOpenDirectory_(DirectoryHandle* handle, const SafeString& dirname) = 0;
    virtual bool doCloseDirectory_(DirectoryHandle* handle) = 0;
    virtual bool doReadDirectory_(u32* readNum, DirectoryHandle* handle, DirectoryEntry* entry, u32 num) = 0;
    virtual bool doMakeDirectory_(const SafeString& path, u32 permission) = 0;
    virtual s32 doGetLastRawError_() const = 0;
    virtual void doTracePath_(const SafeString& path) const;
    virtual void doResolvePath_(BufferedSafeString* out, const SafeString& path) const;

    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileOpenFlag flag, u32 divSize);
    bool tryClose(FileHandle* handle);
    bool tryRead(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead);
    bool tryWrite(u32* bytesWritten, FileHandle* handle, const u8* inBuffer, u32 bytesToWrite);
    bool trySeek(FileHandle* handle, s32 offset, SeekOrigin origin);

    static const s32 sDriveNameBufferSize = 32;
    static const s32 sBufferMinAlignment = 64;

    sead::SafeString driveName; s32 driveNameBufferSize; char driveNameBuffer[sDriveNameBufferSize]; // FixedSafeString<sDriveNameBufferSize> driveName
    bool permission;
};

class HandleBase : public IDisposer {
public:
    HandleBase()
        : IDisposer()
        , device(nullptr)
        , originalDevice(nullptr)
    { }

    virtual ~HandleBase() { }

    FileDevice* device;
    FileDevice* originalDevice;
    u8 handleBuffer[0x20]; // SafeArray<u8, 32>
};

class FileHandle : public HandleBase {
public:
    FileHandle()
        : HandleBase()
        , divSize(0)
    { }

    virtual ~FileHandle() {
        FileDevice* _device = originalDevice;
        if (_device != nullptr)
            _device->tryClose(this);
    }

    u32 read(u8* outBuffer, u32 bytesToRead);
    u32 getFileSize();

    s32 divSize;
};

}
