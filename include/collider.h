#pragma once

#include "sead.h"
#include "util/rect.h"
#include "util/vec2.h"

class StageActor;
class CollisionMgr;

class ColliderBase : public sead::IDisposer {  // size: 0x158
public:
    typedef void (*Callback)(ColliderBase* cSelf, CollisionMgr* otherMgr, u32 sensorId);

    class List {
    public:
        struct Node {
            ColliderBase* owner;    // 0
            Node* next;             // 4
            Node* prev;             // 8
        };

    public:
        virtual void insert(Node* where, Node* node);   // C
        virtual void remove(Node* node);                // 14
        virtual void insertBack(Node* node);            // 1C
        virtual void insertFront(Node* node);           // 24
        virtual void clear();                           // 2C

        Node* first;            // 0
        Node* last;             // 4
    };


    class Node {
    public:
        struct Sensor {
            Sensor();

            Vec2 p1;       // 0    Position relative to parent's center, Inited to (0, 0)
            Vec2 p2;       // 8    Position relative to parent's center, Inited to (1, 0)
        };

    public:
        Node();

        u8 _0;             // 0    Inited to 8
        u8 _1;             // 1    Inited to 0
        u8 _2;             // 2    Inited to 0
        u8 _3;             // 3    Inited to 0

        Sensor sensor;     // 4    Sub class

        u32 _14;           // 14   Inited to 0
        u32 flags;         // 18   Inited to 0
        u32 _1C;           // 1C   Inited to 0
    };

    class Node2 : public Node {
    public:
        ColliderBase* owner;  // 20
        u8 _24[4];            // 24
        u32 flags2;           // 28
        u32 _2C;              // 2C
        u32 _30;              // 30
        u32 _34;              // 34
    };

    struct OwnerInfo {
        Vec3* position;  // 0
        Vec3* _4;        // 4
        u8* layer;       // 8
        u8* _C;          // C
        s8* playerId;    // 10
    };

    enum Types {
        TypeSolid               = 0,
        TypeCoin                = 1,
        TypeGreenCoin           = 2,
        TypeBlueCoin            = 3,
        TypeCoinOutline         = 4,
        TypeFence               = 5,
        TypeVine                = 6,
        TypeQuestionBlock       = 7,
        TypeBrickBlock          = 8,
        TypeQuestionBlockBig    = 9,
        TypeBrickBlockBig       = 10,
        TypeBlockUsedBig        = 11,
        TypeBlockUsed           = 12,
        TypeUnknown             = 13,
        TypeWoodStoneBlock      = 14,
        TypeUnknown2            = 15,
        TypeDonutBlock          = 16,
        TypeBoostBlock          = 17,
        TypeUnknown3            = 18,
        TypeWater               = 19,
        TypeLava                = 20,
        TypePoison              = 21,
        TypeQuicksand           = 22,
        TypeCarpet              = 23, // Unused
        TypeLeaves              = 24, // Used by Palm Tree
        TypeWood                = 25, // Used by Floating Barrel
        TypeUnknown4            = 26, // Used by Bouncy Cloud
        TypeSwingingVine        = 27,
        TypeSwingingChain       = 28,
        TypeRopeLadder          = 29,
        TypeIce                 = 30,
        TypeIce2                = 31, // Used by frozen actors
        TypeIce3                = 32, // Used by Portable Ice Block
        TypeUnknown5            = 33, // Used by Grrrol Passage and Grrrol Spawner
        TypeUnknown6            = 34,
        TypeUnknown7            = 35, // Used by Pipe Bubbles
        TypeUnknown8            = 36, // Used by Airship Hand
        TypeUnknown9            = 37, // Used by Water Geyser
        TypeUnknown10           = 38, // Used by Pipes
        TypeUnknown11           = 39, // Used by Spine Coaster
        TypeUnknown12           = 40, // Used by Urchin
        TypeInvisibleBlock      = 41
    };

