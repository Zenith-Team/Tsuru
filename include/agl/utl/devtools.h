#pragma once

#include <sead/camera.h>

namespace agl { namespace utl {

class DevTools { // TODO: This class has a lot more
public:
    static void controlCamera(sead::LookAtCamera camera, const void* controller);   // Second parameter is actually const sead::Controller&
};

} }
