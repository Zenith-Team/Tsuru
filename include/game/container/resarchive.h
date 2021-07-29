#pragma once

#include "sead.h"
#include "nw/g3d.h"

class Model;

class ResArchive : public sead::IDisposer {
public:
    Model* getModel(const sead::SafeString& identifier, u32 unk1, u32 numSklAnims, u32 numTexPatternAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* heap);
    Model* getModel(const sead::SafeString& identifier, u32 numSklAnims, u32 numTexPatternAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* heap);

    nw::g3d::res::ResFile* mRes;
};

class ResArchiveMgr {
public:
    static ResArchiveMgr* sInstance;

    ResArchive* get(const sead::SafeString& identifier);
};

bool loadActorResArchive(const sead::SafeString& name, sead::Heap* heap);
