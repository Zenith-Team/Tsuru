#pragma once

#include "list.h"
#include "runtimetypeinfo.h"

namespace sead {

class Resource : public TListNode<Resource*> {
    SEAD_RTTI_BASE(Resource)

public:
    Resource();
    virtual ~Resource();

    virtual void doPostCreate_();
};

class Heap;

class DirectResource : public Resource {
    SEAD_RTTI_OVERRIDE(DirectResource, Resource)

public:
    DirectResource();
    virtual ~DirectResource();

    virtual s32 getLoadDataAlignment();
    virtual void doCreate_(u8*, u32, Heap*);

    // ...
};

}
