#pragma once

#include "savedata.h"
#include <sead.h>

class SaveMgr { // Size: 0x50
    SEAD_SINGLETON_DISPOSER(SaveMgr)

public:
    SaveMgr(sead::Heap* heap);
    
    static inline SaveData::SaveSlot getLastUsedSaveSlot() { return SaveMgr::instance()->saveData->saveSlots[SaveMgr::instance()->saveData->header.lastSessionSaveSlot]; }

    void* thread;           // sead::DelegateThread*
    u32 _14;
    u8 _18[0x24 - 0x18];    // Unknown values 1
    SaveData* saveData;
    void* personalSaveData; // PersonalSaveData*
    u8 _2C;
    u8 _2D;
    u8 _2E;
    u8 _2F;
    s32 _30;
    u8 _34[0x38 - 0x34];    // Unknown values 2
    u8 _38[0x8];            // sead::DateTime
    u8 _40[0x8];            // sead::DateTime
    void* _48;              // Some sort of vtable
    u8 _4C[0x4F - 0x4C];    // Unknown values 3
};

static_assert(sizeof(SaveMgr) == 0x50, "SaveMgr size mismatch");
