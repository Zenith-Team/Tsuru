#pragma once

#include <sead/heap.h>
#include <tsuru/minipointerlist.h>

#define SAVEMGR_SYSTEM_MAX 0x100 // The maximum amount of Save Managers that the system can hold

class CustomSaveMgr;

class SaveMgrSystem { // This class handles initializing and saving all custom save managers
public:
    // Instanciating this class will enter the class instance pointed to by the parameter into the system list
    // @param createInstance Pointer to the createInstance function of the target manager
    SaveMgrSystem(CustomSaveMgr* (*createInstance)(sead::Heap* heap));

private:
    // Creates all instances from the instances funcptr array and calls init() on each of them
    static void initSystem();

    // Calls save() on every manager in the managers pointer array
    static void saveSystem();

    // Array of function pointers to createInstance
    static MiniPointerList<CustomSaveMgr* (*)(sead::Heap* heap), SAVEMGR_SYSTEM_MAX> ciList;
    
    // Array of pointers to manager instances
    static MiniPointerList<CustomSaveMgr*, SAVEMGR_SYSTEM_MAX> managers;
};

// Enters a save manager into the global save manager system
#define SAVEMGR_SYSTEM_ENTRY(CLASS)                         \
    const SaveMgrSystem CLASS ## _System (                  \
        reinterpret_cast<CustomSaveMgr* (*)(sead::Heap*)> ( \
            &CLASS::createInstance                          \
        )                                                   \
    )
