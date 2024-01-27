#include "tsuru/save/managers/carterrasavemgr.h"
#include "tsuru/save/system/savemgrsystem.h"
#include "game/savemgr.h"
#include "game/level/levelinfo.h"

SEAD_SINGLETON_DISPOSER_IMPL(CarterraSaveMgr);

CarterraSaveMgr::CarterraSaveData CarterraSaveMgr::sSaveData aligned(sead::FileDevice::sBufferMinAlignment);

CarterraSaveMgr::CarterraSaveMgr()
    : CustomSaveMgr("save://crt_savedata.dat", &CarterraSaveMgr::sSaveData)
{ }

u32 CarterraSaveMgr::getSaveDataSize() {
    return sizeof(CarterraSaveMgr::CarterraSaveData);
}

void CarterraSaveMgr::remakeSaveData() {
    CarterraSaveMgr::sSaveData = CarterraSaveData();
}

SAVEMGR_SYSTEM_ENTRY(CarterraSaveMgr);

/** PATCHES: */

void setNormalExitFlag() {
    u32 lastSessionSaveSlot = SaveMgr::instance()->saveData->header.lastSessionSaveSlot;
    CarterraSaveMgr::CarterraSaveData::SaveSlot* slot = &CarterraSaveMgr::sSaveData.saveSlots[lastSessionSaveSlot];
    slot->levelCompletions[LevelInfo::instance()->world][LevelInfo::instance()->level] |= CarterraSaveMgr::CarterraSaveData::LevelCompletion::NormalExit;
}

void setSecretExitFlag() {
    u32 lastSessionSaveSlot = SaveMgr::instance()->saveData->header.lastSessionSaveSlot;
    CarterraSaveMgr::CarterraSaveData::SaveSlot* slot = &CarterraSaveMgr::sSaveData.saveSlots[lastSessionSaveSlot];
    slot->levelCompletions[LevelInfo::instance()->world][LevelInfo::instance()->level] |= CarterraSaveMgr::CarterraSaveData::LevelCompletion::SecretExit;
}
