#pragma once

#include <sead.h>
#include <types.h>

class StageActor;

class HitboxCollider : public sead::IDisposer { // size: 0x128
public:
    typedef void (*Callback)(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    enum HitboxShape {
        ShapeRectangle      = 0,
        ShapeCircle         = 1,
        ShapeTrapezoidVert  = 2,
        ShapeTrapezoidHoriz = 3
    };

    struct Info {
        static Info sDefault;

        Vec2f distToCenter;     // _0
        Vec2f distToEdge;       // _8
        HitboxShape shape;      // _10
        u32 _14;                // _14
        u32 _18;                // _18
        u32 _1C;                // _1C
        u32 collisionMask;      // _20  Sets allowed collisions such as colliding with Yoshi
        u32 interactionMask;    // _24  Sets allowed interactions such as being pickup-able
        Callback callback;      // _28
    };

    class List {
    public:
        struct Node {
            HitboxCollider* owner;     // _0
            Node* next;                // _4
            Node* prev;                // _8
        };

        virtual void insert(Node*, Node*); // _C
        virtual void remove(Node*);         // _14
        virtual void insertBack(Node*);     // _1C
        virtual void insertFront(Node*);    // _24
        virtual void clear();                // _2C

        Node* first;   // _0
        Node* last;    // _4
    };

    HitboxCollider();
    virtual ~HitboxCollider();

    void init(StageActor* owner, const Info*, void** callbackTable);
    void init(StageActor* owner, const Info*, u8* collisionMask, void** callbackTable);
    
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

    List::Node activeNode;      // _10
    List::Node createNode;      // _1C
    List::Node _28;             // _28
    List::Node _34;             // _34
    StageActor* owner;          // _40
    u32 _44;                    // _44
    u32 _48;                    // _48
    Vec2f _4C;                  // _4C
    Vec2f _54;                  // _54
    u32 _5C;                    // _5C
    u32 _60;                    // _60
    u32 _64;                    // _64
    u32 _68;                    // _68
    u8 collisionMask;           // _6C
    u8 layer;                   // _6D
    u8 flags;                   // _6E
    u8 _6F;                     // _6F  //? Maybe padding
    void** callbackTable;       // _70
    Info colliderInfo;          // _74
    f32 trapezoidTopLeft;       // _A0
    f32 trapezoidTopRight;      // _A4
    f32 trapezoidBottomLeft;    // _A8
    f32 trapezoidBottomRight;   // _AC
    f32 _B0[0xF];               // _B0
    f32 _EC[0xF];               // _EC
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

    HitboxCollider::List activeList; // _10
    HitboxCollider::List createList; // _1C
    HitboxCollider::List _28;         // _28
    HitboxCollider::List _34;         // _34
};
