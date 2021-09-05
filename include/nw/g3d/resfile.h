#pragma once

#include <nw/g3d/rescommon.h>

namespace nw { namespace g3d { namespace res {

struct ResFileData {
    BinaryFileHeader fileHeader;
    u32 alignment;
    s32 ofsName;
    u32 sizeStringPool;
    s32 ofsStringPool;
    s32 ofsModelDic;
    s32 ofsTextureDic;
    s32 ofsSkeletalAnimDic;
    s32 ofsShaderParamAnimDic;
    s32 ofsColorAnimDic;
    s32 ofsTexSrtAnimDic;
    s32 ofsTexPatternAnimDic;
    s32 ofsBoneVisAnimDic;
    s32 ofsMatVisAnimDic;
    s32 ofsShapeAnimDic;
    s32 ofsSceneAnimDic;
    s32 ofsExternalFileDic;
    u16 numModel;
    u16 numTexture;
    u16 numSkeletalAnim;
    u16 numShaderParamAnim;
    u16 numColorAnim;
    u16 numTexSrtAnim;
    u16 numTexPatternAnim;
    u16 numBoneVisAnim;
    u16 numMatVisAnim;
    u16 numShapeAnim;
    u16 numSceneAnim;
    u16 numExternalFile;
    u32 userPtr;
};

class ResFile : public ResFileData { };

} } }
