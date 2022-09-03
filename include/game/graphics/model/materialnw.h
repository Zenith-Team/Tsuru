#pragma once

#include "game/graphics/model/material.h"
#include "nw/g3d/materialobj.h"

class MaterialNW : public Material {
public:
    MaterialNW(nw::g3d::MaterialObj* material)
        : materialObj(material)
        , texSrtMtx()
    { }

    void setTexSrtMtx(s32 index, const Vec2f& scale, const u32& rotate, const Vec2f& translate) override;
    void setTexSrt(s32 index, const Vec2f& scale, const u32& rotate, const Vec2f& translate) override;
    void getTexSrt(s32 index, Vec2f* scale = nullptr, u32* rotate = nullptr, Vec2f* translate = nullptr) const override;
    void setTevColor(s32 index, const sead::Color4f& color) override;
    void getTevColor(s32 index, sead::Color4f& color) const override;
    void setTevKColor(s32 index, const sead::Color4f& color) override;
    void getTevKColor(s32 index, sead::Color4f& color) const override;

    nw::g3d::MaterialObj* materialObj;
    Mtx34 texSrtMtx[8];
};
