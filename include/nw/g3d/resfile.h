#pragma once

#include <nw/g3d/rescommon.h>

namespace nw { namespace g3d { namespace res {

struct ResFileData {
    BinaryFileHeader mFileHeader;
    u32 mAlignment;
    s32 mOfsName;
    u32 mSizeStringPool;
    s32 mOfsStringPool;
    s32 mOfsModelDic;
    s32 mOfsTextureDic;
    s32 mOfsSkeletalAnimDic;
    s32 mOfsShaderParamAnimDic;
    s32 mOfsColorAnimDic;
    s32 mOfsTexSrtAnimDic;
    s32 mOfsTexPatternAnimDic;
    s32 mOfsBoneVisAnimDic;
    s32 mOfsMatVisAnimDic;
    s32 mOfsShapeAnimDic;
    s32 mOfsSceneAnimDic;
    s32 mOfsExternalFileDic;
    u16 mNumModel;
    u16 mNumTexture;
    u16 mNumSkeletalAnim;
    u16 mNumShaderParamAnim;
    u16 mNumColorAnim;
    u16 mNumTexSrtAnim;
    u16 mNumTexPatternAnim;
    u16 mNumBoneVisAnim;
    u16 mNumMatVisAnim;
    u16 mNumShapeAnim;
    u16 mNumSceneAnim;
    u16 mNumExternalFile;
    u32 mUserPtr;
};

class ResFile : public ResFileData { };

} } }
