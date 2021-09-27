#pragma once

#include <sead/idisposer.h>
#include <agl/resbinaryshaderarchive.h>
#include <agl/resshaderarchive.h>
#include <sead/buffer.h>
#include <agl/shaderprogram.h>

namespace agl {

class ShaderProgramArchive : public sead::IDisposer { // Size: 0x4C
public:
    class ShaderProgramEx { // Size: 0x124
    public:
        ShaderProgramEx();
        virtual ~ShaderProgramEx();

        u32 _0;
        u32 _4;
        u8 _8[0x58][3]; // Class array
        Vec2i _110;
        u32 _118;
        u8 _11C;
    };

    class ShaderSource : public sead::IDisposer { // Size: 0x30
        ShaderSource();
        virtual ~ShaderSource();

        u8 _0[0x4]; // Unknown values
        u32 _14;
        u32 _18;
        u32 _1C;
        u32 _20;
        u32 _24;
        Vec2i _28;
    };

public:
    ShaderProgramArchive();
    virtual ~ShaderProgramArchive();

    ResBinaryShaderArchive resBinarySharc;
    ResShaderArchive resSharc;
    sead::Buffer<ShaderProgram> shaderProgramBuffer;
    u32 _20;
    u32 _24;
    u16 _28;
    u16 _2A;
    sead::Buffer<ShaderProgramEx> shaderProgramExBuffer;
    sead::Buffer<ShaderSource> shaderSourceBuffer;
    sead::Buffer<u32> _3C;  //? What is the template param for these?
    sead::Buffer<u32> _44;  //? What is the template param for these?
};

static_assert(sizeof(ShaderProgramArchive) == 0x4C, "agl::ShaderProgramArchive size mismatch");
static_assert(sizeof(ShaderProgramArchive::ShaderProgramEx) == 0x124, "agl::ShaderProgramArchive::ShaderProgramEx size mismatch");
static_assert(sizeof(ShaderProgramArchive::ShaderSource) == 0x30, "agl::ShaderProgramArchive::ShaderSource size mismatch");

}
