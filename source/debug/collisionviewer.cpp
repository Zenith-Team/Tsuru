#include "game/task/areatask.h"
#include "game/task/courseselecttask.h"
#include "game/collision/collidermgr.h"
#include "game/collision/solid/polygoncollider.h"
#include "game/collision/solid/circularcollider.h"
#include "game/collision/solid/polylinecollider.h"
#include "game/collision/actorphysicsmgr.h"
#include "game/actor/actormgr.h"
#include "game/actor/courseselect/cscollisionactor.h"
#include "game/collision/cshitboxcollider.h"
#include "agl/lyr/renderinfo.h"
#include "log.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "sead/matrix.h"
#include "math/functions.h"
#include "sead/graphicscontext.h"
#include "sead/primitiverenderer.h"
#include "sead/mathcalccommon.h"
#include "agl/lyr/renderer.h"
#include "game/graphics/model/modelnw.h"
#include "game/tilemgr.h"
#include "game/level/levelcamera.h"
#include "game/level/level.h"
#include "game/level/levelinfo.h"
#include "imgui/imgui.h"

#include <cmath>

void drawLine3D(const Vec3f& position, const u32 rotation, const sead::Color4f& color, const f32 lineLength, const f32 lineThickness) {
    Vec3f scale(lineLength, lineThickness, lineThickness);
    Vec3u rot(0x80000000, (rotation + 0x40000000) * 0xFFFFFFFF, 0x00000000);
    f32 rotSin;
    f32 rotCos;
    sead::Mathf::sinCosIdx(&rotSin, &rotCos, rotation);
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
    mtx.makeSRT(scale, rot, pos);
    sead::PrimitiveRenderer::instance()->rendererImpl->drawQuadImpl(mtx, color, color);
}

void drawLine(const Vec2f& point1, const Vec2f& point2, const sead::Color4f& color, const f32 lineThickness) {
    f32 length = sqrtf(powf(point1.x - point2.x, 2) + powf(point1.y - point2.y, 2));

    const Vec2f& leftPoint = (point1.x < point2.x) ? point1 : point2;
    const Vec2f& rightPoint = (&leftPoint == &point1) ? point2 : point1;
    f32 angle = atan2f(rightPoint.y - leftPoint.y, rightPoint.x - leftPoint.x);

    drawLine(leftPoint, angle, color, length, lineThickness);
}

void drawBox(const sead::BoundBox2f& box, const sead::Color4f& color, const f32 lineWidth) {
    Rect* rect = (Rect*)&box;

    Vec2f point1(rect->left, rect->top);
    Vec2f point2(rect->right, rect->top);
    Vec2f point3(rect->right, rect->bottom);
    Vec2f point4(rect->left, rect->bottom);

    drawLine(point1, point2, color, lineWidth);
    drawLine(point2, point3, color, lineWidth);
    drawLine(point3, point4, color, lineWidth);
    drawLine(point1, point4, color, lineWidth);
}

const sead::Color4f& getTileCollisionColor(const TileDataInfo& bcData) {
    switch (bcData.getUnitSolidType()) {
        case TileDataInfo::SolidType_None:
        default:
            return sead::colorBlack;
        case TileDataInfo::SolidType_Fill:
            return sead::colorBlue;
        case TileDataInfo::SolidType_Outer:
            return sead::colorMagenta;
        case TileDataInfo::SolidType_Inner:
            return sead::colorGreen;
        case TileDataInfo::SolidType_OuterAndInner:
            return sead::colorGray;
    }
}

