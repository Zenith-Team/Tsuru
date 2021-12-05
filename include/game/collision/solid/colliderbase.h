#pragma once

#include "sead.h"
#include "game/collision/physicsmgr.h"

class ColliderBase : public sead::IDisposer {
public:
    typedef void (*Callback)(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);

    class List {
    public:
        struct Node {
            ColliderBase* owner;   // 0
            Node* next;            // 4
            Node* prev;            // 8
        };

    public:
        virtual void insert(Node* where, Node* node);
        virtual void remove(Node* node);
        virtual void insertBack(Node* node);
        virtual void insertFront(Node* node);
        virtual void clear();

        Node* first;   // 0
        Node* last;    // 4
    };

    class Node {
    public:
        struct Sensor {
            Sensor();

            Vec2f point1;  // 0   Position relative to parent's center, Inited to (0, 0)
            Vec2f point2;  // 8   Position relative to parent's center, Inited to (1, 0)
        };

    public:
        Node();

        u8 _0;              // 0   Inited to 8
        u8 _1;              // 1   Inited to 0
        u8 _2;              // 2   Inited to 0
        u8 _3;              // 3   Inited to 0
        Sensor sensor;      // 4
        u32 _14;            // 14  Inited to 0
        u32 flags;          // 18  Inited to 0
        u32 _1C;            // 1C  Inited to 0
    };

    class Node2 : public Node {
    public:
        ColliderBase* owner;    // 20
        u8  _24[4];             // 24
        u32 flags2;             // 28
        u32 _2C;                // 2C
        u32 _30;                // 30
        u32 _34;                // 34
    };

    struct OwnerInfo {
        Vec3f* position;   // 0
        Vec3f* _4;         // 4
        u8* layer;         // 8
        u8* _C;            // C
        s8* playerID;      // 10
    };

    enum Type {
        Type_Solid                          = 0,
        Type_Coin                           = 1,
        Type_GreenCoin                      = 2,
        Type_BlueCoin                       = 3,
        Type_CoinOutline                    = 4,
        Type_Fence                          = 5,
        Type_Vine                           = 6,
        Type_QuestionBlock                  = 7,
        Type_BrickBlock                     = 8,
        Type_QuestionBlockBig               = 9,
        Type_BrickBlockBig                  = 10,
        Type_BlockUsedBig                   = 11,
        Type_BlockUsed                      = 12,
        Type_Unknown                        = 13,
        Type_WoodStoneBlock                 = 14,
        Type_Unknown2                       = 15,
        Type_DonutBlock                     = 16,
        Type_BoostBlock                     = 17,
        Type_Unknown3                       = 18,
        Type_Water                          = 19,
        Type_Lava                           = 20,
        Type_Poison                         = 21,
        Type_Quicksand                      = 22,
        Type_Carpet                         = 23, // Unused
        Type_Leaves                         = 24, // Used by Palm Tree
        Type_Wood                           = 25, // Used by Floating Barrel
        Type_Unknown4                       = 26, // Used by Bouncy Cloud
        Type_SwingingVine                   = 27,
        Type_SwingingChain                  = 28,
        Type_RopeLadder                     = 29,
        Type_Ice                            = 30,
        Type_Ice2                           = 31, // Used by frozen actors
        Type_Ice3                           = 32, // Used by Portable Ice Block
        Type_Unknown5                       = 33, // Used by Grrrol Passage and Grrrol Spawner
        Type_Unknown6                       = 34,
        Type_Unknown7                       = 35, // Used by Pipe Bubbles
        Type_Unknown8                       = 36, // Used by Airship Hand
        Type_Unknown9                       = 37, // Used by Water Geyser
        Type_Unknown10                      = 38, // Used by Pipes
        Type_Unknown11                      = 39, // Used by Spine Coaster
        Type_Unknown12                      = 40, // Used by Urchin
        Type_InvisibleBlock                 = 41
    };

    enum SolidityType {
        SolidityType_None                   = 0,
        SolidityType_Solid                  = 1,
        SolidityType_SolidOnTop             = 2,
        SolidityType_SolidOnBottom          = 3,
        SolidityType_SolidOnTopAndBottom    = 4,
        SolidityType_Slide                  = 17,
        SolidityType_SteepSlide             = 18,
        SolidityType_Staircase              = 33,
        SolidityType_Staircase2             = 34
    };

    enum SurfaceType {
        SurfaceType_Regular                 = 0,
        SurfaceType_Ice                     = 1,
        SurfaceType_Snow                    = 2,
        SurfaceType_Quicksand               = 3,
        SurfaceType_Sand                    = 4,
        SurfaceType_Grass                   = 5,
        SurfaceType_Cloud                   = 6,
        SurfaceType_BeachSand               = 7, // Unused
        SurfaceType_Carpet                  = 8, // Unused
        SurfaceType_Leaves                  = 9,
        SurfaceType_Wood                    = 10,
        SurfaceType_Water                   = 11,
        SurfaceType_BeanstalkLeaf           = 12
    };

public:
    ColliderBase();
    virtual ~ColliderBase() { }
    SEAD_RTTI_BASE(ColliderBase)
    virtual bool vf24(u32*, u32);
    virtual u32 vf2C(u32*); // deleted
    virtual void vf34() = 0;
    virtual void execute() = 0;
    virtual bool vf44(Node2*, u8*, Vec2f*, Vec2f*, u8) = 0;
    virtual bool vf4C(Node2*, Vec2f*, Vec2f*, s32 sensorID, PhysicsMgr* physicsMgr) = 0;
    virtual bool vf54(u8*, Vec2f*) = 0;
    virtual bool vf5C(u32*) = 0;
    virtual void vf64();
    virtual void vf6C() = 0;
    virtual void vf74(u32*) = 0;
    virtual bool vf7C(Vec2f*, f32) = 0;

    void setType(Type type);
    void setSolidityType(SolidityType solidityType);
    void setSurfaceType(SurfaceType surfaceType);

    List::Node _10[8];          // 10
    Rect rect;                  // 70
    Vec2f _80;                  // 80
    u32 _88;                    // 88
    u32 _8C;                    // 8C
    StageActor* owner;          // 90
    u32 _94;                    // 94
    OwnerInfo ownerInfo;        // 98
    Vec2f distToCenter;         // AC
    Vec2f _B4;                  // B4
    Vec2f _BC;                  // BC
    Vec2f _C4;                  // C4
    Vec2f _CC;                  // CC
    Vec2f _D4;                  // D4
    u32 _DC;                    // DC
    u32 _E0;                    // E0
    Rect _E4;                   // E4   //? Possible Vec4
    u32 rotation;               // F4
    u32 _F8;                    // F8
    List _FC[4];                // FC
    Type type;                  // 12C
    u32 flags;                  // 130
    u32 _134;                   // 134
    Callback topCallback;       // 138  PhysicsMgr Sensor colliding with top of the collider
    Callback bottomCallback;    // 13C  PhysicsMgr Sensor colliding with bottom of the collider
    Callback sideCallback;      // 140  PhysicsMgr Sensor colliding with side of the collider
    void* _144;                 // 144
    void* _148;                 // 148
    void* _14C;                 // 14C
    void** callbackTable;       // 150
    u32 _154;                   // 154
};
