#pragma once

#include "sead/camera.h"
#include "sead/controller.h"

namespace agl { namespace utl {

class DevTools {
public:
    static void controlCamera(sead::LookAtCamera camera, const sead::Controller& controller);
    
};

} }
