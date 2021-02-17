#pragma once

#include "util/rect.h"
#include "util/vec2.h"
#include "sead.h"

class Actor;

class ActiveCollider : public sead::IDisposer   // size: 0x128
{
public:
    typedef void (*Callback)(ActiveCollider* acSelf, ActiveCollider* acOther);

    enum Shape
    {
        ShapeRectangle      = 0,
        ShapeCircle         = 1,
        ShapeTrapezoidVert  = 2,
        ShapeTrapezoidHoriz = 3
    };

    struct Info
    {
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

    class List
    {
    public:
        struct Node
        {
            ActiveCollider* owner;  // 0
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

    ActiveCollider();
    virtual ~ActiveCollider();

    void init(Actor* owner, const Info*, void** callbackTable);
    void init(Actor* owner, const Info*, u8* collisionMask, void** callbackTable);

    f32 getTop();
    f32 getBottom();
    f32 getLeft();
    f32 getRight();
    f32 getCenterX();
    f32 getCenterY();


    void getRect(Rect& outRect);
    static bool collidersOverlap(ActiveCollider* acSelf, ActiveCollider* acOther);

    List::Node activeNode;  // 10
    List::Node createNode;  // 1C
    List::Node list3Node;   // 28
    List::Node list4Node;   // 34
    Actor* owner;           // 40
    u32 _44;
    u32 _48;
    Vec2 _4C;
    Vec2 _54;
    u32 _5C;
    u32 _60;
    u32 _64;
    u32 _68;
    u8 collisionMask;
    u8 layer;
    u8 flags;
    void** callbackTable;
    Info info;                      // 74
    f32 trapezoidTopLeft;           // A0
    f32 trapezoidTopRight;          // A4
    f32 trapezoidBottomLeft;        // A8
    f32 trapezoidBottomRight;       // AC
    f32 _B0[0xF];
    f32 _EC[0xF];
};
