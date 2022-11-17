#pragma once

#include "nw/g3d/res/resfile.h"

namespace nw { namespace g3d { namespace res {

struct ResModelData {
    BinaryBlockHeader blockHeader;
    BinString ofsName;
    BinString ofsPath;
    Offset ofsSkeleton;
    Offset ofsVertexArray;
    Offset ofsShapeDict;
    Offset ofsMaterialDict;
    Offset ofsUserDataDict;
    u16 numVertices;
    u16 numShapes;
    u16 numMaterials;
    u16 numUserData;
    u32 totalProcessVertices;
    BinPtr userPtr;
};

class ResModel : private ResModelData {
public:
    void Setup();
    void Cleanup();
    void Reset();

    // TODO
};

} } }
