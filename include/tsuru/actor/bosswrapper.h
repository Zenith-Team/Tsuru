#pragma once

#include "game/actor/stage/boss.h"
#include "game/actor/stage/bosscontroller.h"
#include "game/actorglobalsholder.h"
#include "game/profile/profileid.h"

template <u32 THitPoints>
class BossWrapper : public Boss { // Because the original Boss class is ridiculous to use :skull:
public:
    BossWrapper(const ActorBuildInfo* buildInfo)
        : Boss(buildInfo)
    { }

    void collisionPlayer(HitboxCollider* hcSelf, HitboxCollider* hcOther) override {
        u32 hitType = this->processCollision(hcSelf, hcOther);

        if (hitType == 0) {
            this->damagePlayer(hcSelf, hcOther);
        } else if (hitType == 1 || hitType == 3) {
            this->onStomp(hcOther->owner);
        }
    }

    void initHitsToDeath() override { this->hitsToDeath = THitPoints; }
    void initHitsToDamage() { this->hitsToDamage = THitPoints / 6; }

    void processHits(u32 amount) override {
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
    void onKill() override { this->vf574(); this->finishedDying(); }
    u32 stompDamageAmount() override { return THitPoints / 3; }
    u32 groundPoundDamageAmount() override { return THitPoints / 3; }
    u32 stompDamageAmount2() override { return THitPoints / 3; }
    u32 stompDamageAmountEx() override { return THitPoints / 3; }

    void updateModel() override = 0;
    void initHitboxCollider() override = 0;

    void finishedDying() {
        ActorGlobalsHolder::instance()->activeBossController->bossDoneDying = true;
    }

    void finishedSpawning() {
        ActorGlobalsHolder::instance()->activeBossController->startSequenceFinished = true;
    }
};

class BossControllerWrapper : public BossController {
public:
    BossControllerWrapper(const ActorBuildInfo* buildInfo)
        : BossController(buildInfo)
    { }

    u32 vf1F4() override { return 1; }
    u8 vf1FC() override { return this->_17CA; }
    u32 vf204() override { return 1; }

    Boss* getTargetBoss() override = 0;
    void spawnCutsceneKamek() override = 0;
};
