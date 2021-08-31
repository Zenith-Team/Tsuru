#pragma once

#include <types.h>

// "FFL" handles Mii related stuff
namespace FFL {
    struct AuthorID { // Size: 0x8
        u16 _0;
        u16 _2;
        u16 _4;
        u16 _6;
    };

    struct CreateIDBase { // Size: 0x6
        u8 _0;
        u8 _1;
        u8 _2;
        u8 _3;
        u16 authorIdCRC16;
    };

    struct CreateID { // Size: 0xA
        u8 flags;
        u8 _1;
        u8 _2;
        u8 index;
        CreateIDBase createIdBase;
    };

    struct MiiDataCore { // Size: 0x48
         u32 _0;
         AuthorID authorID; // 4
         CreateID createId; // C
         u8 _16[2];
         u16 _18;
         wchar_t miiName[10];   // 1A
         u8 _2E;
         u8 _2F;
         u32 _30;
         u32 _34;
         u32 _38;
         u32 _3C;
         u32 _40;
         u32 _44;
    };

    struct MiiData { // Size: 0x5C
        MiiDataCore miiDataCore;
        wchar_t creatorName[10];
    };

    // A complete Mii character object
    struct StoreData { // Size: 0x60
        MiiData miiData; // 0
        u16 _5C;         // 5C
        u16 CRC16;       // 5E
    };
}
