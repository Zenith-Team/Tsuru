#pragma once

#include "idisposer.h"
#include "string.h"

namespace sead {

class FileHandle;

class FileDevice {
public:
    enum FileOpenFlag {
        cFileOpenFlag_ReadOnly = 0,   // r
        cFileOpenFlag_WriteOnly = 1,  // w
        cFileOpenFlag_ReadWrite = 2,  // r+
        cFileOpenFlag_Create = 3      // w+
    };

public:
    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileOpenFlag flag, u32 divSize);
    bool tryClose(FileHandle* handle);

    static const s32 cBufferMinAlignment = 0x40;
};

class HandleBase : public IDisposer {
public:
    HandleBase()
        : IDisposer()
        , mDevice(NULL)
        , mOriginalDevice(NULL)
    { }

    virtual ~HandleBase() { }

    FileDevice* mDevice;
    FileDevice* mOriginalDevice;
    u8 mHandleBuffer[0x20];       // HandleBuffer = SafeArray<u8, 32>
};

class FileHandle : public HandleBase {
public:
    FileHandle()
        : HandleBase()
        , mDivSize(0)
    { }

    virtual ~FileHandle() {
        FileDevice* _device = mOriginalDevice;
        if (_device != NULL)
            _device->tryClose(this);
    }

    u32 read(u8* outBuffer, u32 bytesToRead);

    s32 mDivSize;
};

}
