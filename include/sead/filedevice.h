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
            : mPath("")
            , mBuffer(NULL)
            , mBuffersize(0)
            , mHeap(NULL)
            , mAlignment(0)
            , mDivSize(0)
            , mReadSize(0)
            , mRoundupSize(0)
            , mNeedUnload(false)
        { }

        LoadArg(const LoadArg& arg)
            : mPath(arg.mPath)
            , mBuffer(arg.mBuffer)
            , mBuffersize(arg.mBuffersize)
            , mHeap(arg.mHeap)
            , mAlignment(arg.mAlignment)
            , mDivSize(arg.mDivSize)
            , mReadSize(arg.mReadSize)
            , mRoundupSize(arg.mRoundupSize)
            , mNeedUnload(arg.mNeedUnload)
        { }

        SafeString mPath;
        u8* mBuffer;
        u32 mBuffersize;
        Heap* mHeap;
        s32 mAlignment;
        u32 mDivSize;
        u32 mReadSize;
        u32 mRoundupSize;
        bool mNeedUnload;
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
        , mDevice(nullptr)
        , mOriginalDevice(nullptr)
    { }

    virtual ~HandleBase() { }

    FileDevice* mDevice;
    FileDevice* mOriginalDevice;
    u8 mHandleBuffer[0x20]; // SafeArray<u8, 32>
};

class FileHandle : public HandleBase {
public:
    FileHandle()
        : HandleBase()
        , mDivSize(0)
    { }

    virtual ~FileHandle() {
        FileDevice* _device = mOriginalDevice;
        if (_device != nullptr)
            _device->tryClose(this);
    }

    s32 mDivSize;
};

}
