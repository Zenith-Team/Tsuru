#pragma once

#include "nw/g3d.h"
#include "game/graphics/layer/objlayer.h"

class SkeletalAnimation;
class TextureAnimation;
class ShaderAnimation;
class VisibilityAnimation;
class ShapeAnimation;

class RenderObjLayer : public ObjLayer {
public:
    class Node : public ObjLayer::Node, public sead::IDisposer {
        SEAD_RTTI_OVERRIDE(Node, ObjLayer::Node)

    public:
        class Material;

    public:
        Node();
        virtual ~Node();

        virtual void updateAnimations() = 0;
        virtual void updateModel() = 0;
        virtual void setMtx(const Mtx34& mtxRT) = 0;
        virtual const Mtx34& getMtx() const = 0;
        virtual void setScale(const Vec3f& scale) = 0;
        virtual const Vec3f& getScale() const = 0;
        virtual bool hasShapesFlag1() const = 0;
        virtual bool hasShapesFlag2() const = 0;
        virtual s32 getBoneIdx(const sead::SafeString& name) const = 0;
        virtual const char* getBoneName(u32 idx) const = 0;
        virtual u32 getBoneCount() const = 0;
        virtual void setBoneSRT(u32 idx, const Mtx34& mtxRT, const Vec3f& scale) = 0;
        virtual void getBoneSRT(u32 idx, Mtx34* mtxRT, Vec3f* scale) = 0;
        virtual void setBoneTransform(u32 idx, const Mtx34& transform) = 0;
        virtual void getBoneTransform(u32 idx, Mtx34& transform) = 0;
        virtual void setBoneVisibility(u32 idx, bool visibility) = 0;
        virtual bool getBoneVisibility(u32 idx) const = 0;
        virtual u32 getMaterialCount() const = 0;
        virtual s32 getMaterialIdx(const sead::SafeString& name) const = 0;
        virtual const char* getMaterialName(u32 idx) const = 0;
        virtual Material& getMaterial(u32 idx) = 0;
        virtual void setMaterialVisibility(u32 idx, bool visibility) = 0;
        virtual bool getMaterialVisibility(u32 idx) const = 0;
        virtual void vf124() = 0;
        virtual void vf12C() = 0;
        virtual const nw::g3d::Sphere& getBounding() = 0;
        virtual void initViewShapesBuffer(void*, void*) = 0;
        virtual void getName(sead::SafeString& name) const = 0;
        virtual void setSklAnimRelatedFloat(u32 idx, f32) = 0;
        virtual f32 getSklAnimRelatedFloat() = 0;
        virtual void setSklAnim(u32 idx, const SkeletalAnimation& anim) = 0;
        virtual void setTexPatternAnim(u32 idx, const TextureAnimation& anim) = 0;
        virtual void setTexSrtAnim(u32 idx, const ShaderAnimation& anim) = 0;
        virtual void setVisAnim(u32 idx, const VisibilityAnimation& anim) = 0;
        virtual void setShaAnim(u32 idx, const ShapeAnimation& anim) = 0;
        virtual const SkeletalAnimation** getSklAnims() const = 0;
        virtual const TextureAnimation** getTexPatternAnims() const = 0;
        virtual const ShaderAnimation** getTexSrtAnims() const = 0;
        virtual const VisibilityAnimation** getVisAnims() const = 0;
        virtual const ShapeAnimation** getShaAnims() const = 0;

        s32 _20;
        s32 _24;
    };

public:
    RenderObjLayer();
    virtual ~RenderObjLayer();

    u32 vf24() override;
    void vf2C(void*, u32) override;
    void doInitialize(sead::Heap* heap) override;

    bool vf54(u32) override;

    void vf64(u32) override;

    Mtx44 _42C;
    u8 _46C;
    f32 _470;
    f32 _474;
};

static_assert(sizeof(RenderObjLayer) == 0x478, "RenderObjLayer size mismatch");
