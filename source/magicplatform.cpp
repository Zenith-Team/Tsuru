#include "actor/actor.h"
#include "actor/twowayplatform.h"

#include "model.h"
#include "drawmgr.h"
#include "collider.h"
#include "movementhandler.h"
#include "level.h"
#include "math.h"
#include "tile.h"

class MagicPlatform : public Actor
{
public:
    MagicPlatform(const ActorBuildInfo* buildInfo);
    virtual ~MagicPlatform() { }

    static Base* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;
    u32 onDelete() override;

    bool magicPlatformAcCallback1(ActiveCollider*, Vec2*) { return false; }
    void magicPlatformAcCallback3(ActiveCollider*, Vec2*) { }
    void magicPlatformAcCallback4(ActiveCollider*, Vec2*) { }
    bool magicPlatformCbCallback1(ColliderBase*, Vec2*)   { return true; }
    void magicPlatformCbCallback3(ColliderBase*, Vec2*)   { }
    void magicPlatformCbCallback4(ColliderBase*, Vec2*)   { }

    u16* tileData;
    u32 tileW, tileH;

    MovementHandler movementHandler;

    u8 collisionType;
    RectCollider rectCollider;
    CallbackTable* callbackTable;
    SolidOnTopCollider solidOnTopCollider;
};

const ActorInfo magicPlatformActorInfo = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ActorInfo::FlagIgnoreSpawnRange | ActorInfo::FlagUnknown };
const Profile magicPlatformProfile(&MagicPlatform::build, ProfileId::Sprite314, "MagicPlatform", &magicPlatformActorInfo, 0);
PROFILE_RESOURCES(ProfileId::Sprite314);

// Callback table, useful for squishing the player
Actor::CallbackTable magicPlatformCallbackTable = {
    nullptr,
    static_cast<Actor::CallbackTable::typeAcCallbackB>(&Actor::actorAcCallback0),
    static_cast<Actor::CallbackTable::typeAcCallbackB>(&MagicPlatform::magicPlatformAcCallback1),
    static_cast<Actor::CallbackTable::typeAcCallbackB>(&Actor::actorAcCallback2),
    static_cast<Actor::CallbackTable::typeAcCallbackV>(&MagicPlatform::magicPlatformAcCallback3),
    static_cast<Actor::CallbackTable::typeAcCallbackV>(&MagicPlatform::magicPlatformAcCallback4),
    static_cast<Actor::CallbackTable::typeCbCallbackB>(&Actor::actorCbCallback0),
    static_cast<Actor::CallbackTable::typeCbCallbackB>(&MagicPlatform::magicPlatformCbCallback1),
    static_cast<Actor::CallbackTable::typeCbCallbackB>(&TwoWayPlatform::twoWayPlatformCbCallback2),
    static_cast<Actor::CallbackTable::typeCbCallbackV>(&MagicPlatform::magicPlatformCbCallback3),
    static_cast<Actor::CallbackTable::typeCbCallbackV>(&MagicPlatform::magicPlatformCbCallback4),
};


