#pragma once

#include "game/actor/stage/boss.h"
#include "game/actor/stage/bosscontroller.h"
#include "game/actorglobalsholder.h"
#include "game/profile/profileid.h"

template <u32 hits>
class BossWrapper : public Boss { // Because the original Boss class is ridiculous to use :skull:
public:
    BossWrapper(const ActorBuildInfo* buildInfo)
        : Boss(buildInfo)
    { }

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override {
        u32 hitType = this->processCollision(hcSelf, hcOther);

        if (hitType == 1) {
            this->onStomp(hcOther->owner);
        }
    }

    void initHitsToDeath() override { this->hitsToDeath = hits; }
    void initHitsToDamage() { this->hitsToDamage = hits / 6; }

    void processHits(u32 amount) override {
        // copied ida decomp moment
        int dlt = this->hitsToDeath - amount;
        if (dlt > 0) {
            this->hitsToDeath = dlt;

            if (dlt >= this->hitsToDamage) {
                dlt = (dlt + this->hitsToDamage - 1) / this->hitsToDamage * this->hitsToDamage;
                this->hitsToDeath = dlt;
            }
        } else {
            this->hitsToDeath = 0;
        }
    }

    u32 vf59C() override {
        return (this->hitsToDeath - 1) / this->hitsToDamage > 1;
    }

    void startCutscene() override { this->isCutscene = true; }
    void endCutscene() override { this->isCutscene = false; }
    void vf594() override { }
    bool isNextDamageKill() override { return (this->hitsToDeath - 1) / this->hitsToDamage == 1; }
    u32 vf5AC() override { return 1; }
    u32 fireDamageAmount() override { return 1; }
    u32 vf5DC() override { return 0; }
    u32 vf5E4() override { return 0; }
    u32 vf5EC() override { return 0; }
    void vf634(StageActor* col) override { this->FUN_202D0F8(col, &this->position, 3); }
    void vf63C(StageActor* col) override { this->FUN_202D0F8(col, &this->position, 4); }
    void onStompDamage(StageActor* col) override { this->FUN_202D030(col, &this->position, 5); }
    void onStompKill(StageActor* col) override { this->FUN_202D094(col, &this->position, 6); }
    void setLookTarget() override { this->lookTarget.targetPosition.x = this->position.x; this->lookTarget.targetPosition.y = this->position.y; }
    bool vf58C() override { return this->freezeMgr._44 ^ 1; }
    void onKill() override { this->vf574(); ActorGlobalsHolder::instance()->activeBossController->bossDoneDying = true; }
    u32 stompDamageAmount() override { return hits / 3; }
    u32 groundPoundDamageAmount() override { return hits / 3; }
    u32 stompDamageAmount2() override { return hits / 3; }
    u32 stompDamageAmountEx() override { return hits / 3; }

    void updateModel() override = 0;
    void initHitboxCollider() override = 0;
};

template <ProfileID::ProfileIDType BossProfile>
class BossControllerWrapper : public BossController {
public:
    BossControllerWrapper(const ActorBuildInfo* buildInfo)
        : BossController(buildInfo)
    { }

    u32 vf1F4() override { return 1; }
    u8 vf1FC() override { return this->_17CA; }
    u32 vf204() override { return 1; }

    StageActor* getTargetBoss() override {
        for (Actor** current = ActorMgr::instance()->actors.start.buffer; current < ActorMgr::instance()->actors.end.buffer; current++) {
            Actor* actor = *current;
            if (actor && actor->getProfileID() == BossProfile) {
                return (StageActor*) actor;
            }
        }

        #ifdef LOG
            LOG("Could not find target boss with profile ID %d", (u32) BossProfile);
        #endif

        return nullptr;
    }

    void spawnCutsceneKamek() override {
        ActorBuildInfo buildInfo = { 0 };
        buildInfo.profile = Profile::get(ProfileID::CutsceneKamek);

        ((CutsceneKamek*) ActorMgr::instance()->create(buildInfo, 0))->doStateChange(&CutsceneKamek::StateID_CutsceneKamekState2);
    }
};
