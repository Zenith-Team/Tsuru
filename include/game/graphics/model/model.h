#pragma once

#include "game/resource/resarchive.h"
#include "game/graphics/layer/renderobjlayer.h"
#include "game/graphics/model/animation.h"

class Model : public RenderObjLayer::Node {
    SEAD_RTTI_OVERRIDE(Model, RenderObjLayer::Node)

public:
    class Material;

public:
    // Calculates the drawing resources for skeleton matrices, shapes and materials
    void calc() override;

    // Updates buffers for the GPU
    void calcGPU(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) override;

    // Notes:
    // 1. Shadow-only or reflection-only shapes are always invisible
    // 2. Shadow casting for a shape is automatically enabled if "shadow_cast" is not present in its material's render info
    // 3. "Opa" = Opaque & Alphamask, "Xlu" = Translucent

    void drawOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) override;
    void drawXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) override;

    // Draws the shadow of shadow-casting shapes
    void drawShadowOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) override;

    // Draws the reflection on shapes
    void drawReflectionOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) override;
    void drawReflectionXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, ObjLayerRenderer* renderer) override;

    bool hasShadow() const override;

    virtual ~Model();

    void updateAnimations() override;
    void updateModel() override;

    // Sets the model matrix (Rotation + Translation)
    // @param mtxRT Matrix to set
    void setMtx(const Mtx34& mtxRT) override;
    // Gets the model matrix
    // @return Reference to the retrieved matrix
    const Mtx34& getMtx() const override;

    // Sets the scale of the model
    // @param scale Target scale to be set
    void setScale(const Vec3f& scale) override;
    // Gets the scale of the model
    // @return Reference to the retrieved scale
    const Vec3f& getScale() const override;
    bool hasOpa() const override;
    bool hasXlu() const override;
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
    void setup(ResArchive* archive, void* unk = nullptr, sead::Heap* heap = nullptr);
    void updateModel();
    void updateAnimations();

    void setMtx(const Mtx34& mtxRT) { this->model->setMtx(mtxRT); }
    const Mtx34& getMtx() const { return this->model->getMtx(); }

    void setScale(const Vec3f& scale) { this->model->setScale(scale); }
    const Vec3f& getScale() const { return this->model->getScale(); }

    void playSklAnim(const sead::SafeString& identifier, u32 idx = 0) {
        if (idx < this->sklAnims.size)
            this->sklAnims[idx]->play(this->archive, identifier);
    }

    void playTexPatternAnim(const sead::SafeString& identifier, u32 idx = 0) {
        if (idx < this->texPatternAnims.size)
            this->texPatternAnims[idx]->play(this->archive, identifier);
    }

    void playColorAnim(const sead::SafeString& identifier, u32 idx = 0) {
        if (idx < this->texSrtAnims.size)
            this->texSrtAnims[idx]->playColorAnim(this->archive, identifier);
    }

    void playTexSrtAnim(const sead::SafeString& identifier, u32 idx = 0) {
        if (idx < this->texSrtAnims.size)
            this->texSrtAnims[idx]->playTexSrtAnim(this->archive, identifier);
    }

    void playBoneVisAnim(const sead::SafeString& identifier, u32 idx = 0) {
        if (idx < this->visAnims.size)
            this->visAnims[idx]->play(this->archive, identifier);
    }

    void playShapeAnim(const sead::SafeString& identifier, u32 idx = 0) {
        if (idx < this->shaAnims.size)
            this->shaAnims[idx]->play(this->archive, identifier);
    }

    void loopSklAnims(bool loop) {
        for (u32 i = 0; i < sklAnims.size; i++) {
            SkeletalAnimation* anim = sklAnims[i];
            if (!anim) return;
            anim->shouldLoop(loop);
        }
    }

    static ModelWrapper* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexPatternAnims = 0, u32 numTexSrtAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        ResArchive* archive = ResArchiveMgr::instance()->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive);
        return wrapper;
    }

    static ModelWrapper* create(ResArchive* archive, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexPatternAnims = 0, u32 numTexSrtAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive);
        return wrapper;
    }

    Model* model;                                       // 0
    ResArchive* archive;                                // 4
    sead::Buffer<SkeletalAnimation*> sklAnims;          // 8
    sead::Buffer<TextureAnimation*> texPatternAnims;    // 10
    sead::Buffer<ShaderAnimation*> texSrtAnims;         // 18
    sead::Buffer<VisibilityAnimation*> visAnims;        // 20
    sead::Buffer<ShapeAnimation*> shaAnims;             // 28
};
