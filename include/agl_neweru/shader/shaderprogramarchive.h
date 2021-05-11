#pragma once

#include "sead.h"
#include "types.h"
#include "agl/shader.h"

namespace agl {

class ShaderProgramArchive : public sead::IDisposer {
public:
    ShaderProgramArchive();
    ~ShaderProgramArchive();

    s32 searchShaderProgramIndex(sead::SafeStringBase<char>* name);

    void* resBinaryShaderArchive;
    u32 _14;
    List<ShaderProgram> programs;
    u32 _20;
	u32 _24;
	u16 _28;
	u16 _2A;
	u32 _2C;
	u32 _30;
	u32 _34;
	u32 _38;
	u32 _3C;
	u32 _40;
	u32 _44;
	u32 _48;
};

}
