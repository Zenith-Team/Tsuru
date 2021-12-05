#pragma once

#include "sead.h"
#include "nw/g3d.h"

class Model;

class ResArchive : public sead::IDisposer {
public:
    Model* getModel(const sead::SafeString& identifier, u32 unk1, u32 numSklAnims, u32 numTexPatternAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* heap);
    Model* getModel(const sead::SafeString& identifier, u32 numSklAnims, u32 numTexPatternAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* heap);

    nw::g3d::res::ResFile* res;
};

class ResArchiveMgr {
    SEAD_SINGLETON_DISPOSER(ResArchiveMgr)

public:
    ResArchive* get(const sead::SafeString& identifier);
    bool loadResArchive(const sead::SafeString& archiveName, const sead::SafeString& resName, sead::Heap* heap);
};

bool loadActorResArchive(const sead::SafeString& name, sead::Heap* heap);
