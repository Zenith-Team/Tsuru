#pragma once

#include "sead/camera.h"
#include "sead/controller.h"

namespace agl { namespace utl {

class DevTools { // TODO: This class has a lot more
public:
    static void controlCamera(sead::LookAtCamera camera, const sead::Controller& controller);
};

} }
