#pragma once

#include "game/graphics/model/material.h"
#include "nw/g3d/g3d_MaterialObj.h"

class MaterialNW : public Material {
public:
    MaterialNW(nw::g3d::MaterialObj* material)
        : materialObj(material)
        , texSrtMtx()
    { }

    void setTexSrtMtx(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) override;
    void setTexSrt(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) override;
    void getTexSrt(s32 index, sead::Vector2f* scale = nullptr, u32* rotate = nullptr, sead::Vector2f* translate = nullptr) const override;
    void setTevColor(s32 index, const sead::Color4f& color) override;
    void getTevColor(s32 index, sead::Color4f& color) const override;
    void setTevKColor(s32 index, const sead::Color4f& color) override;
    void getTevKColor(s32 index, sead::Color4f& color) const override;

    nw::g3d::MaterialObj* materialObj;
    sead::Matrix34f texSrtMtx[8];
};
