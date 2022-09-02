#pragma once

#include "game/graphics/model/renderobj.h"
#include "game/graphics/model/animation.h"
#include "game/graphics/model/material.h"
#include "agl/shadow/depthshadow.h"
#include "sead/heap.h"
#include "sead/sphere.h"

class ObjLayer;

class Model : public RenderObj, public sead::IDisposer {
    SEAD_RTTI_OVERRIDE(Model, RenderObj);

public:
    Model();
    virtual ~Model();

    virtual void updateAnimations() = 0;
    virtual void updateModel() = 0;
    virtual void setMtxRT(const Mtx34& rt) = 0;
    virtual const Mtx34& getMtxRT() const = 0;
    virtual void setScale(const Vec3f& scale) = 0;
    virtual const Vec3f& getScale() const = 0;
    virtual bool hasOpa() const = 0;
    virtual bool hasXlu() const = 0;
    virtual s32 searchBoneIndex(const sead::SafeString& name) const = 0;
    virtual const char* getBoneName(s32 index) const = 0;
    virtual u32 getBoneNum() const = 0;
    virtual void setBoneLocalMatrix(s32 index, const Mtx34& rt, const Vec3f& scale) = 0;
    virtual void getBoneLocalMatrix(s32 index, Mtx34* rt, Vec3f* scale) const = 0;
    virtual void setBoneWorldMatrix(s32 index, const Mtx34& mtx) = 0;
    virtual void getBoneWorldMatrix(s32 index, Mtx34* mtx) const = 0;
    virtual void setBoneVisible(s32 index, bool visible) = 0;
    virtual bool isBoneVisible(s32 index) const = 0;
    virtual u32 getMaterialNum() const = 0;
    virtual s32 searchMaterialIndex(const sead::SafeString& name) const = 0;
    virtual const char* getMaterialName(s32 index) const = 0;
    virtual Material* getMaterial(s32 index) const = 0;
    virtual void setMaterialVisible(s32 index, bool visible) = 0;
    virtual bool isMaterialVisible(s32 index) const = 0;
    virtual void setBoundingEnable(bool enable) = 0;
    virtual bool isBoundingEnable() const = 0;
    virtual const sead::Sphere3f& getBounding() const = 0;
    virtual void calcViewShapeShadowFlags(agl::sdw::DepthShadow* depthShadow, ObjLayer* shadowLayer, RenderMgr* renderMgr) = 0;
    virtual sead::SafeString getName() const = 0;
    virtual void setSklAnimBlendWeight(s32 index, f32 weight) = 0;
    virtual f32 getSklAnimBlendWeight(s32 index) const = 0;
    virtual void setSklAnim(s32 index, Animation* anim) = 0;
    virtual void setTexAnim(s32 index, Animation* anim) = 0;
    virtual void setShuAnim(s32 index, Animation* anim) = 0;
    virtual void setVisAnim(s32 index, Animation* anim) = 0;
    virtual void setShaAnim(s32 index, Animation* anim) = 0;
    virtual Animation* const* getSklAnims() const = 0;
    virtual Animation* const* getTexAnims() const = 0;
    virtual Animation* const* getShuAnims() const = 0;
    virtual Animation* const* getVisAnims() const = 0;
    virtual Animation* const* getShaAnims() const = 0;

    s32 opaBufferIndex;
    s32 xluBufferIndex;
};

static_assert(sizeof(Model) == 0x28, "Model size mismatch");
