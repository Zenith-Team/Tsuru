#include "game/actor/stage/multistateactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/collision/solid/rectcollider.h"
#include "game/collision/collidermgr.h"
#include "game/actor/actormgr.h"
#include "game/level/levelinfo.h"
#include "game/task/taskmgr.h"
#include "game/task/coursetask.h"
#include "game/graphics/lightsource.h"

class BeepBlock : public MultiStateActor {
    SEAD_RTTI_OVERRIDE_IMPL(BeepBlock, MultiStateActor);

public:
    ENUM_CLASS(Color,
        Red,
        Blue
    );

public:
    BeepBlock(const ActorBuildInfo* buildInfo);
    virtual ~BeepBlock() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    ModelWrapper* model;
    RectCollider rectCollider;
    Color::__type__ beepBlockType;
    LightSource light;

    static Color::__type__ CurrentBeepBlockState;

    static const PolygonCollider::Info colliderInfo;

    DECLARE_STATE(BeepBlock, RedEnabled);
    DECLARE_STATE(BeepBlock, RedDisabled);
    DECLARE_STATE(BeepBlock, BlueEnabled);
    DECLARE_STATE(BeepBlock, BlueDisabled);
};

CREATE_STATE(BeepBlock, RedEnabled);
CREATE_STATE(BeepBlock, RedDisabled);
CREATE_STATE(BeepBlock, BlueEnabled);
CREATE_STATE(BeepBlock, BlueDisabled);

REGISTER_PROFILE(BeepBlock, ProfileID::BeepBlock);
PROFILE_RESOURCES(ProfileID::BeepBlock, Profile::LoadResourcesAt::Course, "block_beep");

const PolygonCollider::Info BeepBlock::colliderInfo = {
    Vec2f(0.0f, 0.0f), 0.0f, 0.0f, Vec2f(-8.0f, 8.0f), Vec2f(8.0f, -8.0f), 0
};

BeepBlock::Color::__type__ BeepBlock::CurrentBeepBlockState = BeepBlock::Color::Blue;

BeepBlock::BeepBlock(const ActorBuildInfo* buildInfo)
    : MultiStateActor(buildInfo)
    , model(nullptr)
    , rectCollider()
    , beepBlockType(BeepBlock::Color::Blue)
{ }

u32 BeepBlock::onCreate() {
    this->rectCollider.init(this, colliderInfo);

    this->model = ModelWrapper::create("block_beep", "block_beep", 0, 1);
    this->model->playTexPatternAnim("switch");
    this->model->texPatternAnims[0]->frameCtrl.speed = 0;

    this->position.y -= 8.0f;
    this->position.x += 8.0f;

    this->beepBlockType = static_cast<BeepBlock::Color::__type__>(this->eventID1 >> 0x4 & 0xF); // Nybble 1

    if (this->beepBlockType == BeepBlock::Color::Red) {
        this->doStateChange(&StateID_RedDisabled);
    } else {
        this->doStateChange(&StateID_BlueDisabled);
        this->model->texPatternAnims[0]->frameCtrl.currentFrame = 1;
    }

    return 1;
}

u32 BeepBlock::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position + Vec3f(0.0f, 0.0f, 240.0f));

    this->model->setScale(this->scale);
    this->model->updateAnimations();
    this->model->setMtx(mtx);
    this->model->updateModel();

    this->states.execute();

    return 1;
}

u32 BeepBlock::onDraw() {
    static f32 radius = 3.0f;
    static sead::Color4f red(0xCC000088);
    static sead::Color4f blue(0x00999955);
    static Vec3f zero = 0;

    if (this->states.currentState()->ID == StateID_RedDisabled.ID || this->states.currentState()->ID == StateID_BlueDisabled.ID) {
        this->light.update(0, &zero, nullptr, &radius, nullptr, &red);
    } else {

        if (this->beepBlockType == BeepBlock::Color::Red) {
            this->light.update(0, &this->position, nullptr, &radius, nullptr, &red);
        } else {
            this->light.update(0, &this->position, nullptr, &radius, nullptr, &blue);
        }

        this->model->draw();
    }

    return 1;
}

/* STATE: RedEnabled */

void BeepBlock::beginState_RedEnabled() {
    ColliderMgr::instance()->add(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_RedEnabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Blue)
        this->doStateChange(&StateID_RedDisabled);

    this->rectCollider.execute();
}

void BeepBlock::endState_RedEnabled() { }

/* STATE: RedDisabled */

void BeepBlock::beginState_RedDisabled() {
    ColliderMgr::instance()->remove(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_RedDisabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Red)
        this->doStateChange(&StateID_RedEnabled);
}

void BeepBlock::endState_RedDisabled() { }

/* STATE: BlueEnabled */

void BeepBlock::beginState_BlueEnabled() {
    ColliderMgr::instance()->add(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_BlueEnabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Red)
        this->doStateChange(&StateID_BlueDisabled);

    this->rectCollider.execute();
}

void BeepBlock::endState_BlueEnabled() { }

/* STATE: BlueDisabled */

void BeepBlock::beginState_BlueDisabled() {
    ColliderMgr::instance()->remove(&this->rectCollider);

    // Don't forget to change the model here when that's done
}

void BeepBlock::executeState_BlueDisabled() {
    if (CurrentBeepBlockState == BeepBlock::Color::Blue)
        this->doStateChange(&StateID_BlueEnabled);
}

void BeepBlock::endState_BlueDisabled() { }
