#include "log.h"
#include "dynlibs/os/functions.h"
#include "dynlibs/gx2/functions.h"

// Replaces __pure_virtual_called
void handlePVC() {
    PRINT("A pure virtual function was called");

    OSFatal("Pure virtual function called");
}

// Replaces __deleted_virtual_called
void handleDVC() {
    PRINT("A deleted virtual function was called");

    OSFatal("A deleted virtual function was called");
}
