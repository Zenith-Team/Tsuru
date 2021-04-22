#pragma once

#include "util/rect.h"
#include "sead.h"


class Level : public sead::IDisposer {  // size: 0xEF0
public:

    class Area {  // size: 0x3B8
    public:
        struct Options {  // size: 0x18
            u32 eventBits32;            // 0
            u32 eventBits64;            // 4
            u16 wrapByte;               // 8
            u16 timelimit;              // A
            u8 _C;                      // C
            u8 _D;                      // D
            u8 _E;                      // E
            u8 _F;                      // F
            u8 startEntrance;           // 10
            u8 _11;                     // 11
            u8 _12;                     // 12
            u8 startEntranceCoinBoost;  // 13
            u16 timelimit2;             // 14
            u16 timelimit3;             // 16
        };

        struct Sprite {  // size: 0x18
            u16 type;         // 0
            u16 x;            // 2
            u16 y;            // 4
            u16 eventId1_2;   // 6
            u32 settings1;    // 8
            u32 settings2;    // C
            u8 zoneId;        // 10
            u8 layer;         // 11
            u8 movementId;    // 12
            u8 linkId;        // 13
            u8 initialState;  // 14
        };

        struct Location {  // size: 0xA
            u16 x;      // 0
            u16 y;      // 2
            u16 w;      // 4
            u16 h;      // 6
            u8 id;      // 8
        };

        struct Zone {  // size: 0x1C
	        u16 x;              // 0
	        u16 y;              // 2
	        u16 w;              // 4
	        u16 h;              // 6
	        u16 theme;          // 8
	        u16 _A;             // A
	        u8 zoneId;          // C
	        u8 boundId;         // D
	        u8 cammode;         // E
	        u8 camzoom;         // F
	        u8 _10;             // 10
	        u8 visibility;      // 11
	        u8 backgroundId;    // 12
	        u8 _13;             // 13
	        u8 _14;             // 14
	        u8 _15;             // 15
	        u8 musicId;         // 16
	        u8 _17;             // 17
	        u8 _18;             // 18
	        u8 _19;             // 19
	        u8 _1A;             // 1A
	        u8 _1B;             // 1B
        };

        struct Path {  // size: 0xC
            u8 id;              // 0
            s8 _1;              // 1
            u16 startNodeIdx;   // 2
            u16 nodeCount;      // 4
            u16 flags;          // 6 (0b10 -> loops)
            u32 _8;             // 8
        };

        struct PathNode {  //? size: 0x14 (0x13 without align)
            u16 x;      // 0
            u16 y;      // 2
            f32 speed;  // 4
            f32 accel;  // 8
            s16 delay;  // C
            u16 _E;     // E
            u8 _10;     // 10
            u8 _11;     // 11
            u8 _12;     // 12
        };

    public:
        Sprite* getSprite(u32 id, void*);
        Location* getLocation(Rect* rectOut, u8 id);
        Path* getPath(u8 id);
        PathNode* getPathNodes(u32 id);

        u32 id;                         // 0
        void* blocks[15];               // 4
        u32 blockSizes[15];             // 40
        u32 blockEntryCounts[15];       // 7C
        u8 _B8[0x100];                  // B8
        u8 _1B8[0x100];                 // 1B8
        u8 _2B8[0x100];                 // 2B8
    };

    Area* getArea(u32 id);

    static Level* instance;

    Area areas[4];
};

class LevelCamera : public sead::IDisposer {  // size:0x
public:		
	static LevelCamera *instance;		
		
	f32 _10;                // 10
	f32 _14;                // 14
	Rect zoneBox;           // 18
	Rect someRects[4];      // 28
	f32 cameraWidth;        // 68
	f32 cameraHeight;       // 6C
	f32 cameraLeft;         // 70
	f32 cameraCenterX;      // 74
	f32 cameraRight;        // 78
	f32 cameraTop;          // 7C
	f32 cameraCenterY;      // 80
	f32 cameraBottom;       // 84
	// TODO: zoom area, scroll limit, etc.		
};

class LevelTimer {
public:
    void setTime(s32 time);
    void addTime(s32 time);
    
    static LevelTimer* instance;
};

class LevelInfo : public sead::IDisposer {  // size: 0x28
public:
    static LevelInfo* instance;

    u8 world;                   // 10
    u8 level;                   // 11
    u8 area;                    // 12
    u8 entrance;                // 13
    u32 zone;                   // 14
    u32 entranceType;           // 18
    u8 destWorld;               // 1C
    u8 destLevel;               // 1D
    u8 destArea;                // 1E
    u8 destEntrance;            // 1F
    u32 destZone;               // 20
    u32 destEntranceType;       // 24
};
