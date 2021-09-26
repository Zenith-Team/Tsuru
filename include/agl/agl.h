#pragma once

#include <agl/initarg.h>

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


namespace agl {
    
void Initialize(InitArg& arg);
void ModifyEndianU32(bool, void*, u32);

}
