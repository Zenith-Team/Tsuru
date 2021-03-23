#pragma once

#include "nw/g3d.h"
#include "sead.h"

class Model;

class ResArchive : public sead::IDisposer {
public:
    Model* getModel(const sead::SafeString& identifier, u32 unk1, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* heap);
    Model* getModel(const sead::SafeString& identifier, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims, bool unk2, sead::Heap* heap);

    nw::g3d::res::ResFile* res;
};

class ResArchiveMgr {
public:
    static ResArchiveMgr* instance;

    ResArchive* get(const sead::SafeString& identifier);
};

bool loadActorResArchive(const sead::SafeString& name, sead::Heap* heap=nullptr);
