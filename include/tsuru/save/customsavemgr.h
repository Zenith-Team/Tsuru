#pragma once

#include <sead/filedevice.h>
#include <sead/filedevicemgr.h>
#include <sead/safestring.h>
#include <log.h>

class CustomSaveMgr { // This is an abstract base class, inherit it if you would like to add a new save file
protected:
    struct CustomSaveData { // The data for the file, inherit this and add members to store more data, must be aligned to sead::FileDevice::sBufferMinAlignment
    protected:
        CustomSaveData()
            : magic(0xCAFEF00D)
        { }

    public:
        friend class CustomSaveMgr;

        u32 magic;
    };

public:
    CustomSaveMgr(const sead::SafeString& filepath, CustomSaveData* savestruct);

    // Override this to return sizeof the inherited custom save data 
    virtual u32 getSaveDataSize() = 0;
    
    // Override this to set the custom save data to the struct constructor again
    virtual void remakeSaveData() = 0;

    // Writes the current save data pointed to by this->savestruct to the file path
    bool write();

    // Initializes the manager class, and loads the save file
    void init();

    // Just calls write() if the manager has been inited
    void save();

    bool inited;                        // Makes sure that the manager only gets inited once per game launch
    const sead::SafeString filepath;    // Pass the path to the new file (it'll be created there if nonexistent on init)
    CustomSaveData* savestruct;         // Points to the save data structure, must inherit CustomSaveMgr::CustomSaveData
};
