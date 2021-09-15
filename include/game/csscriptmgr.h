#pragma once

#include <sead.h>
#include <game/csscript.h>
#include <game/actor/actor.h>

class CSScriptMgr {
    SEAD_SINGLETON_DISPOSER(CSScriptMgr)

public:
    CSScriptMgr();

    void getScriptPointer(CSScript& out);
    u32 getScriptPriority(u32& tableIndex);

    bool FUN_21e3d8c();     // Returns "this->field_0x510 != 0"
    u32 FUN_21e4afc();      // Returns a value related to args
    void FUN_21e4b68(u32*);
    Actor* FUN_21e4d8c();   // Locates an actor from ID at this->_56C and returns a pointer to it
    u32 FUN_21e4710(void*);
    u32 FUN_21e4e28(void*);
    
};
