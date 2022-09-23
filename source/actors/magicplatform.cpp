#include "game/actor/stage/stageactor.h"
#include "game/movementhandler.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/solid/solidontopcollider.h"
#include "game/collision/collidermgr.h"
#include "game/level/level.h"
#include "game/level/levelinfo.h"
#include "game/tilemgr.h"
#include "sead/mathcalccommon.h"
#include "game/graphics/drawmgr.h"
#include "log.h"

class MagicPlatform : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(MagicPlatform, StageActor);

public:
    MagicPlatform(const ActorBuildInfo* buildInfo);
    virtual ~MagicPlatform() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    // Callback table
    bool mpHCCallback1(HitboxCollider*, Vec2f*) { return false; }
    void mpHCCallback3(HitboxCollider*, Vec2f*) { }
    void mpHCCallback4(HitboxCollider*, Vec2f*) { }
    bool mpCBCallback1(ColliderBase*, Vec2f*)   { return true; }
    void mpCBCallback3(ColliderBase*, Vec2f*)   { }
    void mpCBCallback4(ColliderBase*, Vec2f*)   { }

    u16* tileData;
    Vec2u tileSize;
    MovementHandler movementHandler;
    u8 collisionType;
    RectCollider rectCollider;
    StageActorCallbackTable* callbackTable;
    SolidOnTopCollider solidOnTopCollider;
};

const ActorInfo MagicPlatformActorInfo = {
    Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0), 0, 0, 0, 0, ActorInfo::Flags::IgnoreSpawnRange | ActorInfo::Flags::Unknown1
};

const Profile MagicPlatformProfile(&MagicPlatform::build, ProfileID::MagicPlatform, "MagicPlatform", &MagicPlatformActorInfo);

StageActorCallbackTable MagicPlatformCallbackTable = {
                                                         (nullptr),
    static_cast<StageActorCallbackTable::typeHCCallbackB>(&StageActor::actorHCCallback0),
    static_cast<StageActorCallbackTable::typeHCCallbackB>(&MagicPlatform::mpHCCallback1),
    static_cast<StageActorCallbackTable::typeHCCallbackB>(&StageActor::actorHCCallback2),
    static_cast<StageActorCallbackTable::typeHCCallbackV>(&MagicPlatform::mpHCCallback3),
    static_cast<StageActorCallbackTable::typeHCCallbackV>(&MagicPlatform::mpHCCallback4),
    static_cast<StageActorCallbackTable::typeCBCallbackB>(&StageActor::actorCBCallback0),
    static_cast<StageActorCallbackTable::typeCBCallbackB>(&MagicPlatform::mpCBCallback1),
    static_cast<StageActorCallbackTable::typeCBCallbackB>(&StageActor::actorCBCallback2), // TODO: TwoWayPlatform::twpCBCallback2
    static_cast<StageActorCallbackTable::typeCBCallbackV>(&MagicPlatform::mpCBCallback3),
    static_cast<StageActorCallbackTable::typeCBCallbackV>(&MagicPlatform::mpCBCallback4)
};

