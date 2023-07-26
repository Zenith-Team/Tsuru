#pragma once

#include "types.h"

class TileDataInfo
{
public:
    enum Kind
    {
        // ---------- Common ---------- //

        Kind_Normal            = 0,
        Kind_Rail              = 1,
        Kind_CoinOutline       = 2,
        Kind_Coin              = 3,
        Kind_CoinBlue          = 4,
        Kind_Block             = 5,
        Kind_BrickBlock        = 6,
        Kind_QuestionBlock     = 7,
        Kind_RedBlockOutline   = 8,
        Kind_PartialBlock      = 9,
        Kind_InvisibleBlock    = 10,
        Kind_Slope             = 11,
        Kind_ReverseSlope      = 12,
        Kind_Liquid            = 13,
        Kind_Climbable         = 14,   // Vine, Fence and Climbable wall with ledge
        Kind_Damage            = 15,
        Kind_Pipe              = 16,
        Kind_ConveyorBelt      = 17,
        Kind_DonutBlock        = 18,
        Kind_CaveEntrance      = 19,
        Kind_Ledge             = 20,
        Kind_Rope              = 21,
        Kind_Pole              = 22,

        // ------ Game--specific ------ //

        Kind_PoleRope          = 23,   // Swinging chain/vine and Rope ladder
        Kind_BreakableIce      = 24,
        Kind_GrrrolPassage     = 25,
        Kind_StreamCurrent     = 26,
        Kind_Carpet            = 27,
        Kind_Leaves            = 28,
        Kind_Wood              = 29,
        Kind_Cloud             = 30,
        Kind_BoostBlock        = 31,
        Kind_AirshipHand       = 32,
        Kind_WaterGeyser       = 33,
        Kind_BrickBlockBig     = 34,
        Kind_QuestionBlockBig  = 35,
        Kind_BlockUsedBig      = 36,
        Kind_RemoLiftElevator  = 37,
        Kind_SpineCoaster      = 38,
        Kind_Urchin            = 39
    };

    enum SolidType
    {
        SolidType_None             = 0,    // Collision is not solid
        SolidType_Fill             = 1,    // Collision is completely solid                        (filled)
        SolidType_Outer            = 2,    // Collision is solid on the outer surface              (line)
        SolidType_Inner            = 3,    // Collision is solid on the inner surface              (line)
        SolidType_OuterAndInner    = 4     // Collision is solid on the outer and inner surfaces   (line)
    };

    enum SlideType
    {
        SlideType_Normal   = 0,    // Player can slide while colliding when crouching
        SlideType_Slide    = 1,    // Player instantly enters sliding state when colliding
        SlideType_NoSlide  = 2     // Player cannot slide while colliding
    };

    enum SurfaceType
    {
        Surfacetype_Normal         = 0,
        Surfacetype_Ice            = 1,
        Surfacetype_Snow           = 2,
        Surfacetype_Quicksand      = 3,
        Surfacetype_Sand           = 4,
        Surfacetype_Grass          = 5,
        Surfacetype_Cloud          = 6,
        Surfacetype_BeachSand      = 7,    // Unused
        Surfacetype_Carpet         = 8,    // Unused
        Surfacetype_Leaves         = 9,
        Surfacetype_Wood           = 10,
        Surfacetype_Water          = 11,
        Surfacetype_BeanstalkLeaf  = 12
    };

public:
    TileDataInfo()
        : data(0)
    {
    }

    TileDataInfo(u64 dataV)
        : data(dataV)
    {
    }

    u64 getData() const
    {
        return data;
    }

    void setData(u64 dataV)
    {
        data = dataV;
    }

    // -------------------------------------

    u64 getUnitType() const
    {
        return data & 0xFFFFFFFFF;
    }

    Kind getUnitKind() const
    {
        return Kind(data & 0xFFFF);
    }

    u8 getUnitParam0() const
    {
        return (data >> 16) & 0xFF;
    }

    u8 getUnitParam1() const
    {
        return (data >> 24) & 0xFF;
    }

    SolidType getUnitSolidType() const
    {
        return SolidType((data >> 32) & 0xF);
    }

    // -------------------------------------

    SlideType getUnitSlideType() const
    {
        return SlideType((data >> 36) & 0xF);
    }

    SurfaceType getUnitSurfaceType() const
    {
        return SurfaceType((data >> 40) & 0xFF);
    }

private:
    u64 data;  // SolidType == 1: Ignore active camera
};
static_assert(sizeof(TileDataInfo) == 0x8);
