#pragma once

#include "nw/g3d/res/resmodel.h"
#include "nw/g3d/fnd/buffer.h"

namespace nw { namespace g3d {

class SkeletonObj;
class ShapeObj;
class MaterialObj;
struct Sphere;

class ModelObj {
public:
    res::ResModel* res;
    u32* boneVisArray;
    u32* matVisArray;
    u8 numView;
    u8 viewDependent;
    u16 flag;
    fnd::GfxBuffer* viewBlockArray;
    u16 numShape;
    u16 numMaterial;
    SkeletonObj* skeleton;
    ShapeObj* shapeArray;
    MaterialObj* materialArray;
    Sphere* bounding;
    void* userPtr;
    void* bufferPtr;
    void* blockBuffer;
};

} }
