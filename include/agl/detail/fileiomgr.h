#pragma once

#include "sead/idisposer.h"
#include "sead/criticalsection.h"

namespace agl { namespace detail {

class FileIOMgr { // Size: 0x5C
    SEAD_SINGLETON_DISPOSER(FileIOMgr)

public:
    struct CreateArg {

    };

public:
    FileIOMgr();
    virtual ~FileIOMgr();

    void initialize(const CreateArg&, sead::Heap* heap);

    void* _10;
    Vec2u _14;
    sead::CriticalSection _1C;
};

static_assert(sizeof(FileIOMgr) == 0x5C, "agl::detail::FileIOMgr size mismatch");

} }
