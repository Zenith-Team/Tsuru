#include "log.h"
#include "level.h"
#include "actor/enemy.h"
#include "actor/pokey.h"
#include "actor/playerbase.h"

void Bouncy__collisionYoshi(Enemy* _this, HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (_this->processCollision(hcSelf, hcOther, 1) == 0)
        _this->Enemy::collisionYoshi(hcSelf, hcOther);
}

void StationaryPokey(Pokey* _this) {
    // If nybble 8 is checked
    if ((_this->settings1 >> 16) & 0x1) {
        _this->speed.x = 0.0f;
    }

    // Restore replaced instruction
    asm("li r0, -1");
}

void FireproofPokey(Pokey* _this, HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    // If nybble 8 is checked
    // TODO: move this to nybble 7
    if ((_this->settings1 >> 16) & 0x1)
        return;
    else
        _this->Pokey::collisionFireball(hcSelf, hcOther);
}

void LogPowerup(PlayerBase* _this) {
    LOG("powerup state: %x", _this->powerupState);
}
