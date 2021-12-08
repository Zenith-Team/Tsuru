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
        LOG("Handle device was null.");
        return false;
    }

    device->tryWrite(&bytesWritten, &handle, reinterpret_cast<u8*>(this->savestruct), this->getSaveDataSize());

    if (bytesWritten != this->getSaveDataSize()) {
        LOG("Write size mismatch, wrote size: 0x%x, expected size: 0x%x", bytesWritten, this->getSaveDataSize());
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
        LOG("Custom save file at %s does not exist. Creating...", this->filepath.stringTop);

        if (!this->write()) {
            LOG("Write failed.");
            return;
        }
    }

    else if (bytesRead != this->getSaveDataSize()) {
        LOG("Manager %s had a read size mismatch, read size: 0x%x, expected size: 0x%x", this->filepath.stringTop, bytesRead, this->getSaveDataSize());
        this->remakeSaveData();
        this->write();
        return;
    }

    else if (this->savestruct->magic != 0xCAFEF00D) {
        LOG("Custom save file at %s is corrupted. Recreating...", this->filepath.stringTop);
        this->remakeSaveData();
        this->write();
        return;
    }
}

void CustomSaveMgr::save() {
    if (!this->inited){
        LOG("Save manager at %s was not inited before saving. Returning...", this->filepath.stringTop);
        return;
    }

    this->write();
}
