#include "actor/enemy.h"

void Bouncy__collisionYoshi(Enemy* _this, HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (_this->processCollision(hcSelf, hcOther, 1) == 0)
        _this->Enemy::collisionYoshi(hcSelf, hcOther);
}

void StationaryPokey(Enemy* _this) {
    // If nybble 8 is checked
    if ((_this->settings1 >> 16) & 0x1) {
        _this->speed.setX(0.0f);
    }

    // restore replaced instruction
    asm("li r0, -1");
}
