#pragma once

#include "sead.h"
#include "nw/g3d.h"

class Model;

class ResArchive : public sead::IDisposer {
public:
    Model* getModel(const sead::SafeString& rIdentifier, u32 unk1, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* pHeap);
    Model* getModel(const sead::SafeString& rIdentifier, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* pHeap);

    nw::g3d::res::ResFile* mRes;
};

class ResArchiveMgr {
public:
    static ResArchiveMgr* sInstance;

    ResArchive* get(const sead::SafeString& rIdentifier);
};

bool loadActorResArchive(const sead::SafeString& rName, sead::Heap* pHeap);
