#pragma once

#include <game/collision/solid/shapedcollider.h>

class RectCollider : public ShapedCollider {
    SEAD_RTTI_OVERRIDE(RectCollider, ShapedCollider)

public:
    forceinline RectCollider() : ShapedCollider(4, points, nodes[0], nodes[1]) {
        for (u32 i = 0; i < 4; i++) {
            points[i].x = 0.0f;
            points[i].y = 0.0f;
        }

        for (u32 i = 0; i < 4; i++) {
            nodes[0][i].flags = this->flags;
            nodes[0][i]._1C = this->_134;
            nodes[1][i].flags = this->flags;
            nodes[1][i]._1C = this->_134;
        }
    }

    virtual ~RectCollider() { }

    bool vf54(u8*, Vec2f*) override;

    Vec2f points[4];
    Node  nodes[2][4];
};
