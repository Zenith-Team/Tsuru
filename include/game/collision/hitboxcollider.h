#pragma once

#include "sead.h"
#include "types.h"

class StageActor;

class HitboxCollider : public sead::IDisposer { // size: 0x128
public:
    typedef void (*Callback)(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);

    enum HitboxShape {
        Rectangle      = 0,
        Circle         = 1,
        TrapezoidVert  = 2,
        TrapezoidHoriz = 3
    };

    struct Info {
        static Info sDefault;

        Vec2f mDistToCenter;    // _0
        Vec2f mDistToEdge;      // _8
        HitboxShape mShape;     // _10
        u32 _14;                // _14
        u32 _18;                // _18
        u32 _1C;                // _1C
        u32 mCollisionMask;     // _20  Sets allowed collisions such as colliding with Yoshi
        u32 mInteractionMask;   // _24  Sets allowed interactions such as being pickup-able
        Callback mCallback;     // _28
    };

    class List {
    public:
        struct Node {
            HitboxCollider* mOwner;     // _0
            Node* mNext;                // _4
            Node* mPrev;                // _8
        };

        virtual void insert(Node *, Node *); // _C
        virtual void remove(Node *);         // _14
        virtual void insertBack(Node *);     // _1C
        virtual void insertFront(Node *);    // _24
        virtual void clear();                // _2C

        Node* mFirst;   // _0
        Node* mLast;    // _4
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
    static bool sCollidersOverlap(HitboxCollider* pHCSelf, HitboxCollider* pHCOther);

    List::Node mActiveNode;     // _10
    List::Node mCreateNode;     // _1C
    List::Node _28;             // _28
    List::Node _34;             // _34
    StageActor* mOwner;         // _40
    u32 _44;                    // _44
    u32 _48;                    // _48
    Vec2f _4C;                  // _4C
    Vec2f _54;                  // _54
    u32 _5C;                    // _5C
    u32 _60;                    // _60
    u32 _64;                    // _64
    u32 _68;                    // _68
    u8 mCollisionMask;          // _6C
    u8 mLayer;                  // _6D
    u8 mFlags;                  // _6E
    u8 _6F;                     // _6F  Padding?
    void** mCallbackTable;      // _70
    Info mColliderInfo;         // _74
    f32 mTrapezoidTopLeft;      // _A0
    f32 mTrapezoidTopRight;     // _A4
    f32 mTrapezoidBottomLeft;   // _A8
    f32 mTrapezoidBottomRight;  // _AC
    f32 _B0[0xF];               // _B0
    f32 _EC[0xF];               // _EC
};

class HitboxColliderMgr : public sead::IDisposer { // Size: 0x40
public:
    // Constructor is inlined in HitboxCollider::createInstance
    inline HitboxColliderMgr();
    
    virtual ~HitboxColliderMgr();

    static void createInstance(sead::Heap*);

    bool isInActiveList(HitboxCollider*);
    bool isInCreateList(HitboxCollider*);

    void addToCreateList(HitboxCollider*);

    void removeFromActiveList(HitboxCollider*);
    void removeFromCreateList(HitboxCollider*);
    void removeFromList3(HitboxCollider*);

    static HitboxColliderMgr* sInstance;

    HitboxCollider::List mActiveList; // _10
    HitboxCollider::List mCreateList; // _1C
    HitboxCollider::List _28;         // _28
    HitboxCollider::List _34;         // _34
};
