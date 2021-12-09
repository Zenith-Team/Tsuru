#include "game/task/areatask.h"
#include "game/task/courseselecttask.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/shapedcollider.h"
#include "game/collision/solid/circularcollider.h"
#include "game/collision/solid/solidontopcollider.h"
#include "game/collision/actorphysicsmgr.h"
#include "game/actor/actormgr.h"
#include "game/actor/courseselect/cscollisionactor.h"
#include "game/collision/cshitboxcollider.h"
#include "agl/lyr/renderinfo.h"
#include "log.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "utils/mtx.h"
#include "math/functions.h"

//! TODO: Region free using syms
#define __vtbl__21BlockCoinBaseCollider 0x101018AC
#define __vtbl__16CircularCollider 0x10041B28
#define __vtbl__18SolidOnTopCollider 0x10042238
#define __vtbl__22SolidOnTopLiftCollider 0x10129C70
#define __vtbl__14ShapedCollider 0x10042688
#define __vtbl__12RectCollider 0x100FB820
#define __vtbl__4Vine 0x10102F84
#define __vtbl__15RedCoinCollider 0x1014F7B0
#define __vtbl__20RotatingPipeCollider 0x10150CC0
#define __vtbl__23MovingSemisolidCollider 0x10141E40
#define __vtbl__16GoalPoleCollider 0x101198F0
#define __vtbl__18PAcornOnlyCollider 0x1014752C
#define __vtbl__18StoneBlockCollider 0x100EEEDC
#define __vtbl__18SteelBlockCollider 0x100E8330
#define __vtbl__16POWBlockCollider 0x1014C784
#define __vtbl__19PipeCannonBaseCollider 0x1010562C
#define __vtbl__19PipeCannonTopCollider 0x101055A4
#define __vtbl__11IceCollider 0x1007EAB4
#define __vtbl__18TowerBlockCollider 0x101426B0
#define __vtbl__12GearCollider 0x101190B4

void drawLine3D(const Vec3f& position, const u32 rotation, const sead::Color4f& color, const f32 lineLength, const f32 lineThickness) {
    Vec3f scale(lineLength, lineThickness, lineThickness);
    Vec3u rot(0x80000000, (rotation + 0x40000000) * 0xFFFFFFFF, 0x00000000);
    f32 rotSin;
    f32 rotCos;
    sinCosIdx(&rotSin, &rotCos, rotation);
    Vec3f pos(position.x + (lineLength * rotSin) / 2, position.y, position.z + (lineLength * rotCos) / 2);

    Mtx34 mtx;
    mtx.makeSRzxyTIdx(scale, rot, pos);
    sead::PrimitiveRenderer::instance()->rendererImpl->drawCubeImpl(mtx, color, color);
}

void drawLine(const Vec2f& position, const f32 rotation, const sead::Color4f& color, const f32 lineLength, const f32 lineThickness) {
    Vec3f scale(lineLength, lineThickness, 1.0f);
    Vec3f rot(0.0f, 0.0f, rotation);
    Vec3f pos(position.x + (lineLength * cosf(rotation)) / 2, position.y + (lineLength * sinf(rotation)) / 2, 4000.0f);

    Mtx34 mtx;
    Mtx34::makeSRT(mtx, scale, rot, pos);
    sead::PrimitiveRenderer::instance()->rendererImpl->drawQuadImpl(mtx, color, color);
}

void drawLine(const Vec2f& point1, const Vec2f& point2, const sead::Color4f& color, const f32 lineThickness) {
    f32 length = sqrtf(powf(point1.x - point2.x, 2) + powf(point1.y - point2.y, 2));

    const Vec2f& leftPoint = (point1.x < point2.x) ? point1 : point2;
    const Vec2f& rightPoint = (&leftPoint == &point1) ? point2 : point1;
    f32 angle = atan2f(rightPoint.y - leftPoint.y, rightPoint.x - leftPoint.x);

    drawLine(leftPoint, angle, color, length, lineThickness);
}

