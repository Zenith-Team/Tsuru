#pragma once

#include "types.h"

struct CSScriptCommand {
    u32 type;
    u32 arg;
};

struct CSScript {
    u32 priority;
    CSScriptCommand* scriptStart;
};

ENUM_CLASS(CSCommand,
    ShowMiiverseSetup = 311,
    End = 344
);
