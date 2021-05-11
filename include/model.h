#pragma once

#include "renderobjlayer.h"
#include "resarchive.h"

class Model : public RenderObjLayer::Node {
    SEAD_RTTI_OVERRIDE(Model, RenderObjLayer::Node)

public:
    class Material /*: public RenderObjLayer::Node::Material*/;

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

    void setScale(const Vec3& scale) override;
    const Vec3& getScale() const override;

    // Determines if there are any shapes that can be drawn by draw*Shapes1()
    bool hasShapesFlag1() const override;
    // Determines if there are any shapes that can be drawn by draw*Shapes2()
    bool hasShapesFlag2() const override;

    s32 getBoneIdx(const sead::SafeString& name) const override;
    const char* getBoneName(u32 idx) const override;
    u32 getBoneCount() const override;
    void setBoneSRT(u32 idx, const Mtx34& mtxRT, const Vec3& scale) override;
    void getBoneSRT(u32 idx, Mtx34* mtxRT = NULL, Vec3* scale = NULL) override;
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


struct Animation {
    enum Flags {
        FlagRepeat  = 1 << 0,
        FlagUnk2    = 1 << 1,
        FlagIsDone  = 1 << 5,
    };

    void setRepeat(bool repeat);

    inline bool isAnimationDone() { return flags & FlagIsDone; }

    f32 startFrame; // 0    Inited to 0.0
    f32 endFrame;   // 4    Inited to 1.0
    f32 _8;         // 8    Inited to 0.0
    f32 _C;         // C    Inited to 1.0
    f32 frame;      // 10   Inited to 0.0
    f32 speed;      // 14   Inited to 1.0
    u32 flags;      // 18   Inited to FlagRepeat | FlagUnk2
};

class ModelAnimation : public Animation {
public:
    ModelAnimation();
    virtual void calculate() = 0;
};

class SkeletalAnimation : public ModelAnimation {  // size: 0x98
public:
    SkeletalAnimation();
    void calculate() override;

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& identifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation {
public:
    TextureAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShaderAnimation : public ModelAnimation {
public:
    ShaderAnimation();
    void calculate() override;

    void playColorAnim(ResArchive* archive, const sead::SafeString& identifier);
    void playTexSrtAnim(ResArchive* archive, const sead::SafeString& identifier);
};

class VisibilityAnimation : public ModelAnimation {
public:
    VisibilityAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShapeAnimation : public ModelAnimation {
public:
    ShapeAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};


class ModelWrapper {
public:
    ModelWrapper(Model* model, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* archive, void* unk, sead::Heap* heap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtxRT) {
        model->setMtx(mtxRT);
    }

    inline const Mtx34& getMtx() const {
        return model->getMtx();
    }

    inline void setScale(const Vec3& scale) {
        model->setScale(scale);
    }

    inline const Vec3& getScale() const {
        return model->getScale();
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < sklAnims.mSize)
            sklAnims[idx]->play(archive, identifier);
    }

    inline void playTexPatternAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < texAnims.mSize)
            texAnims[idx]->play(archive, identifier);
    }

    inline void playColorAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < shuAnims.mSize)
            shuAnims[idx]->playColorAnim(archive, identifier);
    }

    inline void playTexSrtAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < shuAnims.mSize)
            shuAnims[idx]->playTexSrtAnim(archive, identifier);
    }

    inline void playBoneVisAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < visAnims.mSize)
            visAnims[idx]->play(archive, identifier);
    }

    inline void playShapeAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < shaAnims.mSize)
            shaAnims[idx]->play(archive, identifier);
    }

    static inline ModelWrapper* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        ResArchive* archive = ResArchiveMgr::instance->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

    static inline ModelWrapper* create(ResArchive* archive, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

	Model* model;                                   // 0
	ResArchive* archive;                            // 4
	sead::Buffer<SkeletalAnimation*> sklAnims;      // 8
	sead::Buffer<TextureAnimation*> texAnims;       // 10
	sead::Buffer<ShaderAnimation*> shuAnims;        // 18
	sead::Buffer<VisibilityAnimation*> visAnims;    // 20
	sead::Buffer<ShapeAnimation*> shaAnims;         // 28
};