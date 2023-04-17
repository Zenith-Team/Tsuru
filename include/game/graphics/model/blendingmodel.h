#pragma once

#include "game/graphics/model/modelnw.h"

class CalcRatio { // Size: 0x14
public:
    CalcRatio();

    f32 ratioSource;
    f32 ratioTarget;
    f32 counter;
    f32 invDuration;
    bool isActive;
};

static_assert(sizeof(CalcRatio) == 0x14, "CalcRatio size mismatch");

class BlendingModel : public ModelWrapper { // Size: 0x48
public:
    BlendingModel(Model* model, u32 numSklAnims, u32 numTexPatternAnims, u32 numTexSrtAnims, u32 numVisAnims, u32 numShaAnims);
    void updateModel();

    void calcBlend();

    void setSklAnim(ResArchive* res, const sead::SafeString& name, f32 blendDuration);
    void setSklAnim(const sead::SafeString& name, f32 blendDuration, bool loop = true, f32 rate = 1.0f, f32 frame = 0.0f);
    void setSklAnim(const sead::SafeString& name, bool loop = true, f32 rate = 1.0f, f32 frame = 0.0f);

    static BlendingModel* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims, u32 numTexPatternAnims = 0, u32 numTexSrtAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        ResArchive* archive = ResArchiveMgr::instance()->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims, unk2, nullptr);
        BlendingModel* mdl = new BlendingModel(model, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims);
        mdl->setup(archive);
        return mdl;
    }

    static BlendingModel* create(ResArchive* archive, const sead::SafeString& modelIdentifier, u32 numSklAnims, u32 numTexPatternAnims = 0, u32 numTexSrtAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false) {
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims, unk2, nullptr);
        BlendingModel* mdl = new BlendingModel(model, numSklAnims, numTexPatternAnims, numTexSrtAnims, numVisAnims, numShaAnims);
        mdl->setup(archive);
        return mdl;
    }

    CalcRatio calcRatio;
    u32 currentAnimIndex;
};

static_assert(sizeof(BlendingModel) == 0x48, "BlendingModel size mismatch");
