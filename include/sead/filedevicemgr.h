#pragma once

#include "sead/filedevice.h"
#include "sead/safestring.h"

namespace sead {

class FileDeviceMgr {
    SEAD_SINGLETON_DISPOSER(FileDeviceMgr);

public:
    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileDevice::FileOpenFlag flag, u32 divSize);
    u8* tryLoad(FileDevice::LoadArg& arg);
};

}
