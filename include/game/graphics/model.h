#pragma once

#include "game/container/resarchive.h"
#include "game/graphics/renderobjlayer.h"

class Model : public RenderObjLayer::Node {
    SEAD_RTTI_OVERRIDE(Model, RenderObjLayer::Node)

public:
    class Material;

public:
    // Calculates the drawing resources for skeleton matrices, shapes and materials
    void Calc() override;

    // Calculates the drawing resources for the view
    void CalcView(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Notes:
    // 1. Shadow-only or reflection-only shapes are always invisible
    // 2. Shadow casting for a shape is automatically enabled if "shadow_cast" is not present in its material's render info

    void vf2C(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override; // always a nullsub

    // These two do not draw shadow-only or reflection-only shapes
    void drawAllShapes1(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;
    void drawAllShapes2(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;

    // I think this just draws the shadow of shadow-casting shapes
    void drawShadowCastShapes(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;

    // These two do not draw reflection-only shapes
    void drawReflectionShapes1(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;
    void drawReflectionShapes2(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool hasShadowCastShapes() const override;

    virtual ~Model();

    void updateAnimations() override;
    void updateModel() override;

    // Rotation + Translation matrix
    void setMtx(const Mtx34& mtxRT) override;
    const Mtx34& getMtx() const override;

    void setScale(const Vec3f& scale) override;
    const Vec3f& getScale() const override;

    // Determines if there are any shapes that can be drawn by draw*Shapes1()
    bool hasShapesFlag1() const override;
    // Determines if there are any shapes that can be drawn by draw*Shapes2()
    bool hasShapesFlag2() const override;

    s32 getBoneIdx(const sead::SafeString& name) const override;
    const char* getBoneName(u32 idx) const override;
    u32 getBoneCount() const override;
    void setBoneSRT(u32 idx, const Mtx34& mtxRT, const Vec3f& scale) override;
    void getBoneSRT(u32 idx, Mtx34* mtxRT = NULL, Vec3f* scale = NULL) override;
    // World matrix for bone
    void setBoneTransform(u32 idx, const Mtx34& transform) override;
    void getBoneTransform(u32 idx, Mtx34& transform) override;
    void setBoneVisibility(u32 idx, bool visibility) override;
    bool getBoneVisibility(u32 idx) const override; // deleted
    u32 getMaterialCount() const override;
    s32 getMaterialIdx(const sead::SafeString& name) const override;
    const char* getMaterialName(u32 idx) const override;
    RenderObjLayer::Node::Material& getMaterial(u32 idx) override;
    void setMaterialVisibility(u32 idx, bool visibility) override;
    bool getMaterialVisibility(u32 idx) const override; // deleted
    void vf124() override; // deleted
    void vf12C() override; // gets a flag
    const nw::g3d::Sphere& getBounding() override;
    void initViewShapesBuffer(void*, void*) override;
    void getName(sead::SafeString& name) const override;
    void setSklAnimRelatedFloat(u32 idx, f32) override;
    f32 getSklAnimRelatedFloat() override; // deleted
    void setSklAnim(u32 idx, const SkeletalAnimation& anim) override;
    void setTexAnim(u32 idx, const TextureAnimation& anim) override;
    void setShuAnim(u32 idx, const ShaderAnimation& anim) override;
    void setVisAnim(u32 idx, const VisibilityAnimation& anim) override;
    void setShaAnim(u32 idx, const ShapeAnimation& anim) override;
    const SkeletalAnimation** getSklAnims() const override;
    const TextureAnimation** getTexAnims() const override;
    const ShaderAnimation** getShuAnims() const override;
    const VisibilityAnimation** getVisAnims() const override;
    const ShapeAnimation** getShaAnims() const override;

    // ...
};

class Animation {
public:
    enum Flags {
        FlagRepeat = 1 << 0,
        FlagUnk2   = 1 << 1,
        FlagIsDone = 1 << 5
    };

    void setRepeat(bool repeat);

    inline bool isAnimationDone() {
        return mFlags & FlagIsDone;
    }

    f32 mStartFrame; // 0    Inited to 0.0
    f32 mEndFrame;   // 4    Inited to 1.0
    f32 _8;          // 8    Inited to 0.0
    f32 _C;          // C    Inited to 1.0
    f32 mFrame;      // 10   Inited to 0.0
    f32 mSpeed;      // 14   Inited to 1.0
    u32 mFlags;      // 18   Inited to FlagRepeat | FlagUnk2
};

class ModelAnimation : public Animation {
public:
    ModelAnimation();
    
    virtual void calculate() = 0;
};

class SkeletalAnimation : public ModelAnimation {
public:
    SkeletalAnimation();

    void calculate() override;

    void init(Model* pModel, ResArchive* pArchive, void* unk, sead::Heap* pHeap);
    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation {
public:
    TextureAnimation();

    void calculate() override;

    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class ShaderAnimation : public ModelAnimation {
public:
    ShaderAnimation();

    void calculate() override;

    void playColorAnim(ResArchive* pArchive, const sead::SafeString& rIdentifier);
    void playTexSrtAnim(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class VisibilityAnimation : public ModelAnimation {
public:
    VisibilityAnimation();

    void calculate() override;

    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class ShapeAnimation : public ModelAnimation {
public:
    ShapeAnimation();

    void calculate() override;

    void play(ResArchive* pArchive, const sead::SafeString& rIdentifier);
};

class ModelWrapper {
public:
    ModelWrapper(Model* pModel, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* pArchive, void* unk, sead::Heap* pHeap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtxRT) {
        mModel->setMtx(mtxRT);
    }

    inline const Mtx34& getMtx() const {
        return mModel->getMtx();
    }

    inline void setScale(const Vec3f& scale) {
        mModel->setScale(scale);
    }

    inline const Vec3f& getScale() const {
        return mModel->getScale();
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < mSklAnims.mSize)
            mSklAnims[idx]->play(mArchive, identifier);
    }

    inline void playTexPatternAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < mTexAnims.mSize)
            mTexAnims[idx]->play(mArchive, identifier);
    }

    inline void playColorAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < mShuAnims.mSize)
            mShuAnims[idx]->playColorAnim(mArchive, identifier);
    }

    inline void playTexSrtAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < mShuAnims.mSize)
            mShuAnims[idx]->playTexSrtAnim(mArchive, identifier);
    }

    inline void playBoneVisAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < mVisAnims.mSize)
            mVisAnims[idx]->play(mArchive, identifier);
    }

    inline void playShapeAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < mShaAnims.mSize)
            mShaAnims[idx]->play(mArchive, identifier);
    }

    static inline ModelWrapper* create(const sead::SafeString& rArchiveIdentifier, const sead::SafeString& rModelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        ResArchive* archive = ResArchiveMgr::sInstance->get(rArchiveIdentifier);
        Model* model = archive->getModel(rModelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

    static inline ModelWrapper* create(ResArchive* pArchive, const sead::SafeString& rModelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        Model* model = pArchive->getModel(rModelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(pArchive, nullptr, nullptr);
        return wrapper;
    }

	Model* mModel;                                   // 0
	ResArchive* mArchive;                            // 4
	sead::Buffer<SkeletalAnimation*> mSklAnims;      // 8
	sead::Buffer<TextureAnimation*> mTexAnims;       // 10
	sead::Buffer<ShaderAnimation*> mShuAnims;        // 18
	sead::Buffer<VisibilityAnimation*> mVisAnims;    // 20
	sead::Buffer<ShapeAnimation*> mShaAnims;         // 28
};
