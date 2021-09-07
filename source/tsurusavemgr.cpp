#include <sead.h>
#include <tsuru/tsurusavemgr.h>
#include <log.h>

SEAD_SINGLETON_DISPOSER_IMPL(TsuruSaveMgr)

TsuruSaveMgr::TsuruSaveData TsuruSaveMgr::sSaveData __attribute__((aligned(sead::FileDevice::cBufferMinAlignment)));

TsuruSaveMgr::TsuruSaveMgr()
    : inited(false)
{ }

void TsuruSaveMgr::init() {
    if (TsuruSaveMgr::instance()->inited) {
        LOG("TsuruSaveMgr was inited already. Returning...");
        return;
    }

    sead::FileHandle readHandle;
    sead::FileDeviceMgr::instance()->tryOpen(&readHandle, "save://ts_savedata.dat", sead::FileDevice::cFileOpenFlagReadOnly, 0);

    u32 bytesRead = readHandle.read(reinterpret_cast<u8*>(&TsuruSaveMgr::sSaveData), sizeof(TsuruSaveMgr::TsuruSaveData));

    if (!readHandle.device) { // Savefile does not exist
        LOG("ts_savedata.dat does not exist. Creating...");

        u32 bytesWritten;
        sead::FileHandle writeHandle;
        
        sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&writeHandle, "save://ts_savedata.dat", sead::FileDevice::cFileOpenFlagCreate, 0);
        
        if (!writeHandle.device) {
            LOG("writeHandle.device is nullptr");
            return;
        }

        device->tryWrite(&bytesWritten, &writeHandle, reinterpret_cast<u8*>(&TsuruSaveMgr::sSaveData), sizeof(TsuruSaveMgr::TsuruSaveData));

        if (bytesWritten != sizeof(TsuruSaveMgr::TsuruSaveData)) {
            LOG("Write size mismatch, wrote size: %u, expected size: %u", bytesWritten, sizeof(TsuruSaveMgr::TsuruSaveData));
            return;
        }
    }

    else if (bytesRead != sizeof(TsuruSaveMgr::TsuruSaveData)) { // Savefile is corrupted OR something broke with reading
        LOG("Read size mismatch, read size: %u, expected size: %u", bytesRead, sizeof(TsuruSaveMgr::TsuruSaveData));
        return; // TODO: Make it recreate the file again
    }

    if (TsuruSaveMgr::sSaveData.magic != 0xCAFEF00D) {
        LOG("sh_savedata.dat is corrupted. Recreating...");
        return; // TODO: Make it recreate the file again
    }

    LOG("TsuruSaveMgr inited!");
    TsuruSaveMgr::instance()->inited = true;
}

void TsuruSaveMgr::save() {
    LOG("Saving TsuruSaveData...");

    if (!TsuruSaveMgr::instance()->inited) {
        LOG("TsuruSaveMgr was not inited. Returning...");
        return;
    }

    sead::FileHandle handle;
    sead::FileDeviceMgr::instance()->tryOpen(&handle, "save://sh_savedata.dat", sead::FileDevice::cFileOpenFlagWriteOnly, 0);

    if (!handle.device) {
        LOG("handle.device is nullptr");
        return;
    }

    u32 bytesWritten;

    handle.device->tryWrite(&bytesWritten, &handle, reinterpret_cast<u8*>(&TsuruSaveMgr::sSaveData), sizeof(TsuruSaveMgr::TsuruSaveData));

    if (bytesWritten != sizeof(TsuruSaveMgr::TsuruSaveData))
        LOG("Write size mismatch: wrote size: %u, expeected size: %u", bytesWritten, sizeof(TsuruSaveMgr::TsuruSaveData));
}

void TsuruSaveMgr::boot() {
    TsuruSaveMgr::createInstance(nullptr)->init();
}
