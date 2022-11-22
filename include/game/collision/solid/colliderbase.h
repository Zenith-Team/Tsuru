#pragma once

#include "game/collision/physicsmgr.h"
#include "sead/runtimetypeinfo.h"
#include "sead/idisposer.h"

struct StageActorCallbackTable;

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

    ENUM_CLASS(Type,
        Solid                          = 0,
        Coin                           = 1,
        GreenCoin                      = 2,
        BlueCoin                       = 3,
        CoinOutline                    = 4,
        Fence                          = 5,
        Vine                           = 6,
        QuestionBlock                  = 7,
        BrickBlock                     = 8,
        QuestionBlockBig               = 9,
        BrickBlockBig                  = 10,
        BlockUsedBig                   = 11,
        BlockUsed                      = 12,
        Unknown                        = 13,
        WoodStoneBlock                 = 14,
        Unknown2                       = 15,
        DonutBlock                     = 16,
        BoostBlock                     = 17,
        Unknown3                       = 18,
        Water                          = 19,
        Lava                           = 20,
        Poison                         = 21,
        Quicksand                      = 22,
        Carpet                         = 23, // Unused
        Leaves                         = 24, // Used by Palm Tree
        Wood                           = 25, // Used by Floating Barrel
        Bouncy                         = 26, // Used by Bouncy Cloud
        SwingingVine                   = 27,
        SwingingChain                  = 28,
        RopeLadder                     = 29,
        Ice                            = 30,
        Ice2                           = 31, // Used by frozen actors
        Ice3                           = 32, // Used by Portable Ice Block
        Unknown5                       = 33, // Used by Grrrol Passage and Grrrol Spawner
        Unknown6                       = 34,
        Unknown7                       = 35, // Used by Pipe Bubbles
        Unknown8                       = 36, // Used by Airship Hand
        Unknown9                       = 37, // Used by Water Geyser
        Unknown10                      = 38, // Used by Pipes
        Unknown11                      = 39, // Used by Spine Coaster
        Unknown12                      = 40, // Used by Urchin
        InvisibleBlock                 = 41
    );

    ENUM_CLASS(SolidityType,
        None                            = 0,
        Solid                           = 1,
        SolidOnTop                      = 2,
        SolidOnBottom                   = 3,
        SolidOnTopAndBottom             = 4,
        Slide                           = 17,
        SteepSlide                      = 18,
        Staircase                       = 33,
        Staircase2                      = 34
    );

    ENUM_CLASS(SurfaceType,
        Regular                         = 0,
        Ice                             = 1,
        Snow                            = 2,
        Quicksand                       = 3,
        Sand                            = 4,
        Grass                           = 5,
        Cloud                           = 6,
        BeachSand                       = 7, // Unused
        Carpet                          = 8, // Unused
        Leaves                          = 9,
        Wood                            = 10,
        Water                           = 11,
        BeanstalkLeaf                   = 12
    );

public:
    ColliderBase();
    virtual ~ColliderBase() { }
    SEAD_RTTI_BASE(ColliderBase);
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

    void setType(Type::__type__ type);
    void setSolidityType(SolidityType::__type__ solidityType);
    void setSurfaceType(SurfaceType::__type__ surfaceType);

    List::Node _10[8];                          // 10
    Rect rect;                                  // 70
    Vec2f _80;                                  // 80
    u32 _88;                                    // 88
    u32 _8C;                                    // 8C
    StageActor* owner;                          // 90
    u32 _94;                                    // 94
    OwnerInfo ownerInfo;                        // 98
    Vec2f distToCenter;                         // AC
    Vec2f _B4;                                  // B4
    Vec2f _BC;                                  // BC
    Vec2f _C4;                                  // C4
    Vec2f _CC;                                  // CC
    Vec2f _D4;                                  // D4
    u32 _DC;                                    // DC
    u32 _E0;                                    // E0
    Rect _E4;                                   // E4   //? Possible Vec4
    u32 rotation;                               // F4
    u32 _F8;                                    // F8
    List _FC[4];                                // FC
    Type::__type__ type;                        // 12C
    u32 flags;                                  // 130
    u32 _134;                                   // 134
    Callback topCallback;                       // 138  PhysicsMgr Sensor colliding with top of the collider
    Callback bottomCallback;                    // 13C  PhysicsMgr Sensor colliding with bottom of the collider
    Callback sideCallback;                      // 140  PhysicsMgr Sensor colliding with side of the collider
    void* _144;                                 // 144
    void* _148;                                 // 148
    void* _14C;                                 // 14C
    StageActorCallbackTable** callbackTable;   // 150
    u32 _154;                                   // 154
};
