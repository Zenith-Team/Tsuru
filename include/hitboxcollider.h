#pragma once

#include "util/rect.h"
#include "util/vec2.h"
#include "sead.h"

class StageActor;

class HitboxCollider : public sead::IDisposer { // size: 0x128
public:
    typedef void (*Callback)(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    enum Shape {
        ShapeRectangle      = 0,
        ShapeCircle         = 1,
        ShapeTrapezoidVert  = 2,
        ShapeTrapezoidHoriz = 3
    };

    struct Info {
        static Info Default;

        Vec2 distToCenter;  // 0
        Vec2 distToEdge;    // 8
        u32 shape;          // 10
        u32 _14;            // 14
        u32 _18;            // 18
        u32 _1C;            // 1C
        u32 collisionMask;  // 20 (sets allowed collisions, such as colliding with Yoshi)
        u32 flags2;         // 24 (sets allowed interactions, such as being pick-able)
        Callback callback;  // 28
    };

    class List {
    public:
        struct Node {
            HitboxCollider* owner;  // 0
            Node* next;             // 4
            Node* prev;             // 8
        };

    public:
        virtual void insert(Node* where, Node* node);   // C
        virtual void remove(Node* node);                // 14
        virtual void insertBack(Node* node);            // 1C
        virtual void insertFront(Node* node);           // 24
        virtual void clear();                           // 2C

        Node* first;                // 0
        Node* last;                 // 4
    };

    HitboxCollider();
    virtual ~HitboxCollider();

    void init(StageActor* owner, const Info*, void** callbackTable);
    void init(StageActor* owner, const Info*, u8* collisionMask, void** callbackTable);

    f32 getTop();
    f32 getBottom();
    f32 getLeft();
    f32 getRight();
    f32 getCenterX();
    f32 getCenterY();


    void getRect(Rect& outRect);
    static bool collidersOverlap(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    List::Node activeNode;          // 10
    List::Node createNode;          // 1C
    List::Node list3Node;           // 28
    List::Node list4Node;           // 34
    StageActor* owner;              // 40
    u32 _44;                        // 44
    u32 _48;                        // 48
    Vec2 _4C;                       // 4C
    Vec2 _54;                       // 54
    u32 _5C;                        // 5C
    u32 _60;                        // 60
    u32 _64;                        // 64
    u32 _68;                        // 68
    u8 collisionMask;               // 6C
    u8 layer;                       // 6D
    u8 flags;                       // 6E
    void** callbackTable;           // 70
    Info info;                      // 74
    f32 trapezoidTopLeft;           // A0
    f32 trapezoidTopRight;          // A4
    f32 trapezoidBottomLeft;        // A8
    f32 trapezoidBottomRight;       // AC
    f32 _B0[0xF];                   // B0
    f32 _EC[0xF];                   // EC
};

class HitboxColliderMgr : public sead::IDisposer {  // size: 0x40
public:
    bool isInActiveList(HitboxCollider* aCollider);
    void removeFromActiveList(HitboxCollider* aCollider);

    bool isInCreateList(HitboxCollider* aCollider);
    void addToCreateList(HitboxCollider* aCollider);
    void removeFromCreateList(HitboxCollider* aCollider);

    void removeFromList3(HitboxCollider* aCollider);

    inline void add(HitboxCollider* aCollider) {
        if (!isInActiveList(aCollider) && !isInCreateList(aCollider))
            addToCreateList(aCollider);
    }

    inline void remove(HitboxCollider* aCollider) {
        removeFromActiveList(aCollider);
        removeFromCreateList(aCollider);
        removeFromList3(aCollider);
    }

    static HitboxColliderMgr* instance;

    HitboxCollider::List activeList;    // 10
    HitboxCollider::List createList;    // 1C
    HitboxCollider::List list3;         // 28
    HitboxCollider::List list4;         // 34
};