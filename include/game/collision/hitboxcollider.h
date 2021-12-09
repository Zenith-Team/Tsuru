#pragma once

#include "sead.h"
#include "types.h"

class StageActor;

class HitboxCollider : public sead::IDisposer { // Size: 0x128
public:
    typedef void (*Callback)(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    enum HitboxShape {
        HitboxShape_Rectangle      = 0,
        HitboxShape_Circle         = 1,
        HitboxShape_TrapezoidVert  = 2,
        HitboxShape_TrapezoidHoriz = 3
    };

    struct Info {
        static Info sDefault;

        Vec2f distToCenter;     // 0
        Vec2f distToEdge;       // 8
        HitboxShape shape;      // 10
        u32 _14;                // 14
        u32 _18;                // 18
        u32 _1C;                // 1C
        u32 collisionMask;      // 20  Sets allowed collisions such as colliding with Yoshi
        u32 interactionMask;    // 24  Sets allowed interactions such as being pickup-able
        Callback callback;      // 28
    };

    class List {
    public:
        struct Node {
            HitboxCollider* owner;     // 0
            Node* next;                // 4
            Node* prev;                // 8
        };

        virtual void insert(Node*, Node*);  // C
        virtual void remove(Node*);         // 14
        virtual void insertBack(Node*);     // 1C
        virtual void insertFront(Node*);    // 24
        virtual void clear();               // 2C

        Node* first;   // 0
        Node* last;    // 4
    };

    HitboxCollider();
    virtual ~HitboxCollider();

    // Initializes the collider
    // @param owner Pointer to owner of the collider
    // @param info Pointer to collider info struct
    void init(StageActor* owner, const Info* info, void** callbackTable = nullptr);
    // Initializes the collider
    // @param owner Pointer to owner of the collider
    // @param info Pointer to collider info struct
    void init(StageActor* owner, const Info* info, u8* collisionMask, void** callbackTable);

    void moveToOnlyCreate(u32);
    void moveToOnlyCreateFromMask(u32);
    bool checkBit(u32) const;

    f32 getTopY() const;
    f32 getBottomY() const;
    f32 getCenterY() const;
    f32 getRightX() const;
    f32 getLeftX() const;
    f32 getCenterX() const;

    // Custom functions
    void getRect(Rect& outRect);
    static bool sCollidersOverlap(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    List::Node activeNode;      // 10
    List::Node createNode;      // 1C
    List::Node _28;             // 28
    List::Node _34;             // 34
    StageActor* owner;          // 40
    u32 _44;                    // 44
    u32 _48;                    // 48
    Vec2f _4C;                  // 4C
    Vec2f _54;                  // 54
    u32 _5C;                    // 5C
    u32 _60;                    // 60
    u32 _64;                    // 64
    u32 _68;                    // 68
    u8 collisionMask;           // 6C
    u8 layer;                   // 6D
    u8 flags;                   // 6E
    u8 _6F;                     // 6F  //? Maybe padding
    void** callbackTable;       // 70
    Info colliderInfo;          // 74
    f32 trapezoidTopLeft;       // A0
    f32 trapezoidTopRight;      // A4
    f32 trapezoidBottomLeft;    // A8
    f32 trapezoidBottomRight;   // AC
    f32 _B0[0xF];               // B0
    f32 _EC[0xF];               // EC
};

class HitboxColliderMgr { // Size: 0x40
    SEAD_SINGLETON_DISPOSER(HitboxColliderMgr)

public:
    // Constructor is inlined in HitboxCollider::createInstance
    inline HitboxColliderMgr();

    virtual ~HitboxColliderMgr();

    bool isInActiveList(HitboxCollider*);
    bool isInCreateList(HitboxCollider*);

    void addToCreateList(HitboxCollider*);

    void removeFromActiveList(HitboxCollider*);
    void removeFromCreateList(HitboxCollider*);
    void removeFromList3(HitboxCollider*);

    HitboxCollider::List activeList;    // 10
    HitboxCollider::List createList;    // 1C
    HitboxCollider::List _28;           // 28
    HitboxCollider::List _34;           // 34
};