void drawTilesCollision() {
    LevelCamera* levelCamera = LevelCamera::instance();
    TileMgr* tileMgr = TileMgr::instance();

    const s32 unitSize = 16;
    const s32 delta = unitSize - 1;
    const u32 mask = ~delta;

    const s32 left   =  s32(std::floor( levelCamera->cameraLeft  ))          & mask;
    const s32 right  = (s32(std::ceil ( levelCamera->cameraRight )) + delta) & mask;
    const s32 bottom = (s32(std::ceil (-levelCamera->cameraBottom)) + delta) & mask;
    const s32 top    =  s32(std::floor(-levelCamera->cameraTop   ))          & mask;

    for (s32 y = top; y < bottom; y += unitSize) {
        for (s32 x = left; x < right; x += unitSize) {
            const TileDataInfo bcData = tileMgr->getTileData(x, y, 0);
            if (bcData.getUnitKind() == TileDataInfo::Kind_Normal && bcData.getUnitSolidType() == TileDataInfo::SolidType_None)
                continue;

            const sead::Color4f& color = getTileCollisionColor(bcData);

            const sead::BoundBox2f box(
                sead::Vector2<f32>(static_cast<f32>(x),            -static_cast<f32>(y + unitSize)),
                sead::Vector2<f32>(static_cast<f32>(x + unitSize), -static_cast<f32>(y))
            );

            drawBox(box, color, 1.0f);
        }
    }
}