    enum SolidityTypes {
        SolidityTypeNone                = 0,
        SolidityTypeSolid               = 1,
        SolidityTypeSolidOnTop          = 2,
        SolidityTypeSolidOnBottom       = 3,
        SolidityTypeSolidOnTopAndBottom = 4,
        SolidityTypeSlide               = 17,
        SolidityTypeSteepSlide          = 18,
        SolidityTypeStaircase           = 33,
        SolidityTypeStaircase2          = 34
    };

    enum SurfaceTypes {
        SurfaceTypeRegular       = 0,
        SurfaceTypeIce           = 1,
        SurfaceTypeSnow          = 2,
        SurfaceTypeQuicksand     = 3,
        SurfaceTypeSand          = 4,
        SurfaceTypeGrass         = 5,
        SurfaceTypeCloud         = 6,
        SurfaceTypeBeachSand     = 7, // Unused
        SurfaceTypeCarpet        = 8, // Unused
        SurfaceTypeLeaves        = 9,
        SurfaceTypeWood          = 10,
        SurfaceTypeWater         = 11,
        SurfaceTypeBeanstalkLeaf = 12
    };

public:
    ColliderBase();
    virtual ~ColliderBase();

    SEAD_RTTI_BASE(ColliderBase)

    virtual bool vf24(u32*, u32); // TODO: Define
    virtual u32 vf2C(u32*);       // deleted
    virtual void vf34() = 0;
    virtual void execute() = 0;
    virtual bool vf44(Node2*, u8*, Vec2*, Vec2*, u8) = 0;
    virtual bool vf4C(Node2*, Vec2*, Vec2*, s32 sensorId, CollisionMgr* collisionMgr) = 0;
    virtual bool vf54(u8*, Vec2*) = 0;
    virtual bool vf5C(u32*) = 0;
    virtual void vf64();
    virtual void vf6C() = 0;
    virtual void vf74(u32*) = 0;
    virtual bool vf7C(Vec2*, f32) = 0;

    void setType(Types type);
    void setSolidity(SolidityTypes solidity);
    void setSurfaceType(SurfaceTypes surfaceType);

    List::Node _10[8];          // 10
    Rect rect;                  // 70
    Vec2 _80;                   // 80
    u32 _88;                    // 88
    u32 _8C;                    // 8C
    StageActor* owner;          // 90
    u32 _94;                    // 94
    OwnerInfo ownerInfo;        // 98
    Vec2 distToCenter;          // AC
    Vec2 _B4;                   // B4
    Vec2 _BC;                   // BC
    Vec2 _C4;                   // C4
    Vec2 _CC;                   // CC
    Vec2 _D4;                   // D4
    u32 _DC;                    // DC
    u32 _E0;                    // E0
    Rect _E4;                   // E4 Vec4, maybe?
    u32 rotation;               // F4
    u32 _F8;                    // F8
    List _FC[4];                // FC
    Types type;                 // 12C
    u32 flags;                  // 130
    u32 _134;                   // 134
    Callback topCallback;       // 138 CollisionMgr Sensor colliding with top of the collider
    Callback bottomCallback;    // 13C CollisionMgr Sensor colliding with bottom of the collider
    Callback sideCallback;      // 140 CollisionMgr Sensor colliding with side of the collider
    void* _144;                 // 144
    void* _148;                 // 148
    void* _14C;                 // 14C
    void** callbackTable;       // 150
    u32 _154;                   // 154
};

class ShapedCollider : public ColliderBase {  // size: 0x170
    SEAD_RTTI_OVERRIDE(ShapedCollider, ColliderBase)

public:
    struct Info {
        Vec2 distToCenter;  // 0
        f32 _8;             // 8
        f32 _C;             // C
        Vec2 topLeft;       // 10
        Vec2 bottomRight;   // 18
        u32 rotation;       // 20

    };

public:
    ShapedCollider();
    ShapedCollider(s32 numPoints, Vec2* points, Node* nodes1, Node* nodes2);
    virtual ~ShapedCollider();

