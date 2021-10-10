#pragma once

#include <sead/buffer.h>

class CustomSaveMgr;

class SaveMgrSystem { // This class handles initializing and saving all custom save managers
public:
    SaveMgrSystem(CustomSaveMgr* (*createInstance)(sead::Heap* heap));

    // Creates all instances from the instances funcptr array and calls init() on each of them
    static void initAll();

    // Calls save() on every manager in the managers pointer array
    static void saveAll();

    // Array of function pointers to createInstance
    static sead::Buffer<CustomSaveMgr* (*)(sead::Heap* heap)> instances;
    
    // Array of pointers to manager instances
    static sead::Buffer<CustomSaveMgr*> managers;
};

// Enters a save manager into the global save manager system
#define SAVEMGR_SYSTEM_ENTRY(CLASS)                         \
    const SaveMgrSystem CLASS ## _System (                  \
        reinterpret_cast<CustomSaveMgr* (*)(sead::Heap*)> ( \
            &CLASS::createInstance                          \
        )                                                   \
    )
