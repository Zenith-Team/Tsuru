#pragma once

#include <sead/buffer.h>
#include <sead/idisposer.h>

class CustomSaveMgr;

class SaveMgrSystem {
    SEAD_SINGLETON_DISPOSER(SaveMgrSystem)

public:
    SaveMgrSystem();

    // Creates the system instance and calls initAllManagers
    static void globalInit();

    // Uses the system instance to call saveAllManagers
    static void globalSave();

    // Iterates through the list and calls init() on each manager in the system
    void initAllManagers();

    // Iterates through the list and calls save() on each manager in the system
    void saveAllManagers();

    void addToList(CustomSaveMgr* manager);

    sead::Buffer<CustomSaveMgr*> customManagers;
};

