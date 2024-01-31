#pragma once

#include "tsuru/save/system/customsavemgr.h"
#include "tsuru/save/system/savemgrsystem.h"

// Array of function pointers to createInstance
MiniPointerList<CustomSaveMgr* (*)(sead::Heap* heap), SAVEMGR_SYSTEM_MAX> SaveMgrSystem::ciList;

// Array of pointers to manager instances
MiniPointerList<CustomSaveMgr*, SAVEMGR_SYSTEM_MAX> SaveMgrSystem::managers;

SaveMgrSystem::SaveMgrSystem(CustomSaveMgr* (*createInstance)(sead::Heap* heap)) {
    SaveMgrSystem::ciList.append(createInstance);
}

void SaveMgrSystem::initSystem() {
    // Create each instance using the function pointer given in the ctor
    for (u32 i = 0; i < SaveMgrSystem::ciList.count(); i++)
        SaveMgrSystem::managers.append((SaveMgrSystem::ciList[i])(nullptr));

    // Call init() on each of the managers that we just created
    for (u32 i = 0; i < SaveMgrSystem::managers.count(); i++)
        SaveMgrSystem::managers[i]->init();

    if (SaveMgrSystem::managers.count() > 1) {
        PRINT("%u save managers were inited", SaveMgrSystem::managers.count());
    } else {
        PRINT("1 save manager was inited");
    }
}

void SaveMgrSystem::saveSystem() {
    for (u32 i = 0; i < SaveMgrSystem::managers.count(); i++)
        SaveMgrSystem::managers[i]->save();

    if (SaveMgrSystem::managers.count() > 1) {
        PRINT("%u save managers were written to disk", SaveMgrSystem::managers.count());
    } else {
        PRINT("1 save manager was written to disk");
    }
}
