#pragma once

#include "sead.h"

class Level {
    SEAD_SINGLETON_DISPOSER(Level)

public:
    class Area {
    public:
        struct Options {
            u32 eventBits32;                // 0
            u32 eventBits64;                // 4
            u16 wrapValue;                  // 8
            u16 timeLimit;                  // A
            u8 _C;                          // C
            u8 _D;                          // D
            u8 _E;                          // E
            u8 _F;                          // F
            u8 startEntrance;               // 10
            u8 _11;                         // 11
            u8 _12;                         // 12
            u8 startEntranceCoinBoost;      // 13
            u16 timeLimit2;                 // 14
            u16 timeLimit3;                 // 16
        };

        struct Sprite {
            u16 id;                         // 0
            u16 x;                          // 2
            u16 y;                          // 4
            u16 eventID1_2;                 // 6
            union { u32 settings1;          // 8
                struct {                    // 8
                    u32 nybble12 : 4;       // 8
                    u32 nybble11 : 4;       // 8
                    u32 nybble10 : 4;       // 8
                    u32 nybble9  : 4;       // 8
                    u32 nybble8  : 4;       // 8
                    u32 nybble7  : 4;       // 8
                    u32 nybble6  : 4;       // 8
                    u32 nybble5  : 4;       // 8
                };                          // 8
            };                              // 8
            union { u32 settings2;          // C
                struct {                    // C
                    u32 nybble20 : 4;       // C
                    u32 nybble19 : 4;       // C
                    u32 nybble18 : 4;       // C
                    u32 nybble17 : 4;       // C
                    u32 nybble16 : 4;       // C
                    u32 nybble15 : 4;       // C
                    u32 nybble14 : 4;       // C
                    u32 nybble13 : 4;       // C
                };                          // C
            };                              // C
            u8 zoneID;                      // 10
            u8 layer;                       // 11
            u8 movementID;                  // 12
            u8 linkID;                      // 13
            u8 initialStateFlag;            // 14
        };

        struct Location {
            u16 x;                          // 0
            u16 y;                          // 2
            u16 w;                          // 4
            u16 h;                          // 6
            u8 id;                          // 8
        };

        struct Path {
            u8 id;                          // 0
            s8 _1;                          // 1
            u16 startNodeIdx;               // 2
            u16 nodeCount;                  // 4
            u16 flags;                      // 6 (0b10 -> loops)
            u32 _8;                         // 8
        };

        struct PathNode {
            u16 x;                          // 0
            u16 y;                          // 2
            f32 speed;                      // 4
            f32 accel;                      // 8
            s16 delay;                      // C
            u16 _E;                         // E
            u8 _10;                         // 10
            u8 _11;                         // 11
            u8 _12;                         // 12
        };

    public:
        // @param id Target sprite ID
        // @return Pointer to the retrieved sprite
        Sprite* getSprite(u32 id, Sprite*);

        // @param outRect Output rect which represents the location
        // @param id Target location ID
        // @return Pointer to the retrieved location
        Location* getLocation(Rect* outRect, u8 id);

        // @param id Target path ID
        // @return Pointer to the retrieved path
        Path* getPath(u8 id);

        // @param id Target path node ID
        // @return Pointer to the retrieved path node
        PathNode* getPathNodes(u32 id);

        u32 id;                             // 0
        void* blocks[15];                   // 4
        u32 blockSizes[15];                 // 40
        u32 blockEntryCounts[15];           // 7C
        u8 _B8[0x100];                      // B8
        u8 _1B8[0x100];                     // 1B8
        u8 _2B8[0x100];                     // 2B8
    };

public:

    // @param id Target area ID
    // @return Pointer to the retrieved area
    Area* getArea(u32 id);

    Area areas[4];
};
