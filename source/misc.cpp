#include "actor/enemy.h"

void Bouncy__collisionYoshi(Enemy* _this, HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (_this->processCollision(hcSelf, hcOther, 1) == 0)
        _this->Enemy::collisionYoshi(hcSelf, hcOther);
}
