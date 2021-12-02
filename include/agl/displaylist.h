#pragma once

#include <types.h>
#include <sead/heap.h>

namespace agl {

class DisplayList { // Size: 0x10
public:
    DisplayList();
    virtual ~DisplayList();

    void clear();
    void setBuffer(u8*, u32);
    void copyTo(DisplayList& out);

    u32 beginDisplayList(u32);  // Param is unused
    void beginDisplayListBuffer(u8*, u32);
    void beginDisplayListTemporary(u32);

    void endDisplayList(u32);   // Param is unused
    DisplayList* endDisplayListBuffer(sead::Heap*);
    DisplayList* endDisplayListTemporary(sead::Heap*);

    u32 _0;
    u32 _4;
    u32 _8;
};

static_assert(sizeof(DisplayList) == 0x10, "agl::DisplayList size mismatch");

}
