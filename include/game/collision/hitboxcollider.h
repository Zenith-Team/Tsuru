#pragma once

#include "dynlibs/os/functions.h"
#include "sead/idisposer.h"

class StageActor;

class HitboxCollider : public sead::IDisposer { // Size: 0x128
public:
    typedef void (*Callback)(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    ENUM_CLASS(Shape,
        Rectangle,
        Circle,
        TrapezoidVert,
        TrapezoidHoriz
    );

    ENUM_CLASS(CollisionMask,
        Fireball            = 1 << 1,
        Iceball             = 1 << 2,
        Star                = 1 << 3,
        ButtSlide           = 1 << 5,
        GroundPound         = 1 << 7,
        FencePunch          = 1 << 8,
        ThrowableObject     = 1 << 9,
        PenguinSlide        = 1 << 10,
        PropellerDrill      = 1 << 13,
        Fire2               = 1 << 14,
        Unknown             = 1 << 15, // Possibly eaten by yoshi?
        PipeCannon          = 1 << 17,
        YoshiHammer         = 1 << 19,
        YoshiFireball       = 1 << 20,
        YoshiIceball        = 1 << 21,
    );

    struct Info {

        static Info sDefault;

        Vec2f distToCenter;     // 0
        Vec2f distToEdge;       // 8
        Shape::__type__ shape;  // 10
        u32 _14;                // 14
        u32 _18;                // 18
        u32 _1C;                // 1C
        u32 collisionMask;      // 20  Sets allowed collisions such as colliding with Yoshi
        u32 interactionMask;    // 24  Sets allowed interactions such as being pickup-able
        Callback callback;      // 28
    
        void set(const Vec2f& distToCenter, const Vec2f& distToEdge, Shape::__type__ shape, u32 _14, u32 _18, u32 _1C, u32 collisionMask, u32 interactionMask, Callback callback) {
            this->distToCenter = distToCenter;
            this->distToEdge = distToEdge;
            this->shape = shape;
            this->_14 = _14;
            this->_18 = _18;
            this->_1C = _1C;
            this->collisionMask = collisionMask;
            this->interactionMask = interactionMask;
            this->callback = callback;
        }
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
    SEAD_SINGLETON_DISPOSER(HitboxColliderMgr);

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

    inline void safeAddToCreateList(HitboxCollider* hc) {
        if (!this->isInActiveList(hc) && !this->isInCreateList(hc)) {
            this->addToCreateList(hc);
        }
    }

    HitboxCollider::List activeList;    // 10
    HitboxCollider::List createList;    // 1C
    HitboxCollider::List _28;           // 28
    HitboxCollider::List _34;           // 34
};
