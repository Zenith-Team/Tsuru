#pragma once

#include <sead.h>

class Level {
    SEAD_SINGLETON_DISPOSER(Level)

public:
    class Area {
    public:
        struct Options {
            u32 eventBits32;                // _0
            u32 eventBits64;                // _4
            u16 wrapValue;                  // _8
            u16 timelimit;                  // _A
            u8 _C;                          // _C
            u8 _D;                          // _D
            u8 _E;                          // _E
            u8 _F;                          // _F
            u8 startEntrance;               // _10
            u8 _11;                         // _11
            u8 _12;                         // _12
            u8 startEntranceCoinBoost;      // _13
            u16 timelimit2;                 // _14
            u16 timelimit3;                 // _16
        };

        struct Sprite {
            u16 type;                       // _0
            u16 x;                          // _2
            u16 y;                          // _4
            u16 eventID1_2;                 // _6
            union { u32 settings1;          // _8
                struct {                    // _8
                    u32 nybble12 : 4;       // _8
                    u32 nybble11 : 4;       // _8
                    u32 nybble10 : 4;       // _8
                    u32 nybble9  : 4;       // _8
                    u32 nybble8  : 4;       // _8
                    u32 nybble7  : 4;       // _8
                    u32 nybble6  : 4;       // _8
                    u32 nybble5  : 4;       // _8
                };                          // _8
            };                              // _8
            union { u32 settings2;          // _C
                struct {                    // _C
                    u32 nybble20 : 4;       // _C
                    u32 nybble19 : 4;       // _C
                    u32 nybble18 : 4;       // _C
                    u32 nybble17 : 4;       // _C
                    u32 nybble16 : 4;       // _C
                    u32 nybble15 : 4;       // _C
                    u32 nybble14 : 4;       // _C
                    u32 nybble13 : 4;       // _C
                };                          // _C
            };                              // _C
            u8 zoneID;                      // _10
            u8 layer;                       // _11
            u8 movementID;                  // _12
            u8 linkID;                      // _13
            u8 initialStateFlag;            // _14
        };

        struct Location {
            u16 x;                          // _0
            u16 y;                          // _2
            u16 w;                          // _4
            u16 h;                          // _6
            u8 id;                          // _8
        };

        struct Path {
            u8 id;                          // _0
            s8 _1;                          // _1
            u16 startNodeIdx;               // _2
            u16 nodeCount;                  // _4
            u16 flags;                      // _6 (0b10 -> loops)
            u32 _8;                         // _8
        };

        struct PathNode {
            u16 x;                          // _0
            u16 y;                          // _2
            f32 speed;                      // _4
            f32 accel;                      // _8
            s16 delay;                      // _C
            u16 _E;                         // _E
            u8 _10;                         // _10
            u8 _11;                         // _11
            u8 _12;                         // _12
        };
    
    public:
        Sprite* getSprite(u32 id, void*);
        Location* getLocation(Rect* outRect, u8 id);
        Path* getPath(u8 id);
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
    Area* getArea(u32 id);

    Area areas[4];
};
