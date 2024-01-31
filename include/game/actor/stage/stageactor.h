#pragma once

#include "game/eatdata.h"
#include "game/actor/actor.h"
#include "game/collision/hitboxcollider.h"
#include "game/collision/actorphysicsmgr.h"
#include "game/direction.h"

class ColliderBase;
class StageActor;

struct StageActorCallbackTable {
    typedef bool (StageActor::*typeHCCallbackB)(HitboxCollider*, sead::Vector2f*);
    typedef void (StageActor::*typeHCCallbackV)(HitboxCollider*, sead::Vector2f*);
    typedef bool (StageActor::*typeCBCallbackB)(ColliderBase*, sead::Vector2f*);
    typedef void (StageActor::*typeCBCallbackV)(ColliderBase*, sead::Vector2f*);

    void (StageActor::*root)(); // nullptr
    typeHCCallbackB hcCallback0;
    typeHCCallbackB hcDRCTouchCallback; // Boost mode/gamepad touch
    typeHCCallbackB hcCallback2;
    typeHCCallbackV hcCallback3;
    typeHCCallbackV hcCallback4;
    typeCBCallbackB cbCallback0;
    typeCBCallbackB cbCallback1;
    typeCBCallbackB cbCallback2;
    typeCBCallbackV cbCallback3;
    typeCBCallbackV cbCallback4;
};

class StageActor : public Actor {
    SEAD_RTTI_OVERRIDE_DECL(StageActor, Actor);

public:
    ENUM_CLASS(Type,
        Actor,
        Player,
        Yoshi,
        Enemy,
        BabyYoshi,

        // Custom types
        Boss
    );

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
    // @return Pointer to the ActorPhysicsMgr instance for this actor
    virtual ActorPhysicsMgr* getActorPhysicsMgr();
    virtual void vfAC();
    virtual bool vfB4();
    virtual void vfBC();
    virtual void vfC4();
    virtual void vfCC();
    virtual void killAtGoal();
    virtual void splashWater(sead::Vector3f*);
    virtual void splashLava(sead::Vector3f*);
    virtual void splashLavaWave(sead::Vector3f*);
    virtual void splashPoison(sead::Vector3f*);
    virtual bool isOffScreen();
    virtual void damageFromUnder();

    s32 distanceToPlayer(sead::Vector2f& out);
    u8 directionToPlayerH(const sead::Vector3f& position);
    u8 directionToPlayerV(const sead::Vector3f& position);
    u8 directionToActorH(const StageActor& other);

    sead::Vector2f distanceToPlayer() {
        sead::Vector2f out;
        this->distanceToPlayer(out);
        return out;
    }

    void cullCheck(u32 unkMask = 0);
    bool offscreenDelete(u32 unkMask = 0);

    bool actorHCCallback0(HitboxCollider*, sead::Vector2f*);
    bool actorHCCallback1(HitboxCollider*, sead::Vector2f*);
    bool actorHCCallback2(HitboxCollider*, sead::Vector2f*);
    void actorHCCallback3(HitboxCollider*, sead::Vector2f*);
    void actorHCCallback4(HitboxCollider*, sead::Vector2f*);
    bool actorCBCallback0(ColliderBase*, sead::Vector2f*);
    bool actorCBCallback1(ColliderBase*, sead::Vector2f*);
    bool actorCBCallback2(ColliderBase*, sead::Vector2f*);
    void actorCBCallback3(ColliderBase*, sead::Vector2f*);
    void actorCBCallback4(ColliderBase*, sead::Vector2f*);

    sead::Vector2f get2DPosition() const {
        return sead::Vector2f(this->position.x, this->position.y);
    }

    u32 direction;                      // 50      Inited to 0
    s8  playerID;                       // 54      Inited to -1
    s8  controllerPlayerID;             // 55      Inited to -1
    u8  layer;                          // 56      Inited to buildInfo->layer
    u8  collisionMask;                  // 57      Inited to 1
    f32 xSpeed;                         // 58      Inited to 0
    f32 _5C;                            // 5C      Inited to 0
    f32 fallSpeed;                      // 60      Inited to 0
    f32 gravity;                        // 64      Inited to 0
    f32 xAcceleration;                  // 68      Inited to 0
    sead::Vector3f position;            // 6C
    sead::Vector3f speed;               // 78      Inited to 0
    sead::Vector3f maxSpeed;            // 84      Inited to 0
    sead::Vector3f scale;               // 90      Inited to 1.0
    sead::Vector3u rotation;            // 9C      Inited to 0
    u32 _A8;                            // A8      Inited to 0
    u32 _AC;                            // AC      Inited to 0
    u32 rotationDelta;                  // B0      Inited to 0
    sead::Vector2f positionDelta;       // B4      Inited to 0
    HitboxCollider hitboxCollider;      // BC
    sead::Vector2f visibleAreaOffs;     // 1E4     Inited to actorInfo->spawnRangeOffset
    sead::Vector2f visibleAreaSize;     // 1EC     Inited to actorInfo->spawnRangeSize
    sead::Vector2f size;                // 1F4
    f32 _1FC;                           // 1FC     Inited to 256.0 + actorInfo->_18
    f32 _200;                           // 200     Inited to 256.0 + actorInfo->_1A
    f32 _204;                           // 204     Inited to 80.0 + actorInfo->_1C
    f32 _208;                           // 208     Inited to 80.0 + actorInfo->_1E
    u8  zoneID;                         // 20C
    u8  type;                           // 20D     0: Actor, 1: Player, 2: Yoshi, 3: Enemy, 4: Unknown, 5: Boss
    bool isActive;                      // 20E     Inited to true
    bool isVisible;                     // 20F     Inited to true
    bool noSpawn;                       // 210     Inited to false
    u8  _211;                           // 211     Inited to 1
    u8  _212;                           // 212     Inited to 0
    u8  eventID2;                       // 213
    u8  eventID1;                       // 214
    u8  _215;                           // 215
    u16 actorInfoFlags;                 // 216     Inited to actorInfo->flags
    u32 bumpDamageTimer;                // 218     Inited to 0
    u32 _21C;                           // 21C     Inited to 0
    u32 _220;                           // 220     Inited to 0
    u32 _224;                           // 224     Inited to 0
    u32 _228;                           // 228     Inited to 0
    u32 killStreak;                     // 22C     Inited to 0
    u32 profileFlags;                   // 230     Inited to profile->flags
    sead::Vector3f positionOffset;      // 234     Inited to 0
    sead::Vector3f _240;                // 240     Inited to position
    sead::Vector3f _24C;                // 24C     Inited to position
    sead::Vector3f _258;                // 258     Inited to position
    YoshiEatData* yoshiEatData;         // 264
    BabyYoshiEatData* babyYoshiData;    // 268
    u32 _26C;                           // 26C
    u8* _270;                           // 270     buildInfo->_28
    f32 _274;                           // 274     Inited to 0
    void* babyYoshiBubbleData;          // 278
};
