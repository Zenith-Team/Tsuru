#include "tsuru/save/system/customsavemgr.h"

CustomSaveMgr::CustomSaveMgr(const sead::SafeString& filepath, CustomSaveData* savestruct)
    : filepath(filepath)
    , inited(false)
    , savestruct(savestruct)
{ }

bool CustomSaveMgr::write() {
    u32 bytesWritten;
    sead::FileHandle handle;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, this->filepath, sead::FileDevice::cFileOpenFlag_Create, 0);

    if (!handle.isOpen()) {
        PRINT("Handle device was null.");
        return false;
    }

    device->tryWrite(&bytesWritten, &handle, reinterpret_cast<u8*>(this->savestruct), this->getSaveDataSize());

    if (bytesWritten != this->getSaveDataSize()) {
        PRINT("Write size mismatch, wrote size: ", fmt::hex, bytesWritten, ", expected size: ", fmt::hex, this->getSaveDataSize());
        return false;
    }

    else return true;
}

void CustomSaveMgr::init() {
    if (this->inited)
        return;

    sead::FileHandle readHandle;
    sead::FileDeviceMgr::instance()->tryOpen(&readHandle, this->filepath, sead::FileDevice::cFileOpenFlag_ReadOnly, 0);

    u32 bytesRead = readHandle.read(reinterpret_cast<u8*>(this->savestruct), this->getSaveDataSize());

    if (!readHandle.getDevice()) {
        PRINT("Custom save file at ", this->filepath.cstr(), " does not exist. Creating...");

        if (!this->write()) {
            PRINT("Write failed.");
            return;
        }
    }

    else if (bytesRead != this->getSaveDataSize()) {
        PRINT(LogColor::Red, "Manager ", this->filepath.cstr(), " had a read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, this->getSaveDataSize());
        this->remakeSaveData();
        this->write();
        this->inited = true;
        return;
    }

    else if (this->savestruct->magic != 0xCAFEF00D) {
        PRINT("Custom save file at ", this->filepath.cstr(), " is corrupted. Recreating...");
        this->remakeSaveData();
        this->write();
        this->inited = true;
        return;
    }

    this->inited = true;
}

void CustomSaveMgr::save() {
    if (!this->inited) {
        PRINT("Save manager at ", this->filepath.cstr(), " was not inited before saving. Returning...");
        return;
    }

    this->write();
}
