#pragma once

#include <agl/initarg.h>

#include <agl/attributelocation.h>
#include <agl/displaylist.h>
#include <agl/indexstream.h>

// Render
#include <agl/renderbuffer.h>
#include <agl/rendertargetcolor.h>
#include <agl/rendertargetdepth.h>

// Texture
#include <agl/texturedata.h>
#include <agl/texturesampler.h>

// Vertex
#include <agl/vertexattribute.h>
#include <agl/vertexbuffer.h>

// Driver
#include <agl/driver/gx2resource.h>

// Shader
#include <agl/shader.h>
#include <agl/shaderprogram.h>
#include <agl/shaderprogramarchive.h>

// Layer
#include <agl/lyr/drawmethod.h>
#include <agl/lyr/layer.h>
#include <agl/lyr/renderer.h>
#include <agl/lyr/renderinfo.h>

// Utility
#include <agl/utl/debugtexturepage.h>
#include <agl/utl/inamedobj.h>
#include <agl/utl/iparameterobj.h>
#include <agl/utl/parameterbase.h>

namespace agl {
    
void Initialize(InitArg& arg);
void ModifyEndianU32(bool, void*, u32);

}
