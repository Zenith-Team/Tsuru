#include <sead.h>
#include <custom/shsavemgr.h>
#include <log.h>

SEAD_SINGLETON_DISPOSER_IMPL(SHSaveMgr)

SHSaveMgr::SHSaveData SHSaveMgr::sSaveData __attribute__((aligned(sead::FileDevice::cBufferMinAlignment)));

SHSaveMgr::SHSaveMgr()
    : mInited(false)
{ }

void SHSaveMgr::init() {
    if (SHSaveMgr::instance()->mInited) {
        LOG("SHSaveMgr was inited already. Returning...");
        return;
    }

    sead::FileHandle readHandle;
    sead::FileDeviceMgr::instance()->tryOpen(&readHandle, "save://sh_savedata.dat", sead::FileDevice::cFileOpenFlagReadOnly, 0);

    u32 bytesRead = readHandle.read(reinterpret_cast<u8*>(&SHSaveMgr::sSaveData), sizeof(SHSaveMgr::SHSaveData));

    if (!readHandle.mDevice) { // Savefile does not exist
        LOG("sh_savedata.dat does not exist. Creating...");

        u32 bytesWritten;
        sead::FileHandle writeHandle;
        
        sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&writeHandle, "save://sh_savedata.dat", sead::FileDevice::cFileOpenFlagCreate, 0);
        
        if (!writeHandle.mDevice) {
            LOG("writeHandle.mDevice is nullptr");
            return;
        }

        device->tryWrite(&bytesWritten, &writeHandle, reinterpret_cast<u8*>(&SHSaveMgr::sSaveData), sizeof(SHSaveMgr::SHSaveData));

        if (bytesWritten != sizeof(SHSaveMgr::SHSaveData)) {
            LOG("Write size mismatch, wrote size: %u, expected size: %u", bytesWritten, sizeof(SHSaveMgr::SHSaveData));
            return;
        }
    }

    else if (bytesRead != sizeof(SHSaveMgr::SHSaveData)) { // Savefile is corrupted OR something broke with reading
        LOG("Read size mismatch, read size: %u, expected size: %u", bytesRead, sizeof(SHSaveMgr::SHSaveData));
        return; // TODO: Make it recreate the file again
    }

    if (SHSaveMgr::sSaveData.magic != 0xCAFEF00D) {
        LOG("sh_savedata.dat is corrupted. Recreating...");
        return; // TODO: Make it recreate the file again
    }

    LOG("SHSaveMgr inited!");
    LOG("NoClip: %i", SHSaveMgr::sSaveData.noClipEnabled);
    SHSaveMgr::instance()->mInited = true;
}

void SHSaveMgr::save() {
    LOG("Saving SHSaveData...");

    if (!SHSaveMgr::instance()->mInited) {
        LOG("SHSaveMgr was not inited. Returning...");
        return;
    }

    sead::FileHandle handle;
    sead::FileDeviceMgr::instance()->tryOpen(&handle, "save://sh_savedata.dat", sead::FileDevice::cFileOpenFlagWriteOnly, 0);

    if (!handle.mDevice) {
        LOG("handle.mDevice is nullptr");
        return;
    }

    u32 bytesWritten;

    handle.mDevice->tryWrite(&bytesWritten, &handle, reinterpret_cast<u8*>(&SHSaveMgr::sSaveData), sizeof(SHSaveMgr::SHSaveData));

    if (bytesWritten != sizeof(SHSaveMgr::SHSaveData))
        LOG("Write size mismatch: wrote size: %u, expeected size: %u", bytesWritten, sizeof(SHSaveMgr::SHSaveData));
}

void SHSaveMgr::boot() {
    SHSaveMgr::createInstance(nullptr)->init();
}
