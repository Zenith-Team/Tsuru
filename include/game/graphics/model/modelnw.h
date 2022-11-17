#pragma once

#include "game/resource/resarchive.h"
#include "game/graphics/layer/renderobjlayer.h"
#include "game/graphics/model/animation.h"
#include "game/graphics/drawmgr.h"
#include "game/graphics/model/model.h"
#include "game/graphics/model/materialnw.h"
#include "agl/shaderprogram.h"
#include "agl/shaderprogramarchive.h"
#include "agl/shaderlocation.h"
#include "agl/g3d/modelshaderassign.h"
#include "agl/g3d/modelex.h"
#include "nw/g3d/shapeobj.h"
#include "nw/g3d/materialobj.h"
#include "nw/g3d/skeletalanimobj.h"
#include "nw/g3d/res/resmodel.h"
#include "sead/ptrarray.h"

class CullViewFrustum;

class ModelNW : public Model {
    SEAD_RTTI_OVERRIDE(ModelNW, Model);

public:
    struct ShaderAssign {
        void initialize(const agl::ShaderProgram* shaderProgram) {
            this->shaderProgram = shaderProgram;

            this->envLocation.setName("MdlEnvView");
            this->mtxLocation.setName("MdlMtx");
            this->shpLocation.setName("Shp");
            this->matLocation.setName("Mat");
            this->sdwLocation.setName("cShadowMap");
            this->rflLocation.setName("cReflectionMap");

            this->updateLocation();
        }

        void updateLocation() {
            if (this->shaderProgram) {
                this->envLocation.search(*this->shaderProgram);
                this->mtxLocation.search(*this->shaderProgram);
                this->shpLocation.search(*this->shaderProgram);
                this->matLocation.search(*this->shaderProgram);
                this->sdwLocation.search(*this->shaderProgram);
                this->rflLocation.search(*this->shaderProgram);
            }
        }

        const agl::ShaderProgram* shaderProgram;
        agl::UniformBlockLocation envLocation, mtxLocation, shpLocation, matLocation;
        agl::SamplerLocation sdwLocation, rflLocation;
    };

    static_assert(sizeof(ShaderAssign) == 0x64, "ModelNW::ShaderAssign size mismatch");

    struct ShapeRenderInfo {
        s32 idxShape;
        s32 priority;
        sead::BitFlag32 flag;
        s32 polygonOffset;
        mutable agl::DisplayList attribDl, matDl;
    };

    static_assert(sizeof(ShapeRenderInfo) == 0x30, "ModelNW::ShapeRenderInfo size mismatch");

    struct LightMap; // TODO
    struct Shape; // TODO

    struct DrawInfo {
        s32 viewIndex;
        const Mtx34* viewMtx;
        const Mtx44* projMtx;
        const agl::ShaderProgram* shaderProgram;
        ShaderAssign* shaderAssign;
        s32 materialIndex;
        bool drawShape;
        bool drawReflection;
        agl::ShaderMode shaderMode;
        s32 polygonOffset;
        const CullViewFrustum* cull;
    };

    static_assert(sizeof(DrawInfo) == 0x28, "ModelNW::DrawInfo size mismatch");

public:
    ModelNW();
    virtual ~ModelNW();

