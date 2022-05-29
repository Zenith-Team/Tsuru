#pragma once

#include "nw/ut/runtimetypeinfo.h"
#include "nw/ut/linkedlist.h"
#include "nw/lyt/drawinfo.h"

namespace nw { namespace lyt {

class Pane;
class GroupContainer;
class ResourceAccessor;

class Layout { // Size: 0x34
    NW_RTTI_BASE(Layout);

public:
    Layout();
    virtual ~Layout();
    virtual void vf1(); // deleted
    virtual void vf2(); // deleted
    virtual void vf3(); // deleted
    virtual void vf4(); // deleted
    virtual void vf5(); // deleted
    virtual void vf6(); // deleted
    virtual void Animate();
    virtual void UpdateAnimFrame(f32 = 1.0f);
    virtual void CalculateMtx(const DrawInfo& drawInfo, bool forceDirty = false);
    virtual void Draw(DrawInfo& drawInfo);
    virtual void SetTagProcessor(void* tagProcessor);
    virtual bool BuildImpl(const void*, void*, const void*, const void*);
    virtual Pane* BuildPaneObj(u32, const void*, const void*, const void*);
    virtual Layout* BuildPartsLayout(const void*, const void*, const void*);

    ut::internal::LinkListImpl animTransList;
    Pane* rootPane;
    GroupContainer* groupContainer;
    f32 width;
    f32 height;
    void* _1C;
    ResourceAccessor* resourceAccessor;
    ut::internal::LinkListImpl partsPaneList;
};

} }

static_assert(sizeof(nw::lyt::Layout) == 0x34, "nw::lyt::Layout size mismatch");
