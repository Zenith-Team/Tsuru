#pragma once

#include "types.h"
#include "tiles.h"


class TileMgr {
public:
    static u16* getTilePtr(u16 x, u16 y, u32 area, u8 layer, u32* blockIndexOut = nullptr);
    static u16* getTilePtrCurrentArea(u16 x, u16 y, u8 layer, u32* blockIndexOut = nullptr);

    static TileMgr* instance;
};
