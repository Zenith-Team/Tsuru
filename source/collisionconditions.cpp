#include <game/actor/stage/enemy.h>

void collisionYoshi_Bounce(Enemy* _this, HitboxCollider* hcSelf, HitboxCollider* hcOther) {
    if (!_this->processCollision(hcSelf, hcOther, 1))
        _this->Enemy::collisionYoshi(hcSelf, hcOther);
}
