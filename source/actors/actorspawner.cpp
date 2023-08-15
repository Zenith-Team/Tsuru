#include "game/actor/stage/stageactor.h"
#include "game/actor/actormgr.h"
#include "game/eventmgr.h"

class ActorSpawner : public StageActor {
    SEAD_RTTI_OVERRIDE_IMPL(ActorSpawner, StageActor);

public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    virtual ~ActorSpawner() { }

    u32 onCreate() override;
    u32 onExecute() override;

    Actor* child;
    u16 spawnProfileID;
    bool spawned;
};

REGISTER_PROFILE(ActorSpawner, ProfileID::ActorSpawner);

ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo)
    : StageActor(buildInfo)
    , spawned(false)
{ }

u32 ActorSpawner::onCreate() {
    if (!this->eventID1) {
        return 2;
    }

    this->child = nullptr;

    u16 inputID = linkID | ((movementID & 0xF) << 8); //Nybble 22-24

    if (this->movementID & 0x10 /* Nybble 21, Bit 4 */) {
        this->spawnProfileID = Profile::sprite(inputID);
    } else {
        this->spawnProfileID = inputID;
    }

    return this->onExecute();
}

u32 ActorSpawner::onExecute() {
    u8 eventMode = this->movementID >> 6; // Nybble 21 > Bit 1-2

    if (EventMgr::instance()->isActive(this->eventID1 - 1)) {
        if (!this->spawned) {
            if (eventMode == 3 && this->child) {
                StageActor* actor = sead::DynamicCast<StageActor, Actor>(this->child);

                if (actor) {
                    actor->isActive = true;
                    actor->isVisible = true;
                    actor->addHitboxColliders();
                }
                this->isDeleted = this->child->isDeleted;
                return 1;
            }

            ActorBuildInfo buildInfo = { 0 };

            if (this->movementID & 0x20 /* Nybble 21, Bit 3 */) {
                buildInfo.settings2 = this->settings2 & 0xFF0000FF; // Nybbles 13-14 + 19-20
                buildInfo.movementID = this->settings2 >> 16 & 0xFF; // Nybbles 15-16
                buildInfo.linkID = this->settings2 >> 8 & 0xFF; // Nybbles 17-18
            } else {
                buildInfo.settings2 = this->settings2; // Nybble 13-20
            }

            buildInfo.settings1 = this->settings1; // Nybbles 5-12
            buildInfo.profile = Profile::get(this->spawnProfileID);
            buildInfo.position = this->position;
            buildInfo.eventID1 = (this->eventID2 >> 4) & 0xF; // Nybble 3
            buildInfo.eventID2 = this->eventID2 & 0xF; // Nybble 4
            buildInfo.parentID = this->id;
            this->child = ActorMgr::instance()->create(buildInfo, 0);

            this->spawned = true;
        }
    }

    else {
        if (eventMode == 2 && this->child) {
            this->child->isDeleted = true;
            this->child = nullptr;
        }

        else if (eventMode == 3 && this->child) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(this->child);

            if (actor) {
                actor->isActive = false;
                actor->isVisible = false;
                actor->removeHitboxColliders();
            }
            this->isDeleted = this->child->isDeleted;
        }

        if (eventMode != 1) {
            this->spawned = false;
        }
    }

    return 1;
}
