#pragma once

#include <agl/initarg.h>

#include <agl/attributelocation.h>
#include <agl/displaylist.h>

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
#include <agl/utl/inamedobj.h>
#include <agl/utl/iparameterobj.h>
#include <agl/utl/parameterbase.h>

namespace agl {
    
void Initialize(InitArg& arg);
void ModifyEndianU32(bool, void*, u32);

}
