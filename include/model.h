#pragma once

#include "sead.h"
#include "util/mtx34.h"
#include "resarchive.h"

class SkeletalAnimation;
class TextureAnimation;
class ShaderAnimation;
class VisibilityAnimation;
class ShapeAnimation;

class Model     // this has 2 base classes
{
    SEAD_RTTI_BASE(Model)

public:
    // Calculates the drawing resources for skeleton matrices, shapes and materials
    virtual void Calc();

    // Calculates the drawing resources for the view
    virtual void CalcView(s32 viewIndex, const Mtx34& cameraMtx);

    virtual void vf2C(s32 bufferIdx, u32, u32, void*); // always a nullsub
    virtual void vf34(s32 bufferIdx, u32, u32, void*);
    virtual void vf3C(s32 bufferIdx, u32, u32, void*);
    virtual void vf44(s32 bufferIdx, u32, u32, void*);
    virtual void vf4C(s32 bufferIdx, u32, u32, void*);
    virtual void vf54(s32 bufferIdx, u32, u32, void*);
    virtual u32 vf5C(); // gets a flag

    virtual ~Model();

    virtual void updateAnimations();
    virtual void updateModel();

    // Rotation + Translation matrix
    virtual void setMtx(const Mtx34& mtx);
    virtual const Mtx34& getMtx() const;

    virtual void setScale(const Vec3& scale);
    virtual const Vec3& getScale() const;

    virtual void vf9C();
    virtual void vfA4();
    virtual s32 getBoneIdx(const sead::SafeString& name) const;
    virtual const char* getBoneName(u32 idx) const;
    virtual u32 getBoneCount() const;
    virtual void vfC4();
    virtual void vfCC();
    virtual void vfD4();
    virtual void getBoneTransform(u32 idx, Mtx34& transform);
    virtual void vfE4();
    virtual void vfEC();                        // deleted
    virtual u32 getMaterialCount() const;
    virtual s32 getMaterialIdx(const sead::SafeString& name) const;
    virtual const char* getMaterialName(u32 idx) const;
    virtual void vf10C();
    virtual void vf114();
    virtual void vf11C();                        // deleted
    virtual void vf124();                        // deleted
    virtual void vf12C();
    virtual void vf134();                        // getBounding?
    virtual void vf13C();
    virtual void getName(sead::SafeString& name) const;
    virtual void vf14C();
    virtual void vf154();                        // deleted
    virtual void setSklAnim(u32 idx, SkeletalAnimation& anim);
    virtual void setTexAnim(u32 idx, TextureAnimation& anim);
    virtual void setShuAnim(u32 idx, ShaderAnimation& anim);
    virtual void setVisAnim(u32 idx, VisibilityAnimation& anim);
    virtual void setShaAnim(u32 idx, ShapeAnimation& anim);
    virtual const SkeletalAnimation** getSklAnims() const;
    virtual const TextureAnimation** getTexAnims() const;
    virtual const ShaderAnimation** getShuAnims() const;
    virtual const VisibilityAnimation** getVisAnims() const;
    virtual const ShapeAnimation** getShaAnims() const;
};


struct Animation
{
    enum Flags
    {
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

class ModelAnimation : public Animation
{
public:
    ModelAnimation();
    virtual void calculate() = 0;
};

class SkeletalAnimation : public ModelAnimation  // size: 0x98
{
public:
    SkeletalAnimation();
    void calculate() override;

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& identifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation
{
public:
    TextureAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShaderAnimation : public ModelAnimation
{
public:
    ShaderAnimation();
    void calculate() override;

    void playColorAnim(ResArchive* archive, const sead::SafeString& identifier);
    void playTexSrtAnim(ResArchive* archive, const sead::SafeString& identifier);
};

class VisibilityAnimation : public ModelAnimation
{
public:
    VisibilityAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShapeAnimation : public ModelAnimation
{
public:
    ShapeAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};


class ModelWrapper
{
public:
    ModelWrapper(Model* model, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* archive, void* unk, sead::Heap* heap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtx)
    {
        model->setMtx(mtx);
    }

    inline const Mtx34& getMtx() const
    {
        return model->getMtx();
    }

    inline void setScale(const Vec3& scale)
    {
        model->setScale(scale);
    }

    inline const Vec3& getScale() const
    {
        return model->getScale();
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < sklAnims.mSize)
            sklAnims[idx]->play(archive, identifier);
    }

    inline void playTexPatternAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < texAnims.mSize)
            texAnims[idx]->play(archive, identifier);
    }

    inline void playColorAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shuAnims.mSize)
            shuAnims[idx]->playColorAnim(archive, identifier);
    }

    inline void playTexSrtAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shuAnims.mSize)
            shuAnims[idx]->playTexSrtAnim(archive, identifier);
    }

    inline void playBoneVisAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < visAnims.mSize)
            visAnims[idx]->play(archive, identifier);
    }

    inline void playShapeAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shaAnims.mSize)
            shaAnims[idx]->play(archive, identifier);
    }

    static inline ModelWrapper* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false)
    {
        ResArchive* archive = ResArchiveMgr::instance->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

    static inline ModelWrapper* create(ResArchive* archive, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false)
    {
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
