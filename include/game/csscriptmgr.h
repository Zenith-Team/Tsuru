#pragma once

#include <sead.h>
#include <game/csscript.h>
#include <game/actor/actor.h>

class CSScriptMgr { // Size: 0x570
    SEAD_SINGLETON_DISPOSER(CSScriptMgr)

public:
    CSScriptMgr();

    bool isRunningScript();

    u32 getCurrentCommandArg();
    void getCurrentScriptID(u32* out);
    void getCurrentScriptCommandType(u32* out);

    u32 getScriptPriority(u32& tableIndex);

    // Locates an actor from ID at this->_56C and returns a pointer to it
    Actor* FUN_21e4d8c();
    
    u32 FUN_21e4710(void*);
    u32 FUN_21e4e28(void*);

    u8 _10[80][16]; // Array of 16 CLASS_21e5118
    u32 currentScriptID;
    u8 _514[4];
    u8 _518[4][18]; // Array of 18 CLASS_21e50dc
    u32 currentCommandIndex;
    s32 _564;
    u8 _568[4];     // Unknown values
    u32 _56C;       // Some type of Actor ID
};

static_assert(sizeof(CSScriptMgr) == 0x570, "CSScriptMgr size mismatch");
