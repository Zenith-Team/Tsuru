#pragma once

#include "filedevice.h"
#include "string.h"

namespace sead {

class FileDeviceMgr
{
public:
    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileDevice::FileOpenFlag flag, u32 divSize);

    static FileDeviceMgr* sInstance;
};

}
