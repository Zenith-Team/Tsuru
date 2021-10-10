#include <tsuru/save/tsurusavemgr.h>
#include <tsuru/save/savemgrsystem.h>

SEAD_SINGLETON_DISPOSER_IMPL(TsuruSaveMgr)

TsuruSaveMgr::TsuruSaveData TsuruSaveMgr::sSaveData aligned(sead::FileDevice::sBufferMinAlignment);

TsuruSaveMgr::TsuruSaveMgr()
    : CustomSaveMgr("save://ts_savedata.dat", &TsuruSaveMgr::sSaveData)
{ }

u32 TsuruSaveMgr::getSaveDataSize() {
    return sizeof(TsuruSaveMgr::TsuruSaveData);
}

void TsuruSaveMgr::remakeSaveData() {
    TsuruSaveMgr::sSaveData = TsuruSaveData();
}

SAVEMGR_SYSTEM_ENTRY(TsuruSaveMgr);