void AreaTask::renderCollisions(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
        sead::PrimitiveRenderer::instance()->begin();

        HitboxCollider::List::Node* hColliderNode;
        hColliderNode = HitboxColliderMgr::instance()->activeList.first;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->owner;

            if ((hCollider->colliderInfo._1C & 0x800) == 0) {
                Rect rect;
                hCollider->getRect(rect);

                if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Rectangle) {
                    Vec2f point1(rect.left, rect.top);
                    Vec2f point2(rect.right, rect.top);
                    Vec2f point3(rect.right, rect.bottom);
                    Vec2f point4(rect.left, rect.bottom);

                    drawLine(point1, point2, sead::colorRed, 1.0f);
                    drawLine(point2, point3, sead::colorRed, 1.0f);
                    drawLine(point3, point4, sead::colorRed, 1.0f);
                    drawLine(point1, point4, sead::colorRed, 1.0f);
                    drawLine(point1, point3, sead::colorRed, 1.0f);   // Diagonal line
                }

                else if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Circle) {
                    f32 radius = (rect.right - rect.left) / 2.0f;

                    sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(rect.left + radius, rect.bottom + radius, 4000.0f), radius, sead::colorRed);
                }
            }

            hColliderNode = hColliderNode->next;
        }

        hColliderNode = HitboxColliderMgr::instance()->_34.first;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->owner;

            Rect rect;
            hCollider->getRect(rect);

            if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Rectangle) {
                Vec2f point1(rect.left, rect.top);
                Vec2f point2(rect.right, rect.top);
                Vec2f point3(rect.right, rect.bottom);
                Vec2f point4(rect.left, rect.bottom);

                drawLine(point1, point2, sead::colorRed, 1.0f);
                drawLine(point2, point3, sead::colorRed, 1.0f);
                drawLine(point3, point4, sead::colorRed, 1.0f);
                drawLine(point1, point4, sead::colorRed, 1.0f);
                drawLine(point1, point3, sead::colorRed, 1.0f); // Diagonal line
            }

            else if (hCollider->colliderInfo.shape == HitboxCollider::HitboxShape_Circle) {
                f32 radius = (rect.right - rect.left) / 2.0f;

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(rect.left + radius, rect.bottom + radius, 4000.0f), radius, sead::colorRed);
            }

            hColliderNode = hColliderNode->next;
        }

        ColliderBase::List* activeList = &ColliderMgr::instance()->lists[0];
        ColliderBase::List::Node* node = activeList->first;

        while (node != nullptr) {
            ColliderBase* colliderBase = node->owner;
            node = node->next;
            void** vtable = (void**)((u8*)colliderBase + 0xC);

            //if (sead::IsDerivedFrom<CircularCollider, ColliderBase>(colliderBase)) {
            if ((u32)*vtable == __vtbl__16CircularCollider) {
                CircularCollider* collider = static_cast<CircularCollider*>(colliderBase);

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(collider->ownerInfo.position->x + collider->distToCenter.x + collider->_160.x, collider->ownerInfo.position->y + collider->distToCenter.y + collider->_160.y, 4000.f), collider->radius, sead::colorBlue);
            }

            //else if (sead::IsDerivedFrom<SolidOnTopCollider, ColliderBase>(colliderBase)) {
            else if ((u32)*vtable == __vtbl__18SolidOnTopCollider || (u32)*vtable == __vtbl__22SolidOnTopLiftCollider) {
                SolidOnTopCollider* collider = static_cast<SolidOnTopCollider*>(colliderBase);
                if (collider->points.size < 2) continue;

                const Vec2f center = Vec2f((*collider->ownerInfo.position).x, (*collider->ownerInfo.position).y) + collider->distToCenter;

                for (u32 i = 0; i < collider->nodes1.size; i++) {
                    const ColliderBase::Node& node = collider->nodes1[i];
                    drawLine(center + node.sensor.point1, center + node.sensor.point2, sead::colorGreen, 1.0f);
                }
            }

            //else if (sead::IsDerivedFrom<ShapedCollider, ColliderBase>(colliderBase)) {
            else if ((u32)*vtable == __vtbl__14ShapedCollider         || (u32)*vtable == __vtbl__12RectCollider ||
                     (u32)*vtable == __vtbl__21BlockCoinBaseCollider  || (u32)*vtable == __vtbl__4Vine ||
                     (u32)*vtable == __vtbl__15RedCoinCollider        || (u32)*vtable == __vtbl__20RotatingPipeCollider ||
                     (u32)*vtable == __vtbl__16GoalPoleCollider       || (u32)*vtable == __vtbl__23MovingSemisolidCollider ||
                     (u32)*vtable == __vtbl__18PAcornOnlyCollider     || (u32)*vtable == __vtbl__18StoneBlockCollider ||
                     (u32)*vtable == __vtbl__18SteelBlockCollider     || (u32)*vtable == __vtbl__16POWBlockCollider ||
                     (u32)*vtable == __vtbl__19PipeCannonBaseCollider || (u32)*vtable == __vtbl__19PipeCannonTopCollider ||
                     (u32)*vtable == __vtbl__11IceCollider            || (u32)*vtable == __vtbl__18TowerBlockCollider ||
                     (u32)*vtable == __vtbl__12GearCollider) {
                ShapedCollider* collider = static_cast<ShapedCollider*>(colliderBase);
                if (collider->points.size < 2) continue;

                const Vec2f center = Vec2f((*collider->ownerInfo.position).x, (*collider->ownerInfo.position).y) + collider->distToCenter;

                for (u32 i = 0; i < collider->nodes1.size; i++) {
                    const ColliderBase::Node& node = collider->nodes1[i];
                    drawLine(center + node.sensor.point1, center + node.sensor.point2, sead::colorBlue, 1.0f);
                }

                if (collider->points.size >= 4 && !(collider->points.size & 1)) {
                    const ColliderBase::Node& node1 = collider->nodes1[0];
                    const ColliderBase::Node& node2 = collider->nodes1[collider->points.size / 2 - 1];
                    drawLine(center + node1.sensor.point1, center + node2.sensor.point2, sead::colorBlue, 1.0f);
                }
            }

            else {
                LOG("Found unknown collider for actor with ID 0x%X and profile ID 0x%X (vtable addr: 0x%08X)\n",
                    colliderBase->owner->id, colliderBase->owner->profile->id, (u32)*vtable
                );
            }
        }

        ActorBuffer* actors = &ActorMgr::instance()->actors;
        for (u32 i = 0; i < actors->start.size; i++) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(actors->start[i]);
            if (actor == NULL || !actor->isVisible || actor->isDeleted)
                continue;

            ActorPhysicsMgr* actorPhysicsMgr = actor->getActorPhysicsMgr();
            if (actorPhysicsMgr == NULL || actorPhysicsMgr->position == NULL)
                continue;

            for (u32 j = 0; j < 4; j++) {
                const ActorPhysicsMgr::Sensor* sensor = actorPhysicsMgr->getSensor(j);
                if (sensor == nullptr)
                    continue;

                f32 p1 = sensor->point1;
                f32 p2 = sensor->point2;

                if (p1 == p2) {
                    p1 -= 0.5f;
                    p2 += 0.5f;
                }

                if (j < 2) {
                    Vec2f point1(actorPhysicsMgr->position->x + sensor->distanceFromCenter, actorPhysicsMgr->position->y + p1);
                    Vec2f point2(actorPhysicsMgr->position->x + sensor->distanceFromCenter, actorPhysicsMgr->position->y + p2);

                    drawLine(point1, point2, sead::colorYellow, 1.0f);
                }

                else {
                    Vec2f point1(actorPhysicsMgr->position->x + p1, actorPhysicsMgr->position->y + sensor->distanceFromCenter);
                    Vec2f point2(actorPhysicsMgr->position->x + p2, actorPhysicsMgr->position->y + sensor->distanceFromCenter);

                    drawLine(point1, point2, (j == 2) ? sead::colorWhite : sead::colorCyan, 1.0f);
                }
            }
        }

        sead::PrimitiveRenderer::instance()->end();
    }
}

