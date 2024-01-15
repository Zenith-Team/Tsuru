#pragma once

#include <nw/g3d/res/rescommon.h>

namespace nw { namespace g3d { namespace res {

struct ResDicPatriciaData
{
    u32 size;
    s32 numData;

    struct Node
    {
        u32 refBit;
        u16 idxLeft;
        u16 idxRight;
        BinString ofsName;
        Offset ofsData;
    } node[1];
};

class ResDicPatricia : private ResDicPatriciaData
{
public:
    typedef ResDicPatriciaData DataType;

    // TODO
    static ResDicPatricia* ResCast(ResDicPatriciaData* ptr) { return static_cast<ResDicPatricia*>(ptr); }

    int FindIndex(const char* str) const;
};

typedef ResDicPatricia ResDicType;

} } }
