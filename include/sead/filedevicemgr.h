#pragma once

#include "filedevice.h"
#include "safestring.h"

namespace sead {

class FileDeviceMgr {
public:
    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileDevice::FileOpenFlag flag, u32 divSize);
    u8* tryLoad(FileDevice::LoadArg& arg);

    static FileDeviceMgr* sInstance;
};

}
