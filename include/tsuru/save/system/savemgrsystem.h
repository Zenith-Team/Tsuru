#pragma once

#include <tsuru/minipointerlist.h>

#define SAVEMGR_SYSTEM_LIMIT 0x100 // The maximum amount of Save Managers that the system can hold

class CustomSaveMgr;

class SaveMgrSystem { // This class handles initializing and saving all custom save managers
public:
    SaveMgrSystem(CustomSaveMgr* (*createInstance)(sead::Heap* heap));

    // Creates all instances from the instances funcptr array and calls init() on each of them
    static void initSystem();

    // Calls save() on every manager in the managers pointer array
    static void saveSystem();

    // Array of function pointers to createInstance
    static MiniPointerList<CustomSaveMgr* (*)(sead::Heap* heap), SAVEMGR_SYSTEM_LIMIT> ciList;
    
    // Array of pointers to manager instances
    static MiniPointerList<CustomSaveMgr*, SAVEMGR_SYSTEM_LIMIT> managers;
};

// Enters a save manager into the global save manager system
#define SAVEMGR_SYSTEM_ENTRY(CLASS)                         \
    const SaveMgrSystem CLASS ## _System (                  \
        reinterpret_cast<CustomSaveMgr* (*)(sead::Heap*)> ( \
            &CLASS::createInstance                          \
        )                                                   \
    )
