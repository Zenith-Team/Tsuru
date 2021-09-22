#pragma once

#include <sead.h>
#include <game/csscript.h>
#include <game/actor/actor.h>

class CSScriptMgr {
    SEAD_SINGLETON_DISPOSER(CSScriptMgr)

public:
    CSScriptMgr();

    bool isRunningScript();

    u32 getCurrentCommandArg();
    void getCurrentScriptID(u32* out);
    void getCurrentScriptCommandType(u32* out);

    u32 getScriptPriority(u32& tableIndex);

    Actor* FUN_21e4d8c(); // Locates an actor from ID at this->_56C and returns a pointer to it
    u32 FUN_21e4710(void*);
    u32 FUN_21e4e28(void*);

    u8 _0[0x510];
    u32 currentScriptID;
    u8 _514[0x560 - 0x514];
    u32 currentCommandIndex;
};
