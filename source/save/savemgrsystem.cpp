#pragma once

#include <tsuru/save/customsavemgr.h>
#include <tsuru/save/savemgrsystem.h>

// Array of function pointers to createInstance
sead::Buffer<CustomSaveMgr* (*)(sead::Heap* heap)> SaveMgrSystem::instances;

// Array of pointers to manager instances
sead::Buffer<CustomSaveMgr*> SaveMgrSystem::managers;

SaveMgrSystem::SaveMgrSystem(CustomSaveMgr* (*createInstance)(sead::Heap* heap)) {
    SaveMgrSystem::instances.buffer[SaveMgrSystem::instances.size++] = createInstance;
}

void SaveMgrSystem::initAll() {
    // Create each instance using the function pointer given in the ctor
    for (u32 i = 0; i < SaveMgrSystem::instances.size; i++) {
        if (SaveMgrSystem::instances.buffer[i]) {
            SaveMgrSystem::managers.buffer[SaveMgrSystem::managers.size++] = SaveMgrSystem::instances.buffer[i](nullptr);
        }
    }

    // Call init() on each of the managers that we just created
    for (u32 i = 0; i < SaveMgrSystem::managers.size; i++) {
        SaveMgrSystem::managers.buffer[i]->init();
    }

    LOG("%u save managers were inited", SaveMgrSystem::managers.size);
}

void SaveMgrSystem::saveAll() {
    for (u32 i = 0; i < SaveMgrSystem::managers.size; i++) {
        SaveMgrSystem::managers.buffer[i]->save();
    }

    LOG("%u save managers were written to disk", SaveMgrSystem::managers.size);
}
