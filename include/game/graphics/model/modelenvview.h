#pragma once

#include "common/aglUniformBlock.h"

class ModelEnvView {
public:
    ModelEnvView();

    s32 viewNum;
    sead::Buffer<agl::UniformBlock> uniformBlocks;
};
