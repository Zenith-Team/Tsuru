#pragma once

#include <sead/idisposer.h>
#include <sead/safestring.h>

namespace sead {

class FileHandle;

class FileDevice {
public:
    enum FileOpenFlag {
        cFileOpenFlagReadOnly   = 0,
        cFileOpenFlagWriteOnly  = 1,
        cFileOpenFlagReadWrite  = 2,
        cFileOpenFlagCreate     = 3
    };

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
    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileOpenFlag flag, u32 divSize);
    bool tryClose(FileHandle* handle);
    bool tryRead(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead);
    bool tryWrite(u32* bytesWritten, FileHandle* handle, const u8* inBuffer, u32 bytesToWrite);

    static const s32 cBufferMinAlignment = 0x40;
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

    s32 divSize;
};

}
