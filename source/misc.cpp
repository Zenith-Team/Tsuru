#include "actor/enemy.h"

void Bouncy__collisionYoshi(Enemy* _this, ActiveCollider* acSelf, ActiveCollider* acOther) {
    if (_this->processCollision(acSelf, acOther, 1) == 0)
        _this->Enemy::collisionYoshi(acSelf, acOther);
}
