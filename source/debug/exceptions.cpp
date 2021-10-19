#include <log.h>
#include <dynlibs/os/functions.h>
#include <dynlibs/gx2/functions.h>

// Replaces __pure_virtual_called
void handlePVC() {
    LOG("A pure virtual function was called");

    return;
}

// Replaces __deleted_virtual_called
void handleDVC() {
    LOG("A deleted virtual function was called");

    return;

    // TODO: Print a message to the screen

    /* //*Archive:
    // Init OSScreen
    OSScreenInit();
    OSScreenSetBuffers(0xF4000000);
    OSScreenEnable(true);

    while (true) { // Pause
        OSScreenClearBuffer(0);
        OSScreenPutFont(0, 1, "A deleted virtual function was called");
        OSScreenFlipBuffers();
    } */
}
