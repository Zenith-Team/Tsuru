#pragma once

#include "sead/idisposer.h"

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
            u32 settings1;                  // 8
            u32 settings2;                  // C
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
        Sprite* getSprite(u32 id, Sprite*);
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
