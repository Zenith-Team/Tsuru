#pragma once

#include "nw/g3d.h"
#include "util/mtx34.h"
#include "resarchive.h"
#include "sead.h"

class SkeletalAnimation;
class TextureAnimation;
class ShaderAnimation;
class VisibilityAnimation;
class ShapeAnimation;

class Model  { // this has 2 base classes
    SEAD_RTTI_BASE(Model)

public:
    class Material;

public:
    // Calculates the drawing resources for skeleton matrices, shapes and materials
    virtual void Calc();

    // Calculates the drawing resources for the view
    virtual void CalcView(s32 viewIndex, const Mtx34& cameraMtx);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Notes:
    // 1. Shadow-only or reflection-only shapes are always invisible
    // 2. Shadow casting for a shape is automatically enabled if "shadow_cast" is not present in its material's render info

    virtual void vf2C(s32 bufferIdx, u32, u32, void*); // always a nullsub

    // These two do not draw shadow-only or reflection-only shapes
    virtual void drawAllShapes1(s32 bufferIdx, u32, u32, void*);
    virtual void drawAllShapes2(s32 bufferIdx, u32, u32, void*);

    // I think this just draws the shadow of shadow-casting shapes
    virtual void drawShadowCastShapes(s32 bufferIdx, u32, u32, void*);

    // These two do not draw reflection-only shapes
    virtual void drawReflectionShapes1(s32 bufferIdx, u32, u32, void*);
    virtual void drawReflectionShapes2(s32 bufferIdx, u32, u32, void*);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    virtual bool hasShadowCastShapes() const;

    virtual ~Model();

    virtual void updateAnimations();
    virtual void updateModel();

    // Rotation + Translation matrix
    virtual void setMtx(const Mtx34& mtxRT);
    virtual const Mtx34& getMtx() const;

    virtual void setScale(const Vec3& scale);
    virtual const Vec3& getScale() const;

    // Determines if there are any shapes that can be drawn by draw*Shapes1()
    virtual bool hasShapesFlag1() const;
    // Determines if there are any shapes that can be drawn by draw*Shapes2()
    virtual bool hasShapesFlag2() const;

    virtual s32 getBoneIdx(const sead::SafeString& name) const;
    virtual const char* getBoneName(u32 idx) const;
    virtual u32 getBoneCount() const;
    virtual void setBoneSRT(u32 idx, const Mtx34& mtxRT, const Vec3& scale);
    virtual void getBoneSRT(u32 idx, Mtx34* mtxRT = NULL, Vec3* scale = NULL);
    // World matrix for bone
    virtual void setBoneTransform(u32 idx, const Mtx34& transform);
    virtual void getBoneTransform(u32 idx, Mtx34& transform);
    virtual void setBoneVisibility(u32 idx, bool visibility);
    virtual bool getBoneVisibility(u32 idx) const; // deleted
    virtual u32 getMaterialCount() const;
    virtual s32 getMaterialIdx(const sead::SafeString& name) const;
    virtual const char* getMaterialName(u32 idx) const;
    virtual Material& getMaterial(u32 idx);
    virtual void setMaterialVisibility(u32 idx, bool visibility);
    virtual bool getMaterialVisibility(u32 idx) const; // deleted
    virtual void vf124(); // deleted
    virtual void vf12C(); // gets a flag
    virtual const nw::g3d::Sphere& getBounding();
    virtual void initViewShapesBuffer(void*, void*);
    virtual void getName(sead::SafeString& name) const;
    virtual void setSklAnimRelatedFloat(u32 idx, f32);
    virtual f32 getSklAnimRelatedFloat(); // deleted
    virtual void setSklAnim(u32 idx, const SkeletalAnimation& anim);
    virtual void setTexAnim(u32 idx, const TextureAnimation& anim);
    virtual void setShuAnim(u32 idx, const ShaderAnimation& anim);
    virtual void setVisAnim(u32 idx, const VisibilityAnimation& anim);
    virtual void setShaAnim(u32 idx, const ShapeAnimation& anim);
    virtual const SkeletalAnimation** getSklAnims() const;
    virtual const TextureAnimation** getTexAnims() const;
    virtual const ShaderAnimation** getShuAnims() const;
    virtual const VisibilityAnimation** getVisAnims() const;
    virtual const ShapeAnimation** getShaAnims() const;
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