void AreaTask::renderCollisions(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (renderInfo.renderStepIndex != 5) // PostFx
        return;

    sead::GraphicsContext graphicsContext;
    graphicsContext.apply();

    if (TsuruSaveMgr::sSaveData.locationViewerEnabled || TsuruSaveMgr::sSaveData.collisionViewerEnabled || TsuruSaveMgr::sSaveData.pathViewerEnabled) {
        sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
        sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
        sead::PrimitiveRenderer::instance()->begin();
    }

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled)
    {
        ActorBuffer* actors = &ActorMgr::instance()->actors;
        for (u32 i = 0; i < actors->start.size; i++)
        {
            StageActor* actor = sead::DynamicCast<StageActor>(actors->start[i]);
            if (actor)
            {
                Vec2f pos;
                renderInfo.camera->projectByMatrix(&pos, actor->position, *renderInfo.projection, *renderInfo.viewport);
                pos.x = pos.x + 1280.0f / 2.0f;
                pos.y = pos.y +  720.0f / 2.0f;
                pos.y = -pos.y + 720.0f;

                char buf[128] = { 0 };
                __os_snprintf(buf, 128, "0x%08X", actor->id);
                ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x, pos.y), ImColor(1.0f, 0.0f, 1.0f, 1.0f), buf);
                //__os_snprintf(buf, 128, "%f, %f", actor->position.x, actor->position.y);
                //ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x, pos.y + 20.0f), ImColor(1.0f, 0.0f, 1.0f, 1.0f), buf);
            }
        }
    }

    if (TsuruSaveMgr::sSaveData.locationViewerEnabled) {
        for (u32 i = 1; i <= 256; i++) {
            Rect rect;
            void* a = Level::instance()->getArea(LevelInfo::instance()->area)->getLocation(&rect, i);

            if (!a) {
                continue;
            }

            Vec2f point1(rect.left, rect.top);
            Vec2f point2(rect.right, rect.top);
            Vec2f point3(rect.right, rect.bottom);
            Vec2f point4(rect.left, rect.bottom);

            drawLine(point1, point2, sead::colorPurple, 1.0f);
            drawLine(point2, point3, sead::colorPurple, 1.0f);
            drawLine(point3, point4, sead::colorPurple, 1.0f);
            drawLine(point1, point4, sead::colorPurple, 1.0f);
            //drawLine(point1, point3, sead::colorPurple, 1.0f);   // Diagonal line

            sead::BoundBox2f box(*(sead::BoundBox2f*)&rect);
            sead::PrimitiveRenderer::instance()->drawQuad(
                sead::PrimitiveRenderer::QuadArg()
                    .setBoundBox(box, 4000.0f)
                    .setColor(sead::Color4f(1.0f, 0.0f, 1.0f, 0.3f))
            );
        }
    }

    if (TsuruSaveMgr::sSaveData.pathViewerEnabled) {
        for (u32 i = 1; i <= 256; i++) {
            Level::Area::PathNode* path = Level::instance()->getArea(LevelInfo::instance()->area)->getPathNodes(i);

            if (!path) {
                continue;
            }

            u32 nodeCount = Level::instance()->getArea(LevelInfo::instance()->area)->getPath(i)->nodeCount;

            for (u32 node = 0; node < nodeCount; node++) {
                if (node == nodeCount - 1) {
                    // TODO: don't break and draw line from last node to first node if path loops
                    break;
                }

                drawLine(Vec2f(path[node].x, -path[node].y), Vec2f(path[node+1].x, -path[node+1].y), sead::colorGreen, 1.0f);
            }
        }
    }

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled) {
        HitboxCollider::List::Node* hColliderNode = HitboxColliderMgr::instance()->activeList.first;

        while (hColliderNode != nullptr) {
            HitboxCollider* hCollider = hColliderNode->owner;

            if ((hCollider->colliderInfo._1C & 0x800) == 0) {
                Rect rect;
                hCollider->getRect(rect);

                if (hCollider->colliderInfo.shape == HitboxCollider::Shape::Rectangle) {
                    Vec2f point1(rect.left, rect.top);
                    Vec2f point2(rect.right, rect.top);
                    Vec2f point3(rect.right, rect.bottom);
                    Vec2f point4(rect.left, rect.bottom);

                    drawLine(point1, point2, sead::colorRed, 1.0f);
                    drawLine(point2, point3, sead::colorRed, 1.0f);
                    drawLine(point3, point4, sead::colorRed, 1.0f);
                    drawLine(point1, point4, sead::colorRed, 1.0f);
                    //drawLine(point1, point3, sead::colorRed, 1.0f);   // Diagonal line

                    sead::BoundBox2f box(*(sead::BoundBox2f*)&rect);
                    sead::PrimitiveRenderer::instance()->drawQuad(
                        sead::PrimitiveRenderer::QuadArg()
                            .setBoundBox(box, 4000.0f)
                            .setColor(sead::Color4f(1.0f, 0.0f, 0.0f, 0.3f))
                    );
                }

                else if (hCollider->colliderInfo.shape == HitboxCollider::Shape::Circle) {
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

            if (hCollider->colliderInfo.shape == HitboxCollider::Shape::Rectangle) {
                Vec2f point1(rect.left, rect.top);
                Vec2f point2(rect.right, rect.top);
                Vec2f point3(rect.right, rect.bottom);
                Vec2f point4(rect.left, rect.bottom);

                drawLine(point1, point2, sead::colorRed, 1.0f);
                drawLine(point2, point3, sead::colorRed, 1.0f);
                drawLine(point3, point4, sead::colorRed, 1.0f);
                drawLine(point1, point4, sead::colorRed, 1.0f);
                //drawLine(point1, point3, sead::colorRed, 1.0f); // Diagonal line

                sead::BoundBox2f box(*(sead::BoundBox2f*)&rect);
                sead::PrimitiveRenderer::instance()->drawQuad(
                    sead::PrimitiveRenderer::QuadArg()
                        .setBoundBox(box, 4000.0f)
                        .setColor(sead::Color4f(1.0f, 0.0f, 0.0f, 0.3f))
                );
            }

            else if (hCollider->colliderInfo.shape == HitboxCollider::Shape::Circle) {
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

            if (sead::IsDerivedFrom<CircularCollider, ColliderBase>(colliderBase)) {
                CircularCollider* collider = static_cast<CircularCollider*>(colliderBase);

                sead::PrimitiveRenderer::instance()->drawCircle32(Vec3f(collider->ownerInfo.position->x + collider->offset.x + collider->_160.x, collider->ownerInfo.position->y + collider->offset.y + collider->_160.y, 4000.0f), collider->radius, sead::colorPurple);
            }

            else if (sead::IsDerivedFrom<PolylineCollider, ColliderBase>(colliderBase)) {
                PolylineCollider* collider = static_cast<PolylineCollider*>(colliderBase);
                if (collider->points.size < 2) continue;

                const Vec2f center = Vec2f((*collider->ownerInfo.position).x, (*collider->ownerInfo.position).y) + collider->offset;

                for (u32 i = 0; i < collider->nodes1.size; i++) {
                    const ColliderBase::Node& node = collider->nodes1[i];
                    drawLine(center + node.sensor.point1, center + node.sensor.point2, sead::colorOrange, 1.5f);
                }
            }

            else if (sead::IsDerivedFrom<PolygonCollider, ColliderBase>(colliderBase)) {
                PolygonCollider* collider = static_cast<PolygonCollider*>(colliderBase);
                if (collider->points.size < 2) continue;

                const Vec2f center = Vec2f((*collider->ownerInfo.position).x, (*collider->ownerInfo.position).y) + collider->offset;

                for (u32 i = 0; i < collider->nodes1.size; i++) {
                    const ColliderBase::Node& node = collider->nodes1[i];
                    drawLine(center + node.sensor.point1, center + node.sensor.point2, sead::colorBlue, 1.0f);
                }

                // if it's a rectangle
                if (collider->points.size >= 4 && !(collider->points.size & 1)) {
                    const ColliderBase::Node& node1 = collider->nodes1[0];
                    const ColliderBase::Node& node2 = collider->nodes1[collider->points.size / 2 - 1];
                    drawLine(center + node1.sensor.point1, center + node2.sensor.point2, sead::colorBlue, 1.0f);

                    // TODO: fix rotated quads
                    /* //sead::BoundBox2f box(center + Vec2f(node1.sensor.point1.x, node2.sensor.point2.y), center + Vec2f(node2.sensor.point2.x, node2.sensor.point1.y));
                    sead::BoundBox2f box(*(sead::BoundBox2f*)&collider->rect);
                    sead::PrimitiveRenderer::QuadArg quadArg;
                    quadArg.setBoundBox(box, 4000.0f);
                    quadArg.setColor(sead::Color4f(0.0f, 0.0f, 1.0f, 0.3f));

                    Mtx34 mtx;
                    mtx.makeSRTIdx(Vec3f(quadArg.size.x, quadArg.size.y, 1.0f), Vec3u(0, 0, collider->rotation), quadArg.center);
                    //sead::PrimitiveRenderer::instance()->setModelMatrix(mtx);

                    sead::PrimitiveRenderer::instance()->rendererImpl->drawQuadImpl(mtx, quadArg.color0, quadArg.color1); */
                }
            }

            else {
                PRINT(LogColor::Yellow, "Found unknown collider for actor with ID ", fmt::hex, colliderBase->owner->id, " and profile ID ", fmt::hex, colliderBase->owner->profile->id, " (vtable addr: ", (u32)*vtable, ")");
            }
        }

        //drawTilesCollision();

        ActorBuffer* actors = &ActorMgr::instance()->actors;
        for (u32 i = 0; i < actors->start.size; i++) {
            StageActor* actor = sead::DynamicCast<StageActor, Actor>(actors->start[i]);
            if (actor == NULL || actor->isDeleted)
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
    }

    if (TsuruSaveMgr::sSaveData.locationViewerEnabled || TsuruSaveMgr::sSaveData.collisionViewerEnabled || TsuruSaveMgr::sSaveData.pathViewerEnabled) {
        sead::PrimitiveRenderer::instance()->end();
    }
}

void CourseSelectTask::renderCollisions(const agl::lyr::RenderInfo& renderInfo) {
    this->drawLayer3D(renderInfo);

    if (renderInfo.renderStepIndex != 5) // PostFx
        return;

    sead::GraphicsContext graphicsContext;
    graphicsContext.cullingMode = sead::Graphics::CullingMode_None;
    graphicsContext.blendEnable = false;
    graphicsContext.apply();

    if (TsuruSaveMgr::sSaveData.collisionViewerEnabled) {
        ActorBuffer* actors = &ActorMgr::instance()->actors;
        for (u32 i = 0; i < actors->start.size; i++)
        {
            CourseSelectActorBase* actor = sead::DynamicCast<CourseSelectActorBase>(actors->start[i]);
            if (actor)
            {
                Vec2f pos;
                renderInfo.camera->projectByMatrix(&pos, actor->position, *renderInfo.projection, *renderInfo.viewport);
                pos.x = pos.x + 1280.0f / 2.0f;
                pos.y = pos.y +  720.0f / 2.0f;
                pos.y = -pos.y + 720.0f;

                char buf[128] = { 0 };
                __os_snprintf(buf, 128, "0x%08X", actor->id);
                ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x, pos.y), ImColor(1.0f, 0.0f, 1.0f, 1.0f), buf);
                //__os_snprintf(buf, 128, "%f, %f", actor->position.x, actor->position.y);
                //ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x, pos.y + 20.0f), ImColor(1.0f, 0.0f, 1.0f, 1.0f), buf);
            }
        }

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
