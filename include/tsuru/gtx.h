#pragma once

#include "log.h"
#include "filedevice/seadFileDevice.h"
#include "filedevice/seadFileDeviceMgr.h"
#include "agl/texturesampler.h"
#include "agl/texturedatainitializer.h"

// Wrapper around agl::TextureSampler for .GTX files
// TODO: Split this to GTX and GTXSampler
class GTX {
public:
    GTX()
        : gtx(nullptr)
        , texture()
    { }

    GTX(const sead::SafeString& path)
        : gtx(nullptr)
        , texture()
    {
        this->load(path);
    }

    ~GTX() {
        if (this->gtx)
            delete[] this->gtx;

        this->gtx = nullptr;
    }

    bool load(const sead::SafeString& path, sead::Heap* heap = nullptr) {
        sead::FileHandle handle;
        agl::TextureData textureData;

        if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, path, sead::FileDevice::FileOpenFlag_ReadOnly, 0)) {
            PRINT(LogColor::Red, "GTX Texture file at ", path.cstr(), " does not exist.");
            return false;
        }

        u32 filesize = handle.getFileSize();

        if (filesize == 0) {
            PRINT(LogColor::Red, "GTX Texture file at ", path.cstr(), " is empty.");
            return false;
        }

        this->gtx = new(heap, 0x2000) u8[filesize];

        if (gtx == nullptr) {
            PRINT(LogColor::Red, "Failed to allocate ", fmt::hex, filesize, " bytes of memory for GTX texture file: ", path.cstr());
            return false;
        }

        u32 bytesRead = handle.read(this->gtx, filesize);
        if (bytesRead != filesize) {
            PRINT(LogColor::Red, "Read size mismatch occurred while reading file at ", path.cstr(), ", read size: ", fmt::hex,  bytesRead, ", expected size: ", fmt::hex, filesize);
            return false;
        }

        agl::TextureDataInitializerGTX::initialize(&textureData, this->gtx, 0);
        textureData.invalidateGPUCache();

        this->texture.applyTextureData(textureData);

        return true;
    }

private:
    u8* gtx;

public:
    agl::TextureSampler texture;
};
