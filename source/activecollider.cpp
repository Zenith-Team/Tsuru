#include "actor/actor.h"
#include "activecollider.h"

void ActiveCollider::getRect(Rect& outRect)
{
    Vec3* ownerPos = &this->owner->position;

    outRect.left   = ownerPos->x + this->info.distToCenter.x - this->info.distToEdge.x;
    outRect.right  = ownerPos->x + this->info.distToCenter.x + this->info.distToEdge.x;
    outRect.top    = ownerPos->y + this->info.distToCenter.y + this->info.distToEdge.y;
    outRect.bottom = ownerPos->y + this->info.distToCenter.y - this->info.distToEdge.y;
}

bool ActiveCollider::collidersOverlap(ActiveCollider* acSelf, ActiveCollider* acOther)
{
    Rect thisRect;
    acSelf->getRect(thisRect);

    Rect otherRect;
    acOther->getRect(otherRect);

    return Rect::RectsOverlap(thisRect, otherRect);
}
