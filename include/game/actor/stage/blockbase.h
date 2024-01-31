#pragma once

#include "game/actor/stage/multistateactor.h"
#include "game/collision/solid/rectcollider.h"
#include "game/movementhandler.h"

class BlockAndCoinBase : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_DECL(BlockAndCoinBase, MultiStateActor);

public:
    ENUM_CLASS(Content,
        FireMushroom = 0,
        MiniMushroom = 1,
        LifeMushroom = 2,
        Mushroom = 3,
        FireFlower = 4,
        IceMushroom = 5,
        PenguinMushroom = 6,
        PropellerMushroom = 7,
        Star = 8,
        ContinuousStar = 9,
        SquirrelMushroom = 10,
        LifeMoon = 11,
        Coin = 12,
        MultiCoin = 13,
        Vine = 15,
        Yoshi = 16,
        Spring = 17,
        MushroomIfSmall = 19,
        Nothing = 21
    );

public:
    BlockAndCoinBase(const ActorBuildInfo* buildInfo);
    virtual ~BlockAndCoinBase();

    void spawnPortableSpring();
    void spawnYoshiEgg(bool multi);
    void spawnVine();
    void spawnPowerup(const sead::Vector3f& pos, u32, u32, bool spawnAsChild);
    void spawnMultiPowerup(const sead::Vector3f& pos, u32, u32, bool spawnAsChild);

    virtual void vf18C();
    virtual void vf194();
    virtual void setBelowSensor();
    virtual void vf1A4();
    virtual void spawnItemUp();
    virtual void vf1B4();
    virtual void vf1BC();
    virtual void spawnItemDown();
    virtual void vf1CC();
    virtual void vf1D4(bool);
    virtual u32 vf1DC();
    virtual void spawnCoinShower();
    virtual void vf1EC();

    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BumpUp);
    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BlockAndCoinBaseState2);
    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BumpDown);
    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BlockAndCoinBaseState4);
    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BumpUp2);
    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BumpDown2);
    DECLARE_STATE_VIRTUAL(BlockAndCoinBase, BlockAndCoinBaseState7);

    PhysicsMgr::Sensor _17C8;
    u8 _17D4[4];
    RectCollider rectCollider;
    sead::Vector2f _1A68;
    sead::Vector2f _1A70;
    f32 _1A78;
    f32 _1A7C;
    f32 _1A80;
    f32 _1A84;
    f32 _1A88;
    f32 _1A8C;
    u32 _1A90;
    u32 _1A94;
    s32 _1A98;
    u32 _1A9C;
    u16 _1AA0;
    u16 _1AA2;
    u16 _1AA4;
    u8 _1AA6;
    u8 _1AA7;
    s8 _1AA8;
    s8 _1AA9;
    u8 _1AAA;
    u8 _1AAB;
    u8 _1AAC;
    u8 _1AAD;
    u8 _1AAE;
    u8 _1AAF;
    u8 _1AB0;
    u8 _1AB1;
    u8 playerID2;
    u8 _1AB3;
    u32 _1AB4;
    Content::__type__ content;
    u32 hitPlayerID;
    u32 spawnDirection;
    u8 _1AC4;
    u32 _1AC8;
    u8 _1ACC;
    u8 _1ACD;
    u8 _1ACE;
    u8 _1ACF;
    f32 _1AD0;
    f32 _1AD4;
    f32 _1AD8;
    u32 _1ADC;
    u32 _1AE0;
    u32 _1AE4;
    u32 _1AE8;
    u32 _1AEC;
    s8 _1AF0[48];
    u8 _1A20;
    u32 _1B24;
};

class MovementBlockAndCoinBase : public BlockAndCoinBase {
    SEAD_RTTI_OVERRIDE_DECL(MovementBlockAndCoinBase, BlockAndCoinBase);

public:
    MovementBlockAndCoinBase(const ActorBuildInfo* buildInfo);
    virtual ~MovementBlockAndCoinBase();

    void spawnItemUp() override;
    void spawnItemDown() override;
    u32 vf1DC() override;

    virtual void vf29C();
    virtual void setTileFlag();
    virtual u32 vf2AC();
    virtual void vf2B4();
    virtual void vf2BC();
    virtual bool vf2C4();
    virtual void vf2CC();

    bool registerColliderActiveInfo();

    PhysicsMgr::Sensor belowSensor;
    sead::Vector3f posForState;
    MovementHandler movementHandler;
    u8 colliderActiveInfo[0x28];
    sead::Vector2f colliderActiveAreaSize;
    u32 _1C68;
    u8 _1C6C[4];
    u32 tileId;
    u32 movementType;
    u32 moverId;
    u8 _1C7C[0x1CA0 - 0x1C7C];
    StageActorCallbackTable* callbackTable;
    u8 _1CA4[4];
};

class BlockBase : public MovementBlockAndCoinBase {
    SEAD_RTTI_OVERRIDE_DECL(BlockBase, MovementBlockAndCoinBase);

public:
    ENUM_CLASS(StateType,
        QuestionBlock,
        BrickBlock,
        UsedBlock,
        InvisibleBlock
    );

public:
    BlockBase(const ActorBuildInfo* buildInfo);
    virtual ~BlockBase();

    static void activeTopCollisionCallback(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);
    static void activeBottomCollisionCallback(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);
    static void activeSideCollisionCallback(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);

    static void usedTopCollisionCallback(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);
    static void usedBottomCollisionCallback(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);
    static void usedSideCollisionCallback(ColliderBase* cSelf, PhysicsMgr* otherMgr, u32 sensorID);

    bool init(bool registerCollider, bool);
    void initMovementHandler();

    u32 onExecute() override;
    u32 onDraw() override;

    void setBelowSensor() override;
    void spawnItemUp() override;
    void spawnItemDown() override;
    void vf1CC() override;
    void vf1EC() override;

    bool vf2C4() override;

    virtual bool isActive();
    virtual void vf2DC();
    virtual u8 getContent();
    virtual void vf2EC();
    virtual void vf2F4(void*);
    virtual void execute();
    virtual void destroy();
    virtual void destroy2();
    virtual void vf314();
    virtual void vf31C();
    virtual void vf324();
    virtual u32 vf32C();

    DECLARE_STATE_VIRTUAL(BlockBase, Active);
    DECLARE_STATE_VIRTUAL(BlockBase, Used);

    f32 _1CA8;
    f32 _1CAC;
    f32 _1CB0;
    f32 _1CB4;
    f32 _1CB8;
    StateType::__type__ stateType;
    u32 _1CC0;
    u8 _1CC4;
    u8 _1CC5;
    u8 _1CC6;
    u32 _1CC8;
    u8 _1CCC;
    u8 _1CCD;
};
