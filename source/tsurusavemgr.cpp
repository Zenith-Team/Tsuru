#include <sead.h>
#include <tsuru/tsurusavemgr.h>
#include <log.h>

SEAD_SINGLETON_DISPOSER_IMPL(TsuruSaveMgr)

TsuruSaveMgr::TsuruSaveData TsuruSaveMgr::sSaveData aligned(sead::FileDevice::cBufferMinAlignment);

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

        if (!TsuruSaveMgr::instance()->write())
            return;
    }

    else if (bytesRead != sizeof(TsuruSaveMgr::TsuruSaveData)) { // Savefile is corrupted OR something broke with reading
        LOG("Read size mismatch, read size: %u, expected size: %u", bytesRead, sizeof(TsuruSaveMgr::TsuruSaveData));
        TsuruSaveMgr::sSaveData = TsuruSaveMgr::TsuruSaveData();
        TsuruSaveMgr::instance()->write();
        return;
    }

    else if (TsuruSaveMgr::sSaveData.magic != 0xCAFEF00D) { // Savefile is corrupted
        LOG("ts_savedata.dat is corrupted. Recreating...");
        TsuruSaveMgr::sSaveData = TsuruSaveMgr::TsuruSaveData();
        TsuruSaveMgr::instance()->write();
        return;
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

    else {
        TsuruSaveMgr::instance()->write();
    }
}

bool TsuruSaveMgr::write() {
    u32 bytesWritten;
    sead::FileHandle handle;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, "save://ts_savedata.dat", sead::FileDevice::cFileOpenFlagCreate, 0);

    if (!handle.device)
        return false;

    device->tryWrite(&bytesWritten, &handle, reinterpret_cast<u8*>(&TsuruSaveMgr::sSaveData), sizeof(TsuruSaveMgr::TsuruSaveData));

    if (bytesWritten != sizeof(TsuruSaveMgr::TsuruSaveData))
        return false;

    return true;
}

void TsuruSaveMgr::boot() {
    TsuruSaveMgr::createInstance(nullptr)->init();
}