void CourseSelectTask::renderCollisions(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
        sead::PrimitiveRenderer::instance()->begin();

        for (u32 i = 0; i < CSHitboxColliderMgr::instance()->array1.ptrNum; i++) {
            CSHitboxCollider* cshCollider = static_cast<CSHitboxCollider*>(CSHitboxColliderMgr::instance()->array1.ptrs[i]);

            if (!cshCollider)
                continue;

            CourseSelectActor* actor = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->actors.findActorByID(cshCollider->ownerID));

            if (!actor)
                continue;

            sead::PrimitiveRenderer::instance()->drawCube(actor->position + cshCollider->info.offset, cshCollider->info.size, sead::colorYellow);
        }

        for (u32 i = 0; i < CSHitboxColliderMgr::instance()->array2.ptrNum; i++) {
            CSHitboxCollider* cshCollider = static_cast<CSHitboxCollider*>(CSHitboxColliderMgr::instance()->array2.ptrs[i]);

            if (!cshCollider)
                continue;

            CourseSelectActor* actor = reinterpret_cast<CourseSelectActor*>(ActorMgr::instance()->actors.findActorByID(cshCollider->ownerID));

            if (!actor)
                continue;

            sead::PrimitiveRenderer::instance()->drawCube(actor->position + cshCollider->info.offset, cshCollider->info.size, sead::colorRed);
        }

        Actor** current = ActorMgr::instance()->actors.start.buffer;
        while (current < ActorMgr::instance()->actors.end.buffer) {
            Actor* actor = *current;
            if (actor) {
                CourseSelectActor* csactor = static_cast<CourseSelectActor*>(actor);
                drawLine3D(csactor->position, csactor->rotation, sead::colorMagenta, 128.0f, 4.0f);
            }
            current++;
        }

        sead::PrimitiveRenderer::instance()->end();
    }
}