    void init(StageActor* owner, const Info& info);

    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, Vec2*, Vec2*, u8) override;
    bool vf4C(Node2*, Vec2*, Vec2*, s32 sensorId, CollisionMgr* collisionMgr) override;
    bool vf54(u8*, Vec2*) override;
    bool vf5C(u32*) override; // deleted
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(Vec2*, f32) override;

    virtual void vf84();

    void setRect(Vec2* topLeft, Vec2* bottomRight);

    sead::Buffer<Vec2> points;
    sead::Buffer<Node> nodes1;
    sead::Buffer<Node> nodes2;
};


class RectCollider : public ShapedCollider {  // size: 0x290
    SEAD_RTTI_OVERRIDE(RectCollider, ShapedCollider)

public:
    forceinline RectCollider()
        : ShapedCollider(4, points, nodes[0], nodes[1])
    {
        for (u32 i = 0; i < 4; i++) {
            points[i].x = 0.0f;
            points[i].y = 0.0f;
        }

        for (u32 i = 0; i < 4; i++) {
            nodes[0][i].flags = flags;
            nodes[0][i]._1C = _134;
            nodes[1][i].flags = flags;
            nodes[1][i]._1C = _134;
        }
    }

    virtual ~RectCollider() { }

    bool vf54(u8*, Vec2*) override;

    Vec2 points[4];             // 170
    Node nodes[2][4];           // 190
};


class SolidOnTopCollider : public ColliderBase {  // size: 0x178
    SEAD_RTTI_OVERRIDE(SolidOnTopCollider, ColliderBase)

public:
    struct Info {
        Vec2 distToCenter;  // 0
        f32 _8;             // 8
        f32 _C;             // C
        Vec2* points;       // 10
        u32 rotation;       // 14
    };

public:
    SolidOnTopCollider();
    SolidOnTopCollider(s32 numPoints, Vec2* points, Node* nodes1, Node* nodes2);
    virtual ~SolidOnTopCollider();

    void init(StageActor* owner, const Info& info);
    void init(StageActor* owner, const Info& info, s32 numPoints, sead::Heap* heap = nullptr);

    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, Vec2*, Vec2*, u8) override;
    bool vf4C(Node2*, Vec2*, Vec2*, s32 sensorId, CollisionMgr* collisionMgr) override;
    bool vf54(u8*, Vec2*) override;
    bool vf5C(u32*) override;
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(Vec2*, f32) override;

    sead::Buffer<Vec2> points;
    sead::Buffer<Node> nodes1;
    sead::Buffer<Node> nodes2;
    f32 _170;
    u8 _174[0x178-0x174];
};

class CircularCollider : public ColliderBase {  // size: 0x190
    SEAD_RTTI_OVERRIDE(CircularCollider, ColliderBase)

public:
    struct Info {
        Vec2 distToCenter;  // 0
        Vec2 _8;            // 8
        Vec2 _10;           // 10
        f32 radius;         // 18
        u32 rotation;       // 1C
    };

public:
    CircularCollider();
    virtual ~CircularCollider();

    void init(StageActor* owner, const Info& info);

    bool vf24(u32*, u32) override;
    u32 vf2C(u32*) override;
    void vf34() override;
    void execute() override;
    bool vf44(Node2*, u8*, Vec2*, Vec2*, u8) override;
    bool vf4C(Node2*, Vec2*, Vec2*, s32 sensorId, CollisionMgr* collisionMgr) override;
    bool vf54(u8*, Vec2*) override;
    bool vf5C(u32*) override;
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(Vec2*, f32) override;

    Vec2 _158;
    Vec2 _160;
    Vec2 _168;
    f32 radius;
    u8 _174[0x190-0x174];
};

class ColliderMgr : public sead::IDisposer {  // size: 0x64
public:
    void add(ColliderBase* collider);
    void remove(ColliderBase* collider);

    static ColliderMgr* instance;

    ColliderBase::List lists[7];    // 10
};
