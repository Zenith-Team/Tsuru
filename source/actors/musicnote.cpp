#include "game/actor/stage/stageactor.h"
#include "game/graphics/model/modelnw.h"
#include "game/actor/actormgr.h"
#include "game/eventmgr.h"
#include "game/sound/sound.h"
#include "game/movementhandler.h"
#include "game/eventmgr.h"

class MusicNoteMgr;

class MusicNote : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(MusicNote, StageActor);
public:
    MusicNote(const ActorBuildInfo* buildInfo);
    virtual ~MusicNote() { }

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    static const HitboxCollider::Info collisionInfo;

    int note;
    ModelWrapper* noteModel;
    MusicNoteMgr* mgr;
    MovementHandler movementHandler;
    u8 mgrID;
};

class MusicNoteMgr : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(MusicNoteMgr, StageActor);

public:
    MusicNoteMgr(const ActorBuildInfo* buildInfo);
    virtual ~MusicNoteMgr() {}

    u32 onCreate() override;
    u32 onExecute() override;
    u32 onDraw() override;

    static void collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther);

    static const HitboxCollider::Info collisionInfo;

    ModelWrapper* clefModel;
    MovementHandler movementHandler;
    u32 collectedCount;
    u32 targetCount;
    u32 id;
    u32 powerup;
    u32 timeLimit;
    bool touched;
};

const ActorInfo MusicNoteActorInfo = {
    Vec2i(0, 0), Vec2i(0, 0), Vec2i(4800, 4800), 0, 0, 0, 0, 0
};

REGISTER_PROFILE(MusicNote, ProfileID::MusicNote, "MusicNote", &MusicNoteActorInfo);
REGISTER_PROFILE(MusicNoteMgr, ProfileID::MusicNoteMgr);

PROFILE_RESOURCES(ProfileID::MusicNote, Profile::LoadResourcesAt::Course, "note", "star_coin");
PROFILE_RESOURCES(ProfileID::MusicNoteMgr, Profile::LoadResourcesAt::Course, "clef", "star_coin");


// Music Note

const HitboxCollider::Info MusicNote::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 8.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &MusicNote::collisionCallback
};

MusicNote::MusicNote(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , noteModel(nullptr)
    , mgr(nullptr)
    , mgrID(0)
    , movementHandler()
{ }

u32 MusicNote::onCreate() {
    this->noteModel = ModelWrapper::create("note", "note", 0, 1);
    this->noteModel->playTexPatternAnim("rainbow", 0);
    this->noteModel->texPatternAnims[0]->frameCtrl.shouldLoop(true);
    this->hitboxCollider.init(this, &MusicNote::collisionInfo);
    this->addHitboxColliders();

    this->mgrID = this->eventID1 & 0xFF; // nybbles 1-2
    this->note = this->eventID2 >> 0x4 & 0xF; // nybble 3
    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF); // nybble 20
    this->movementHandler.link(this->position, movementMask, this->movementID); // nybble 21-22


    this->scale = .17f;
    this->isActive = false;
    this->isVisible = false;

    return this->onExecute();
}

u32 MusicNote::onExecute() {
    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->rotation.y += fixDeg(3.0f);
    this->noteModel->setMtx(mtx);
    this->noteModel->setScale(this->scale);
    this->noteModel->updateAnimations();
    this->noteModel->updateModel();
    this->movementHandler.execute();
    this->position = this->movementHandler.position;
    for (Actor** it = ActorMgr::instance()->actors.start.buffer; it != ActorMgr::instance()->actors.end.buffer; ++it) { // search for MusicNoteMgr actors with a matching ID
        if (*it != nullptr) {
            Actor& actor = **it;
            if (actor.getProfileID() == ProfileID::MusicNoteMgr) {
                MusicNoteMgr* mgr = static_cast<MusicNoteMgr*>(&actor);
                if (mgr->id == this->mgrID) {
                    this->mgr = mgr;
                    break;
                }
            }
        }
    }

    return 1;
}

u32 MusicNote::onDraw() {
    this->noteModel->draw();
    return 1;
}

// Music Note Manager
const HitboxCollider::Info MusicNoteMgr::collisionInfo = {
    Vec2f(0.0f, 0.0f), Vec2f(8.0f, 16.0f), HitboxCollider::Shape::Rectangle, 5, 0, 0x824F, 0x20208, 0, &MusicNoteMgr::collisionCallback
};

