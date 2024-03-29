#pragma once

#include "game/graphics/model/renderobj.h"
#include "game/graphics/model/animation.h"
#include "game/graphics/model/material.h"
#include "shadow/aglDepthShadow.h"
#include "heap/seadHeap.h"
#include "geom/seadSphere.h"

class ObjLayer;

class Model : public RenderObj, public sead::IDisposer {
    SEAD_RTTI_OVERRIDE_DECL(Model, RenderObj);

public:
    Model();
    virtual ~Model();

    virtual void updateAnimations() = 0;
    virtual void updateModel() = 0;
    virtual void setMtxRT(const sead::Matrix34f& rt) = 0;
    virtual const sead::Matrix34f& getMtxRT() const = 0;
    virtual void setScale(const sead::Vector3f& scale) = 0;
    virtual const sead::Vector3f& getScale() const = 0;
    virtual bool hasOpa() const = 0;
    virtual bool hasXlu() const = 0;
    virtual s32 searchBoneIndex(const sead::SafeString& name) const = 0;
    virtual const char* getBoneName(s32 index) const = 0;
    virtual u32 getBoneNum() const = 0;
    virtual void setBoneLocalMatrix(s32 index, const sead::Matrix34f& rt, const sead::Vector3f& scale) = 0;
    virtual void getBoneLocalMatrix(s32 index, sead::Matrix34f* rt, sead::Vector3f* scale) const = 0;
    virtual void setBoneWorldMatrix(s32 index, const sead::Matrix34f& mtx) = 0;
    virtual void getBoneWorldMatrix(s32 index, sead::Matrix34f* mtx) const = 0;
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
