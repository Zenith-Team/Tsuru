#pragma once

#include <game/eatdata.h>
#include <game/actor/actor.h>
#include <game/collision/hitboxcollider.h>
#include <game/collision/actorphysicsmgr.h>

class ColliderBase;

class StageActor : public Actor {
    SEAD_RTTI_OVERRIDE(StageActor, Actor)

public:
    enum StageActorType {
        StageActorType_Actor    = 0,
        StageActorType_Player   = 1,
        StageActorType_Yoshi    = 2,
        StageActorType_Enemy    = 3,
        StageActorType_Unknown  = 4
    };

public:
    struct CallbackTable {
        typedef bool (StageActor::*typeHCCallbackB)(HitboxCollider*, Vec2f*);
        typedef void (StageActor::*typeHCCallbackV)(HitboxCollider*, Vec2f*);
        typedef bool (StageActor::*typeCBCallbackB)(ColliderBase*, Vec2f*);
        typedef void (StageActor::*typeCBCallbackV)(ColliderBase*, Vec2f*);

        void (StageActor::*root)(); // nullptr
        typeHCCallbackB hcCallback0;
        typeHCCallbackB hcCallback1;
        typeHCCallbackB hcCallback2;
        typeHCCallbackV hcCallback3;
        typeHCCallbackV hcCallback4;
        typeCBCallbackB cbCallback0;
        typeCBCallbackB cbCallback1;
        typeCBCallbackB cbCallback2;
        typeCBCallbackV cbCallback3;
        typeCBCallbackV cbCallback4;
    };

public:
    StageActor(const ActorBuildInfo* buildInfo);
    virtual ~StageActor();

    void afterCreate(u32) override;

    u32 beforeExecute() override;
    void afterExecute(u32) override;

    u32 beforeDraw() override;

    virtual void setPlayerID(s8 id);
    virtual void removeHitboxColliders();
    virtual void addHitboxColliders();
    virtual ActorPhysicsMgr* getActorPhysicsMgr();
    virtual void vfAC();
    virtual bool vfB4();
    virtual void vfBC();
    virtual void vfC4();
    virtual void vfCC();
    virtual void killAtGoal();
    virtual void splashWater(Vec3f*);
    virtual void splashLava(Vec3f*);
    virtual void splashLavaWave(Vec3f*);
    virtual void splashPoison(Vec3f*);
    virtual bool isOffScreen();
    virtual void damageFromUnder();

    s32 distanceToPlayer(Vec2f& out);
    u8 directionToPlayerH(const Vec3f& position);
    u8 directionToPlayerV(const Vec3f& position);
    u8 directionToActorH(const StageActor& other);

    void cullCheck(u32 unkMask = 0);
    bool deleteActorWhenOutOfView(u32);

    bool actorHCCallback0(HitboxCollider*, Vec2f*);
    bool actorHCCallback1(HitboxCollider*, Vec2f*);
    bool actorHCCallback2(HitboxCollider*, Vec2f*);
    void actorHCCallback3(HitboxCollider*, Vec2f*);
    void actorHCCallback4(HitboxCollider*, Vec2f*);
    bool actorCBCallback0(ColliderBase*, Vec2f*);
    bool actorCBCallback1(ColliderBase*, Vec2f*);
    bool actorCBCallback2(ColliderBase*, Vec2f*);
    void actorCBCallback3(ColliderBase*, Vec2f*);
    void actorCBCallback4(ColliderBase*, Vec2f*);

    u32 direction;                      // _50      Inited to 0
    s8  playerID;                       // _54      Inited to -1
    s8  controllerPlayerID;             // _55      Inited to -1
    u8  layer;                          // _56      Inited to buildInfo->layer
    u8  collisionMask;                  // _57      Inited to 1
    f32 xSpeed;                         // _58      Inited to 0
    f32 _5C;                            // _5C      Inited to 0
    f32 fallSpeed;                      // _60      Inited to 0
    f32 gravity;                        // _64      Inited to 0
    f32 xAcceleration;                  // _68      Inited to 0
    Vec3f position;                     // _6C
    Vec3f speed;                        // _78      Inited to 0
    Vec3f maxSpeed;                     // _84      Inited to 0
    Vec3f scale;                        // _90      Inited to 1.0
    Vec3u rotation;                     // _9C      Inited to 0
    u32 _A8;                            // _A8      Inited to 0
    u32 _AC;                            // _AC      Inited to 0
    u32 rotationDelta;                  // _B0      Inited to 0
    Vec2f positionDelta;                // _B4      Inited to 0
    HitboxCollider hitboxCollider;      // _BC
    Vec2f visibleAreaOffs;              // _1E4     Inited to actorInfo->spawnRangeOffset
    Vec2f visibleAreaSize;              // _1EC     Inited to actorInfo->spawnRangeSize
    Vec2f size;                         // _1F4
    f32 _1FC;                           // _1FC     Inited to 256.0 + actorInfo->_18
    f32 _200;                           // _200     Inited to 256.0 + actorInfo->_1A
    f32 _204;                           // _204     Inited to 80.0 + actorInfo->_1C
    f32 _208;                           // _208     Inited to 80.0 + actorInfo->_1E
    u8  zoneID;                         // _20C
    u8  type;                           // _20D     0: Actor, 1: Player, 2: Yoshi, 3: Enemy, 4: Unknown
    bool isActive;                      // _20E     Inited to true
    bool isVisible;                     // _20F     Inited to true
    bool noSpawn;                       // _210     Inited to false
    u8  _211;                           // _211     Inited to 1
    u8  _212;                           // _212     Inited to 0
    u8  eventID1;                       // _213
    u8  eventID2;                       // _214
    u8  _215;                           // _215
    u16 actorInfoFlags;                 // _216     Inited to actorInfo->flags
    u32 bumpDamageTimer;                // _218     Inited to 0
    u32 _21C;                           // _21C     Inited to 0
    u32 _220;                           // _220     Inited to 0
    u32 _224;                           // _224     Inited to 0
    u32 _228;                           // _228     Inited to 0
    u32 killStreak;                     // _22C     Inited to 0
    u32 profileFlags;                   // _230     Inited to profile->flags
    Vec3f positionOffset;               // _234     Inited to 0
    Vec3f _240;                         // _240     Inited to position
    Vec3f _24C;                         // _24C     Inited to position
    Vec3f _258;                         // _258     Inited to position
    YoshiEatData* yoshiEatData;         // _264
    BabyYoshiEatData* babyYoshiData;    // _268
    u32 _26C;                           // _26C
    u8* _270;                           // _270     buildInfo->_28
    f32 _274;                           // _274     Inited to 0
    void* babyYoshiBubbleData;          // _278
};