MagicPlatform::MagicPlatform(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , tileData(nullptr)
    , movementHandler()
    , rectCollider()
    , callbackTable(&magicPlatformCallbackTable)
    , solidOnTopCollider()
{
}

Base* MagicPlatform::build(const ActorBuildInfo* buildInfo)
{
    return new MagicPlatform(buildInfo);
}


u32 MagicPlatform::onCreate()
{
    Level::Area* area = Level::instance->getArea(LevelInfo::instance->area);
    Level::Area::Location* location = area->getLocation(nullptr, settings1 & 0xFF);

    if (!location)
        return 2;

    u32 locX = location->x & ~0xF;
    u32 locY = location->y & ~0xF;
    tileW = (location->w + (location->x & 0xF) + 0xF) / 16;
    tileH = (location->h + (location->y & 0xF) + 0xF) / 16;

    if (!tileW || !tileH)
        return 2;

    tileData = new u16[tileW*tileH];

    for (u32 y = 0; y < tileH; y++)
    {
        for (u32 x = 0; x < tileW; x++)
        {
            u16* tilePtr = TileMgr::getTilePtrCurrentArea(locX + x*16, locY + y*16, 0);
            tileData[x + y*tileW] = tilePtr ? *tilePtr : 0;
        }
    }

    collisionType = (settings1 >> 8) & 0xF;
    if (collisionType > 2)
        return 2;

    const ColliderBase::Types colliderType = ColliderBase::Types((settings1 >> 16) & 0xFF);
    if (colliderType > ColliderBase::TypeInvisibleBlock)
        return 2;

    ColliderBase::SurfaceTypes colliderSurfaceType = ColliderBase::SurfaceTypes((settings1 >> 12) & 0xF);
    if (colliderSurfaceType > ColliderBase::SurfaceTypeBeanstalkLeaf)
        colliderSurfaceType = ColliderBase::SurfaceTypeRegular;

    if (collisionType == 0)
    {
        ShapedCollider::Info info = { Vec2(0.0f, 0.0f), 0.0f, 0.0f, Vec2(tileW * -8.0f, tileH * 8.0f), Vec2(tileW * 8.0f, tileH * -8.0f), 0 };
        rectCollider.init(this, info);

        // Callback table, useful for squishing the player
        rectCollider.callbackTable = reinterpret_cast<void**>(&this->callbackTable);
        rectCollider._144 = reinterpret_cast<void*>(&TwoWayPlatform::cbCallback4);
        rectCollider._148 = reinterpret_cast<void*>(&TwoWayPlatform::cbCallback5);
        rectCollider._14C = reinterpret_cast<void*>(&TwoWayPlatform::cbCallback6);

        rectCollider.setType(colliderType);
        if ((settings1 >> 8) & 1)
            rectCollider.setSurfaceType(colliderSurfaceType);

        ColliderMgr::instance->add(&rectCollider);
    }
    else if (collisionType == 1)
    {
        Vec2 points[2] = { Vec2(tileW * -8.0f, tileH * 8.0f), Vec2(tileW * 8.0f, tileH * 8.0f) };
        SolidOnTopCollider::Info info = { Vec2(0.0f, 0.0f), 0.0f, 0.0f, points, 0 };
        solidOnTopCollider.init(this, info, 2);
        solidOnTopCollider.setType(colliderType);
        if ((settings1 >> 8) & 1)
            solidOnTopCollider.setSurfaceType(colliderSurfaceType);

        ColliderMgr::instance->add(&solidOnTopCollider);
    }

    u32 movementMask = movementHandler.getMaskForMovementType(settings2 & 0xFF);
    movementHandler.link(position, movementMask, movementId);

    return onExecute();
}

u32 MagicPlatform::onExecute()
{
    movementHandler.execute();
    position = movementHandler.position;
    rotation.z = movementHandler.rotation;

    if (collisionType == 0)
    {
        rectCollider.rotation = rotation.z;
        rectCollider.execute();
    }
    else if (collisionType == 1)
    {
        solidOnTopCollider.rotation = rotation.z;
        solidOnTopCollider.execute();
    }

    return 1;
}

u32 MagicPlatform::onDraw()
{
    f32 angle = (static_cast<f32>(rotation.z) / 0x80000000) * M_PI;
    f32 angleCos = cos(angle);
    f32 angleSin = sin(angle);

    for (s32 y = 0; y < tileH; y++)
    {
        for (s32 x = 0; x < tileW; x++)
        {
            s32 offsetX = x*16 - tileW*8 + 8;
            s32 offsetY = y*16 - tileH*8 + 8;

            // https://en.wikipedia.org/wiki/Rotation_matrix#In_two_dimensions
            f32 rotatedX =  offsetX * angleCos + offsetY * angleSin;
            f32 rotatedY = -offsetX * angleSin + offsetY * angleCos;
            Vec3 drawPos(position.x + rotatedX, position.y - rotatedY, position.z);

            DrawMgr::instance->drawTile(tileData[y*tileW + x], drawPos, rotation.z, scale);
        }
    }

    return 1;
}

u32 MagicPlatform::onDelete()
{
    if (tileData)
        delete[] tileData;

    return 1;
}
