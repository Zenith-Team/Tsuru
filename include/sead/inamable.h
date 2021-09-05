#pragma once

#include <sead/safestring.h>

namespace sead {

class INamable {
public:
    INamable()
        : INamableName()
    { }

    INamable(const char* str)
        : INamableName(str)
    { }

    ~INamable() { }

    SafeString INamableName;
};

}