    void calc() override;
    void calcGPU(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;
    virtual void updateView(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;
    virtual void drawOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;
    virtual void drawXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;
    virtual void drawShadowOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;
    virtual void drawReflectionOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;
    virtual void drawReflectionXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) override;

    void updateAnimations() override;
    void updateModel() override;

    bool hasOpa() const override;
    bool hasXlu() const override;

    s32 searchBoneIndex(const sead::SafeString& name) const override;
    const char* getBoneName(s32 idx) const override;
    u32 getBoneNum() const override;

    void setBoneLocalMatrix(s32 idx, const Mtx34& mtx, const Vec3f& scale) override;
    void getBoneLocalMatrix(s32 idx, Mtx34* mtx = nullptr, Vec3f* scale = nullptr) const override;

    void setBoneWorldMatrix(s32 idx, const Mtx34& mtx) override;
    void getBoneWorldMatrix(s32 idx, Mtx34* mtx) const override;

    void setBoneVisible(s32 idx, bool visible) override;
    bool isBoneVisible(s32 idx) const override; // deleted

    u32 getMaterialNum() const override;
    s32 searchMaterialIndex(const sead::SafeString& name) const override;
    const char* getMaterialName(s32 idx) const override;

    Material* getMaterial(s32 idx) const override {
        return this->materials[idx];
    }

    void setMaterialVisible(s32 index, bool visible) override;
    bool isMaterialVisible(s32 index) const override; // deleted

    void setBoundingEnable(bool enable) override; // TODO

    bool isBoundingEnable() const override; // TODO

    const sead::Sphere3f& getBounding() const override {
        return this->bounding;
    }

    void calcViewShapeShadowFlags(agl::sdw::DepthShadow* depthShadow, ObjLayer* shadowLayer, RenderMgr* renderMgr) override;

    sead::SafeString getName() const override; // TODO

    void setSklAnimBlendWeight(s32 index, f32 weight) override {
        this->sklAnimBlendWeights[index] = weight;
    }

    f32 getSklAnimBlendWeight(s32 index) const override {
        return this->sklAnimBlendWeights[index];
    }

    void setSklAnim(s32 index, Animation* anim) override;
    void setTexAnim(s32 index, Animation* anim) override;
    void setShuAnim(s32 index, Animation* anim) override;
    void setVisAnim(s32 index, Animation* anim) override;
    void setShaAnim(s32 index, Animation* anim) override;

    Animation* const* getSklAnims() const override { return reinterpret_cast<Animation* const*>(this->sklAnims.buffer); }
    Animation* const* getTexAnims() const override { return reinterpret_cast<Animation* const*>(this->texAnims.buffer); }
    Animation* const* getShuAnims() const override { return reinterpret_cast<Animation* const*>(this->shuAnims.buffer); }
    Animation* const* getVisAnims() const override { return reinterpret_cast<Animation* const*>(this->visAnims.buffer); }
    Animation* const* getShaAnims() const override { return reinterpret_cast<Animation* const*>(this->shaAnims.buffer); }

    void initialize(nw::g3d::res::ResModel* resModel, const agl::ShaderProgramArchive* shaderArchive, s32 numView, s32 numSklAnim, s32 numTexAnim, s32 numShuAnim, s32 numVisAnim, s32 numShaAnim, u32 boundingMode, sead::Heap* heap);
    void activateMaterial(const agl::g3d::ModelShaderAssign& shaderAssign, const nw::g3d::MaterialObj* material, const LightMap& lightMap) const;
    void setDisplayListDirty();
    void createViewShapeShadowFlagBuffer_(s32 numView, sead::Heap* heap);
    void initializeShapeRenderInfo_(ShapeRenderInfo& renderInfo, const nw::g3d::MaterialObj* material, const nw::g3d::ShapeObj* shape);
    static s32 sortShapeRenderInfoCmp(const ShapeRenderInfo* a, const ShapeRenderInfo* b);
    void calcBounding_();
    void applyBlendWeight_(s32 shapeIndex);
    static void setBoundingFlagArray_(u32 flagArray[], const SkeletalAnimation& anim);

    void drawOpa_(DrawInfo& drawInfo, const RenderMgr* renderMgr) const;
    void drawXlu_(DrawInfo& drawInfo, const RenderMgr* renderMgr) const;

    void drawShape_(DrawInfo& drawInfo, const ShapeRenderInfo& renderInfo, const RenderMgr* renderMgr) const;

    agl::g3d::ModelEx modelEx;
    nw::g3d::SkeletalAnimBlender sklAnimBlender;
    sead::Buffer<SkeletalAnimation*> sklAnims;
    sead::Buffer<TextureAnimation*> texAnims;
    sead::Buffer<ShaderAnimation*> shuAnims;
    sead::Buffer<VisibilityAnimation*> visAnims;
    sead::Buffer<ShapeAnimation*> shaAnims;
    void* buffer;
    void* blockBuffer;
    size_t blockBufferSize;
    void* sklAnimBlenderBuffer;
    sead::Buffer<f32> sklAnimBlendWeights;
    sead::PtrArray<ShapeRenderInfo> opaShapeInfos;
    sead::PtrArray<ShapeRenderInfo> xluShapeInfos;
    sead::Buffer<ShaderAssign> shaderAssigns;
    sead::Buffer<MaterialNW*> materials;
    sead::Buffer<Shape> shapes;
    Mtx34 mtxRT;
    Vec3f scale;
    u8 _128;
    sead::BitFlag32 renderFlag;
    sead::BitFlag32 boundingEnableFlag;
    sead::Buffer<sead::Buffer<sead::BitFlag32> > viewShapeShadowFlagBuffer;
    sead::Sphere3f bounding;
    sead::BoundBox3f* subBounding;
    sead::BitFlag32 shapeFlag;
    u32 boundingFlagArray[10];
    u32 subBoundingFlagArray[10];
    sead::BitFlag32 viewDepthShadowEnableFlag;
    bool displayListDirty;
};

static_assert(sizeof(ModelNW) == 0x1AC, "ModelNW size mismatch");

class ModelWrapper {
public:
    ModelWrapper(Model* model, u32 numSklAnims, u32 numTexPatternAnims, u32 numTexSrtAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* archive, void* unk = nullptr, sead::Heap* heap = nullptr);
    void updateModel();
    void updateAnimations();

    void setMtx(const Mtx34& mtxRT) { this->model->setMtxRT(mtxRT); }
    const Mtx34& getMtx() const { return this->model->getMtxRT(); }

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
            if (!anim)
                return;
            anim->frameCtrl.shouldLoop(loop);
        }
    }

    void draw() {
        DrawMgr::instance()->drawModel(this);
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