MusicNoteMgr::MusicNoteMgr(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , collectedCount(0)
    , id(buildInfo->eventID1 & 0xFF) // nybbles 1-2
    , targetCount(buildInfo->eventID2 & 0xFF) // nybbles 3-4
    , powerup(buildInfo->settings1 >> 0x1C & 0xF) // nybble 5
    , movementHandler()
    , clefModel(nullptr)
    , timeLimit((buildInfo->settings1 >> 0x14 & 0xFF ? buildInfo->settings1 >> 0x14 & 0xFF : 5) * 60) // nybbles 6-7 
    , touched(false)
{ }

u32 MusicNoteMgr::onCreate() {
    this->clefModel = ModelWrapper::create("clef", "clef", 0, 1);
    this->clefModel->playTexPatternAnim("rainbow", 0);
    this->clefModel->texPatternAnims[0]->frameCtrl.shouldLoop(true);
    this->scale = .17f;

    this->hitboxCollider.init(this, &MusicNoteMgr::collisionInfo);
    this->addHitboxColliders();

    u32 movementMask = this->movementHandler.getMaskForMovementType(this->settings2 & 0xFF); // nybble 20
    this->movementHandler.link(this->position, movementMask, this->movementID); // nybble 21-22
    return this->onExecute();
}


u32 MusicNoteMgr::onExecute() {
    if (this->collectedCount >= (this->targetCount)) {
        this->isDeleted = true;
    }

    Mtx34 mtx;
    mtx.makeRTIdx(this->rotation, this->position);
    this->rotation.y += fixDeg(3.0f);
    this->clefModel->setMtx(mtx);
    this->clefModel->setScale(this->scale);
    this->clefModel->updateAnimations();
    this->clefModel->updateModel();
    this->movementHandler.execute();
    this->position = this->movementHandler.position;

    if (this->touched) {
        this->timeLimit--;
    }
    if (this->touched && this->timeLimit <= 180 && this->timeLimit % 60 == 0 && this->timeLimit != 0) { // less than 3 seconds remaining, a sound effect plays once every second
        playSound(SoundEffects::SE_SYS_SWITCH_CT_LAST, this->position);
        for (Actor** it = ActorMgr::instance()->actors.start.buffer; it != ActorMgr::instance()->actors.end.buffer; ++it) { // search for MusicNote actors and make them flicker
            if (*it != nullptr) {
                Actor& actor = **it;
                if (actor.getProfileID() == ProfileID::MusicNote) {
                    MusicNote* individualNote = static_cast<MusicNote*>(&actor);
                    individualNote->isVisible = !isVisible;
                }
            }
        }
    } else if (this->touched && this->timeLimit % 60 == 0 && this->timeLimit != 0) { // play sound effect every 2 seconds
        playSound(SoundEffects::SE_SYS_SWITCH_CT, this->position);
    } else if (this->timeLimit == 0) {
        for (Actor** it = ActorMgr::instance()->actors.start.buffer; it != ActorMgr::instance()->actors.end.buffer; ++it) { // search for MusicNote actors and delete them
            if (*it != nullptr) {
                Actor& actor = **it;
                if (actor.getProfileID() == ProfileID::MusicNote) {
                    MusicNote* individualNote = static_cast<MusicNote*>(&actor);
                    if (individualNote->mgrID == this->id) {
                        individualNote->isDeleted = true;
                    }
                }
            }
        }
        this->isDeleted = true;
    }
    return 1;
}

u32 MusicNoteMgr::onDraw() {
    this->clefModel->draw();
    return 1;
}

// collision
void MusicNote::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (hcOther->owner->type == StageActor::Type::Player) {
        MusicNote* self = (MusicNote*)hcSelf->owner;

        if ((self->mgr->collectedCount + 1) >= (self->mgr->targetCount)) {
            // spawn specified powerup and play the assigned sound
            playSound((SoundEffects::IDs)(SoundEffects::SE_EMY_PATAMET_STEP + self->note), self->position);
            playSound(SoundEffects::SE_EMY_PATAMET_COMPLETE, self->position);

            ActorBuildInfo buildInfo = { 0 };

            buildInfo.settings1 = 0x6000000; // nybble 6 = reward spawn

            switch (self->mgr->powerup) {
                case 1: { // fire flower
                    buildInfo.profile = Profile::get(592);
                    break;
                }
                case 2: { // ice flower
                    buildInfo.profile = Profile::get(594);
                    break;
                }
                case 3: { // mini mushroom
                    buildInfo.profile = Profile::get(593);
                    break;
                }
                case 4: { // propeller
                    buildInfo.profile = Profile::get(595);
                    break;
                }
                case 5: { // penguin
                    buildInfo.profile = Profile::get(596);
                    break;
                }
                case 6: { // acorn
                    buildInfo.profile = Profile::get(598);
                    break;
                }
                case 7: { // 1-up mushroom
                    buildInfo.profile = Profile::get(597);
                    break;
                }
                case 8: { // 3-up moon
                    buildInfo.profile = Profile::get(599);
                    break;
                }
                case 9: { // star coin - 1
                    buildInfo.profile = Profile::get(426);
                    // we dont need to set the settings1 value because the nybble is already set to 0 for star coin 1
                    buildInfo.position = self->mgr->position;
                    break;
                }
                case 10: { // star coin - 2
                    buildInfo.profile = Profile::get(426);
                    buildInfo.settings1 = 4096;
                    buildInfo.position = self->mgr->position;
                    break;
                }
                case 11: { // star coin - 3
                    buildInfo.profile = Profile::get(426);
                    buildInfo.settings1 = 8192;
                    buildInfo.position = self->mgr->position;
                    break;
                }
                default: { // mushroom
                    buildInfo.profile = Profile::get(591);
                    break;
                }
            }
            
            
            ActorMgr::instance()->create(buildInfo, 0);
        }
        else {
            playSound((SoundEffects::IDs)(SoundEffects::SE_EMY_PATAMET_STEP + self->note), self->position);
        }
        self->mgr->collectedCount++;
        self->isDeleted = true;
    }
}

void MusicNoteMgr::collisionCallback(HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    MusicNoteMgr* self = (MusicNoteMgr*)hcSelf->owner;
    self->touched = true;
    playSound(SoundEffects::SE_SYS_RED_RING, hcSelf->owner->position);
    hcSelf->owner->isVisible = false;
    hcSelf->owner->removeHitboxColliders();
    if (hcOther->owner->type == StageActor::Type::Player) {
        for (Actor** it = ActorMgr::instance()->actors.start.buffer; it != ActorMgr::instance()->actors.end.buffer; ++it) { // search for MusicNote actors and activates them if not already activated
            if (*it != nullptr) {
                Actor& actor = **it;
                if (actor.getProfileID() == ProfileID::MusicNote) {
                    MusicNote* individualNote = static_cast<MusicNote*>(&actor);
                    if (individualNote->mgrID == self->id) {
                        individualNote->isActive = true;
                        individualNote->isVisible = true;
                    }
                }
            }
        }
    }

}