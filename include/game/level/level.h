#pragma once

#include <sead.h>

class Level {
    SEAD_SINGLETON_DISPOSER(Level)

public:
    class Area {
    public:
        struct Options {
            u32 mEventBits32;               // _0
            u32 mEventBits64;               // _4
            u16 mWrapByte;                  // _8
            u16 mTimelimit;                 // _A
            u8 _C;                          // _C
            u8 _D;                          // _D
            u8 _E;                          // _E
            u8 _F;                          // _F
            u8 mStartEntrance;              // _10
            u8 _11;                         // _11
            u8 _12;                         // _12
            u8 mStartEntranceCoinBoost;     // _13
            u16 mTimelimit2;                // _14
            u16 mTimelimit3;                // _16
        };

        struct Sprite {
            u16 mType;                      // _0
            u16 mX;                         // _2
            u16 mY;                         // _4
            u16 mEventID1_2;                // _6
            union { u32 mSettings1;
                struct {
                    u32 nybble12 : 4;
                    u32 nybble11 : 4;
                    u32 nybble10 : 4;
                    u32 nybble9  : 4;
                    u32 nybble8  : 4;
                    u32 nybble7  : 4;
                    u32 nybble6  : 4;
                    u32 nybble5  : 4;
                };
            };
            union { u32 mSettings2;
                struct {
                    u32 nybble20 : 4;
                    u32 nybble19 : 4;
                    u32 nybble18 : 4;
                    u32 nybble17 : 4;
                    u32 nybble16 : 4;
                    u32 nybble15 : 4;
                    u32 nybble14 : 4;
                    u32 nybble13 : 4;
                };
            };
            u8 mZoneID;                     // _10
            u8 mLayer;                      // _11
            u8 mMovementID;                 // _12
            u8 mLinkID;                     // _13
            u8 mInitialStateFlag;           // _14
        };

        struct Location {
            u16 mX;                         // _0
            u16 mY;                         // _2
            u16 mW;                         // _4
            u16 mH;                         // _6
            u8 mID;                         // _8
        };

        struct Path {
            u8 mID;                         // _0
            s8 _1;                          // _1
            u16 mStartNodeIdx;              // _2
            u16 mNodeCount;                 // _4
            u16 mFlags;                     // _6 (0b10 -> loops)
            u32 _8;                         // _8
        };

        struct PathNode {
            u16 mX;                         // _0
            u16 mY;                         // _2
            f32 mSpeed;                     // _4
            f32 mAccel;                     // _8
            s16 mDelay;                     // _C
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

        u32 mID;                            // 0
        void* mBlocks[15];                  // 4
        u32 mBlockSizes[15];                // 40
        u32 mBlockEntryCounts[15];          // 7C
        u8 _B8[0x100];                      // B8
        u8 _1B8[0x100];                     // 1B8
        u8 _2B8[0x100];                     // 2B8
    };

public:
    Area* getArea(u32 id);

    Area mAreas[4];
};
