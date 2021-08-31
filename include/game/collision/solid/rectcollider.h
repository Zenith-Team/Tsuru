#pragma once

#include <game/collision/solid/shapedcollider.h>

class RectCollider : public ShapedCollider {
    SEAD_RTTI_OVERRIDE(RectCollider, ShapedCollider)

public:
    forceinline RectCollider()
        : ShapedCollider(4, this->points, this->nodes[0], this->nodes[1])
    {
        for (u32 i = 0; i < 4; i++) {
            this->points[i].x = 0.0f;
            this->points[i].y = 0.0f;
        }

        for (u32 i = 0; i < 4; i++) {
            this->nodes[0][i].mFlags = this->mFlags;
            this->nodes[0][i]._1C    = this->_134;
            this->nodes[1][i].mFlags = this->mFlags;
            this->nodes[1][i]._1C    = this->_134;
        }
    }

    virtual ~RectCollider() { }

    bool vf54(u8*, Vec2f*) override;

    Vec2f points[4];
    Node nodes[2][4];
};
