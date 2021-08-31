#pragma once

#include <sead/safestring.h>

namespace sead {

class INamable {
public:
    INamable()
        : inamableName()
    { }

    INamable(const char* str)
        : inamableName(str)
    { }

    ~INamable() { }

    SafeString inamableName;
};

}
