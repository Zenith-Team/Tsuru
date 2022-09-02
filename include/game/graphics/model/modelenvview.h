#pragma once

#include "agl/uniformblock.h"

class ModelEnvView {
public:
    ModelEnvView();

    s32 viewNum;
    sead::Buffer<agl::UniformBlock> uniformBlocks;
};
