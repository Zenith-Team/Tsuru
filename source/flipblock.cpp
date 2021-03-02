#include "actor/blockbase.h"
#include "actor/player.h"
#include "drawmgr.h"
#include "model.h"
#include "playermgr.h"

/*
    * The flip block does not check if there
    * is an actor (other than the player)
    * overlapping with it and can change from
    * the "flipping" state to the "waiting"
    * state while the actor is inside.
*/

class FlipBlock : public BlockBase
{
public:
    FlipBlock(const ActorBuildInfo* buildInfo);
    virtual ~FlipBlock() { }

    static Base* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    void spawnItemUp() override;
    void spawnItemDown() override;

    void beginState_BlockCoinState3() override;
    void endState_BlockCoinState3() override;

    bool isActive() override;
    void destroy() override;
    void destroy2() override;

    void updateModel();
    bool playerOverlaps();

    ModelWrapper* model;
    int flipsRemaining;

    static const ActiveCollider::Info colliderInfo;

    DECLARE_STATE(FlipBlock, Flipping)
};

CREATE_STATE(FlipBlock, Flipping);

const ActorInfo FlipBlockActorInfo = { 8, -16, 8, -8, 0x100, 0x100, 0, 0, 0, 0, ActorInfo::FlagUnknown };
const Profile FlipBlockProfile(&FlipBlock::build, ProfileId::Sprite551, "FlipBlock", &FlipBlockActorInfo, 0x1002);
PROFILE_RESOURCES(ProfileId::Sprite551, "flip_blocks");

const ActiveCollider::Info FlipBlock::colliderInfo = { Vec2(0.0f, 8.0f), Vec2(8.0f, 8.0f), 0, 0, 0, 0, 0, 0, nullptr };


FlipBlock::FlipBlock(const ActorBuildInfo* buildInfo)
    : BlockBase(buildInfo)
    , flipsRemaining(0)
{
}

Base* FlipBlock::build(const ActorBuildInfo* buildInfo)
{
    return new FlipBlock(buildInfo);
}


u32 FlipBlock::onCreate()
{
    _1CB4 = 0.0f;
    _1CB8 = 0.0f;
    _1AB4 = 0;
    _1AEC = 0;
    _1CC0 = 0;
    collisionMask = 0x1;

    stateType = StateTypeQuestionBlock;
    rectCollider.setType(ColliderBase::TypeQuestionBlock);

    if (!init(true, true))
        return 2;

    content = Nothing;

    _1CAC = 0.0f;
    visibleAreaSize.x = 2048.0f;
    visibleAreaSize.y = 1024.0f;

    registerColliderActiveInfo();

    model = ModelWrapper::create("flip_blocks", "flip_blocks", 0, 1);

    aCollider.init(this, &colliderInfo, nullptr);
    addActiveColliders();

    doStateChange(&StateID_Wait);
    updateModel();

    return 1;
}

u32 FlipBlock::onExecute()
{
    u32 result = BlockBase::onExecute();
    if (result != 1)
        return result;

    updateModel();
    return 1;
}

u32 FlipBlock::onDraw()
{
    DrawMgr::instance->drawModel(model);
    return 1;
}

void FlipBlock::spawnItemUp()
{
    doStateChange(&StateID_Flipping);
}

void FlipBlock::spawnItemDown()
{
    collisionMgr.setSensor(nullptr, 3);
    doStateChange(&StateID_Flipping);
}

void FlipBlock::beginState_BlockCoinState3()
{
    // Delay in frames before switching to StateID_Wait
    _1A90 = 15;
}

void FlipBlock::endState_BlockCoinState3()
{
    _1AAE = 0;

    // Undo our "fake" Used state
    stateType = StateTypeQuestionBlock;
    rectCollider.setType(ColliderBase::TypeQuestionBlock);

    rectCollider._88 |= 0x18;
    rectCollider.topCallback = BlockBase::activeTopCollisionCallback;
    rectCollider.bottomCallback = BlockBase::activeBottomCollisionCallback;
    rectCollider.sideCallback = BlockBase::activeSideCollisionCallback;
    rectCollider.callbackTable = reinterpret_cast<void**>(&this->callbackTable);
}

bool FlipBlock::isActive()
{
    return true;
}

void FlipBlock::destroy()
{
    spawnDirection = 3;
    doStateChange(&StateID_Flipping);
}

void FlipBlock::destroy2()
{
    spawnDirection = 3;
    doStateChange(&StateID_Flipping);
}

void FlipBlock::beginState_Flipping()
{
    flipsRemaining = 7;
    ColliderMgr::instance->remove(&rectCollider);
}

void FlipBlock::executeState_Flipping()
{
    if (spawnDirection == 3) // Down
        rotation.x += 0x8000000;

    else
        rotation.x -= 0x8000000;

    if (rotation.x == 0 && --flipsRemaining <= 0 && !playerOverlaps())
        doStateChange(&StateID_Wait);
}

void FlipBlock::endState_Flipping()
{
    // Add the collider back and literally "reset" the actor
    init(true, true);

    _1AAE = 0;
    rotation.x = 0;
}

void FlipBlock::updateModel()
{
    Vec3 pos(position.x, position.y + 8.0f, position.z);
    Mtx34 mtx;
    mtx.rotateAndTranslate(rotation, pos);

    model->setMtx(mtx);
    model->updateModel();
}

bool FlipBlock::playerOverlaps()
{
    u32 playerActiveMask = 1;
    bool overlaps = false;

    Player* player;

    for (s32 i = 0; i < 4; i++)
    {
        if (PlayerMgr::instance->playerFlags & playerActiveMask)
        {
            player = PlayerMgr::instance->players[i];
            if (player != nullptr)
                overlaps = ActiveCollider::collidersOverlap(&this->aCollider, &player->aCollider);
        }

        if (overlaps)
            return true;

        playerActiveMask <<= 1;
    }

    return false;
}
