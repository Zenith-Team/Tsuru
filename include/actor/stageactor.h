#pragma once

#include "actor/baseactor.h"
#include "hitboxcollider.h"
#include "eatdata.h"
#include "util/vec3u.h"

extern u32 directionToRotationList[];

class ColliderBase;
class CollisionMgr;

class StageActor : public BaseActor {  // size: 0x27C
    SEAD_RTTI_OVERRIDE(StageActor, BaseActor)

public:
    struct CallbackTable {
        typedef bool (StageActor::*typeAcCallbackB)(HitboxCollider*, Vec2*);
        typedef void (StageActor::*typeAcCallbackV)(HitboxCollider*, Vec2*);
        typedef bool (StageActor::*typeCbCallbackB)(ColliderBase*, Vec2*);
        typedef void (StageActor::*typeCbCallbackV)(ColliderBase*, Vec2*);

        void (StageActor::*root)();                               // nullptr
        typeAcCallbackB acCallback0;
        typeAcCallbackB acCallback1;
        typeAcCallbackB acCallback2;
        typeAcCallbackV acCallback3;
        typeAcCallbackV acCallback4;
        typeCbCallbackB cbCallback0;
        typeCbCallbackB cbCallback1;
        typeCbCallbackB cbCallback2;
        typeCbCallbackV cbCallback3;
        typeCbCallbackV cbCallback4;
    };

public:
    StageActor(const ActorBuildInfo* buildInfo);
    virtual ~StageActor();

    void afterCreate(u32) override;
    u32 beforeExecute() override;
    void afterExecute(u32) override;
    u32 beforeDraw() override;

    virtual void setPlayerId(s8 id) {
        playerId = id;
    }

    virtual void removeHitboxColliders();
    virtual void addHitboxColliders();

    virtual CollisionMgr* getCollisionMgr() {
        return nullptr;
    }

    virtual void vfAC() { }

    virtual bool vfB4() {
        return true;
    }

    virtual void vfBC() { }

    virtual void vfC4() { }

    virtual void vfCC() { }

    virtual void killAtGoal();
    virtual void splashWater(Vec3*);
    virtual void splashLava(Vec3*);
    virtual void splashLavaWave(Vec3*);
    virtual void splashPoison(Vec3*);
    virtual bool isOffScreen();

    virtual void damageFromUnder() { }

    s32 distanceToPlayer(Vec2& out);
    u8 directionToPlayerH(const Vec3& position);
    u8 directionToPlayerV(const Vec3& position);
    u8 directionToActorH(const StageActor& other);
    void cullCheck(u32 unkMask = 0);
    bool deleteActorWhenOutOfView(u32);

    bool actorAcCallback0(HitboxCollider*, Vec2*);
    bool actorAcCallback1(HitboxCollider*, Vec2*);
    bool actorAcCallback2(HitboxCollider*, Vec2*);
    void actorAcCallback3(HitboxCollider*, Vec2*);
    void actorAcCallback4(HitboxCollider*, Vec2*);
    bool actorCbCallback0(ColliderBase*, Vec2*);
    bool actorCbCallback1(ColliderBase*, Vec2*);
    bool actorCbCallback2(ColliderBase*, Vec2*);
    void actorCbCallback3(ColliderBase*, Vec2*);
    void actorCbCallback4(ColliderBase*, Vec2*);

    u32 direction;                        // 50   Inited to 0
    s8 playerId;                          // 54   Inited to -1
    s8 controllerLytPlayerId;             // 55   Inited to -1
    u8 layer;                             // 56   Inited to buildInfo->layer
    u8 collisionMask;                     // 57   Inited to 1
    f32 xSpeed;                           // 58   Inited to 0
    f32 _5C;                              // 5C   Inited to 0
    f32 fallSpeed;                        // 60   Inited to 0
    f32 gravity;                          // 64   Inited to 0
    f32 xAccel;                           // 68   Inited to 0
    Vec3 position;                        // 6C
    Vec3 speed;                           // 78   Inited to 0
    Vec3 maxSpeed;                        // 84   Inited to 0
    Vec3 scale;                           // 90   Inited to 1.0
    Vec3u rotation;                       // 9C   Inited to 0
    u32 _A8;                              // A8   Inited to 0
    u32 _AC;                              // AC   Inited to 0
    u32 rotDelta;                         // B0   Inited to 0
    Vec2 posDelta;                        // B4   Inited to 0
    HitboxCollider aCollider;             // BC
    Vec2 visibleAreaOffset;               // 1E4  Inited to actorInfo->spawnRangeOffset
    Vec2 visibleAreaSize;                 // 1EC  Inited to actorInfo->spawnRangeSize
    Vec2 size;                            // 1F4
    f32 rectQ_0;                          // 1FC  Inited to 256.0 + actorInfo->_18
    f32 rectQ_1;                          // 200  Inited to 256.0 + actorInfo->_1A
    f32 destroyBoundDistanceLeft;         // 204  Inited to  80.0 + actorInfo->_1C
    f32 destroyBoundDistanceRight;        // 208  Inited to  80.0 + actorInfo->_1E
    u8 zoneId;                            // 20C
    u8 type;                              // 20D  0: Actor, 1: Player, 2: Yoshi, 3: Enemy, 4: Unknown
    bool isActive;                        // 20E  Inited to true
    bool isVisible;                       // 20F  Inited to true
    bool noRespawn;                       // 210  Inited to false
    u8 _211;                              // 211  Inited to 1
    u8 _212;                              // 212  Inited to 0
    u8 eventId1;                          // 213
    u8 eventId2;                          // 214
    u16 actorInfoFlags;                   // 215  Inited to actorInfo->flags
    u32 bumpDamageTimer;                  // 218  Inited to 0
    u32 _21C;                             // 21C  Inited to 0
    u32 _220;                             // 220  Inited to 0
    u32 _224;                             // 224  Inited to 0
    u32 _228;                             // 228  Inited to 0
    u32 killStreak;                       // 22C  Inited to 0
    u32 profileFlags;                     // 230  Inited to profile->flags
    Vec3 positionOffset;                  // 234  Inited to 0
    Vec3 _240;                            // 240  Inited to position
    Vec3 _24C;                            // 24C  Inited to position
    Vec3 _258;                            // 258  Inited to position
    YoshiEatData* pYoshiEatData;          // 264  Inited to o
    BabyYoshiEatData* pBabyYoshiEatData;  // 268  Inited to o
    u32 _26C;                             // 26C  Inited to o
    u8* _270;                             // 270  Inited to buildInfo->_28
    f32 _274;                             // 274  Inited to 0
    void* pBabyYoshiBubbleData;           // 278  Inited to o
};