MagicPlatform::MagicPlatform(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , tileData(nullptr)
    , tileSize(0, 0)
    , movementHandler()
    , collisionType(0)
    , rectCollider()
    , callbackTable(&MagicPlatformCallbackTable)
    , solidOnTopCollider()
{ }

Actor* MagicPlatform::build(const ActorBuildInfo* buildInfo) {
    return new MagicPlatform(buildInfo);
}

u32 MagicPlatform::onCreate() {
    Level::Area::Location* location = Level::instance()->getArea(LevelInfo::instance()->area)->getLocation(nullptr, this->settings1 & 0xFF);

    if (!location) {
        PRINT("MagicPlatform failed to get location");
        return 2;
    }
    
    u32 locX = location->x & ~0xF;
    u32 locY = location->y & ~0xF;
    this->tileSize.x = (location->w + (location->x & 0xF) + 0xF) / 16;
    this->tileSize.y = (location->h + (location->y & 0xF) + 0xF) / 16;

    if (!this->tileSize.x || !this->tileSize.y) {
        PRINT("MagicPlatform failed to get tile size");
        return 2;
    }
    
    this->tileData = new u16[this->tileSize.x * this->tileSize.y];

    for (u32 y = 0; y < this->tileSize.y; y++) {
        for (u32 x = 0; x < this->tileSize.x; x++) {
            u16* tile = TileMgr::getTilePtrCurrentArea(locX + x * 16, locY + y * 16, 0);
            this->tileData[x + y * this->tileSize.x] = tile ? *tile : 0;
        }
    }

    this->collisionType = (this->settings1 >> 8) & 0xF;
    if (this->collisionType > 2)
        return 2;
    
    const ColliderBase::Type::__type__ colliderType = ColliderBase::Type::__type__((this->settings1 >> 16) & 0xFF);
    if (colliderType > ColliderBase::Type::InvisibleBlock)
        return 2;
    
    ColliderBase::SurfaceType::__type__ colliderSurfaceType = ColliderBase::SurfaceType::__type__((this->settings1 >> 12) & 0xF);
    if (colliderSurfaceType > ColliderBase::SurfaceType::BeanstalkLeaf)
        return 2;
    
    switch (collisionType) {
        case 0: {
            ShapedCollider::Info info = {
                Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(this->tileSize.x * -8.0f, this->tileSize.y * 8.0f), Vec2f(this->tileSize.x * 8.0f, this->tileSize.y * -8.0f), 0
            };

            this->rectCollider.init(this, info);
            this->rectCollider.callbackTable = &this->callbackTable;
            
            this->rectCollider.setType(colliderType);

            if ((this->settings1 >> 8) & 1)
                this->rectCollider.setSurfaceType(colliderSurfaceType);

            ColliderMgr::instance()->add(&this->rectCollider);
            break;
        }

        case 1: {
            Vec2f points[2] = {
                Vec2f(this->tileSize.x * -8.0f, this->tileSize.y * 8.0f),
                Vec2f(this->tileSize.x * 8.0f, this->tileSize.y * 8.0f)
            };

            SolidOnTopCollider::Info info = {
                Vec2f(0.0f, 0.0f), 0.0f, 0.0f, points, 0
            };

            this->solidOnTopCollider.init(this, info, 2);
            this->solidOnTopCollider.setType(colliderType);

            if ((this->settings1 >> 8) & 1)
                this->solidOnTopCollider.setSurfaceType(colliderSurfaceType);

            ColliderMgr::instance()->add(&this->solidOnTopCollider);
            break;
        }
    }

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF);
    this->movementHandler.link(this->position, movementMask, this->movementID);

    return 1;
}

u32 MagicPlatform::onExecute() {
    this->movementHandler.execute();

    this->position = this->movementHandler.position;
    this->rotation.z = this->movementHandler.rotation;

    switch (this->collisionType) {
        case 0: {
            this->rectCollider.rotation = this->rotation.z;
            this->rectCollider.execute();
            break;
        }
        case 1: {
            this->solidOnTopCollider.rotation = this->rotation.z;
            this->solidOnTopCollider.execute();
            break;
        }
    }

    return 1;
}

u32 MagicPlatform::onDraw() {
    f32 angleSin, angleCos;
    sead::Mathf::sinCosIdx(&angleSin, &angleCos, this->rotation.z);

    for (s32 y = 0; y < this->tileSize.y; y++) {
        for (s32 x = 0; x < this->tileSize.x; x++) {
            s32 offsetX = x * 16 - this->tileSize.x * 8 + 8;
            s32 offsetY = y * 16 - this->tileSize.y * 8 + 8;
        
            f32 rotatedX =  offsetX * angleCos + offsetY * angleSin;
            f32 rotatedY = -offsetX * angleSin + offsetY * angleCos;
            Vec3f drawPos(this->position.x + rotatedX, this->position.y - rotatedY, this->position.z);

            DrawMgr::instance()->drawTile(tileData[y * this->tileSize.x + x], drawPos, this->rotation.z, this->scale);
        }
    }

    return 1;
}
