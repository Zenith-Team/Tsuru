#pragma once

#include <game/container/resarchive.h>
#include <game/graphics/renderobjlayer.h>
#include <game/graphics/model/animation.h>

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
    void setTexPatternAnim(u32 idx, const TextureAnimation& anim) override;
    void setTexSrtAnim(u32 idx, const ShaderAnimation& anim) override;
    void setVisAnim(u32 idx, const VisibilityAnimation& anim) override;
    void setShaAnim(u32 idx, const ShapeAnimation& anim) override;
    const SkeletalAnimation** getSklAnims() const override;
    const TextureAnimation** getTexPatternAnims() const override;
    const ShaderAnimation** getTexSrtAnims() const override;
    const VisibilityAnimation** getVisAnims() const override;
    const ShapeAnimation** getShaAnims() const override;

    // ...
};

class ModelWrapper {
public:
    ModelWrapper(Model* model, u32 numSklAnims, u32 numTexPatternAnims, u32 numTexSrtAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* archive, void* unk, sead::Heap* heap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtxRT) {
        this->model->setMtx(mtxRT);
    }

    inline const Mtx34& getMtx() const {
        return this->model->getMtx();
    }

    inline void setScale(const Vec3f& scale) {
        this->model->setScale(scale);
    }

    inline const Vec3f& getScale() const {
        return this->model->getScale();
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < this->sklAnims.size)
            this->sklAnims[idx]->play(this->archive, identifier);
    }

    inline void playTexPatternAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < this->texPatternAnims.size)
            this->texPatternAnims[idx]->play(this->archive, identifier);
    }

    inline void playColorAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < this->texSrtAnims.size)
            this->texSrtAnims[idx]->playColorAnim(this->archive, identifier);
    }

    inline void playTexSrtAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < this->texSrtAnims.size)
            this->texSrtAnims[idx]->playTexSrtAnim(this->archive, identifier);
    }

    inline void playBoneVisAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < this->visAnims.size)
            this->visAnims[idx]->play(this->archive, identifier);
    }

    inline void playShapeAnim(const sead::SafeString& identifier, u32 idx) {
        if (idx < this->shaAnims.size)
            this->shaAnims[idx]->play(this->archive, identifier);
    }

    static inline ModelWrapper* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexPatternAnims = 0, u32 numTexSrtAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        ResArchive* archive = ResArchiveMgr::instance()->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

    static inline ModelWrapper* create(ResArchive* archive, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexPatternAnims = 0, u32 numTexSrtAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

	Model* model;                                      // 0
	ResArchive* archive;                               // 4
	sead::Buffer<SkeletalAnimation*> sklAnims;         // 8
	sead::Buffer<TextureAnimation*> texPatternAnims;  // 10
	sead::Buffer<ShaderAnimation*> texSrtAnims;        // 18
	sead::Buffer<VisibilityAnimation*> visAnims;       // 20
	sead::Buffer<ShapeAnimation*> shaAnims;            // 28
};
