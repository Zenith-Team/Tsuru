#include "tsuru/save/system/customsavemgr.h"

CustomSaveMgr::CustomSaveMgr(const sead::SafeString& filepath, CustomSaveData* savestruct)
    : filepath(filepath)
    , inited(false)
    , savestruct(savestruct)
{ }

bool CustomSaveMgr::write() {
    u32 bytesWritten;
    sead::FileHandle handle;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, this->filepath, sead::FileDevice::FileOpenFlag_Create, 0);

    if (!handle.device) {
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
    sead::FileDeviceMgr::instance()->tryOpen(&readHandle, this->filepath, sead::FileDevice::FileOpenFlag_ReadOnly, 0);

    u32 bytesRead = readHandle.read(reinterpret_cast<u8*>(this->savestruct), this->getSaveDataSize());

    if (!readHandle.device) {
        PRINT("Custom save file at ", this->filepath.stringTop, " does not exist. Creating...");

        if (!this->write()) {
            PRINT("Write failed.");
            return;
        }
    }

    else if (bytesRead != this->getSaveDataSize()) {
        PRINT(LogColor::Red, "Manager ", this->filepath.stringTop, " had a read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, this->getSaveDataSize());
        this->remakeSaveData();
        this->write();
        return;
    }

    else if (this->savestruct->magic != 0xCAFEF00D) {
        PRINT("Custom save file at ", this->filepath.stringTop, " is corrupted. Recreating...");
        this->remakeSaveData();
        this->write();
        return;
    }
}

void CustomSaveMgr::save() {
    if (!this->inited){
        PRINT("Save manager at ", this->filepath.stringTop, " was not inited before saving. Returning...");
        return;
    }

    this->write();
}
