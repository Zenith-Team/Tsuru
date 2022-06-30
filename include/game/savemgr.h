#pragma once

#include "savedata.h"
#include "sead/heap.h"
#include "sead/idisposer.h"
#include "sead/thread.h"

class SaveMgr { // Size: 0x50
    SEAD_SINGLETON_DISPOSER(SaveMgr)

public:
    SaveMgr(sead::Heap* heap);

    // @return Reference to the last used savefile slot
    static inline SaveData::SaveSlot& getLastUsedSaveSlot() { return SaveMgr::instance()->saveData->saveSlots[SaveMgr::instance()->saveData->header.lastSessionSaveSlot]; }

    // Creates SaveMgrThread and initializes the save data
    void init(sead::Heap* heap);

    void save(sead::DelegateThread* thread);

    void threadCallback(sead::DelegateThread* thread, u32 msgQueueElement);

    sead::DelegateThread* thread;
    u32 _14;
    u32 _18;
    s32 _1C;
    u32 _20;
    SaveData* saveData;
    PersonalSaveData* personalSaveData;
    u8 _2C;
    u8 _2D;
    u8 _2E;
    u8 _2F;
    s32 _30;
    u8 _34[0x38 - 0x34];    // Unknown values
    u8 _38[0x8];            // sead::DateTime
    u8 _40[0x8];            // sead::DateTime
    void* _48;              //? why is the vtable pointer here?
    u8 _4C[0x4F - 0x4C];    // Unknown values
};

static_assert(sizeof(SaveMgr) == 0x50, "SaveMgr size mismatch");
