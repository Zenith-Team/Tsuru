#pragma once

#include "tsuru/utils.h"
#include "game/wrappedcontroller.h"

class InputControllers {
public:
    enum ControllerID {
        ControllerID_Wiimote1,
        ControllerID_Wiimote2,
        ControllerID_Wiimote3,
        ControllerID_Wiimote4,
        ControllerID_Gamepad
    };

public:
    InputControllers()
        : controllers()
    { }

    // Initializes each controller with the appropriate ID
    void init() {
        for (u32 i = 0; i < 5; i++) {
            controllers[i].init((ControllerID) i);
        }
    }

    // Calls calc() on each controller
    //! Do not call this, it is not required, but is just here for it may be needed in the future
    void calc(u32 a, bool b) {
        for (u32 i = 0; i < 5; i++) {
            controllers[i].calc(a, b);
        }
    }

    // TODO: Use sead::BitFlag functions instead of our own

    // D-Pad
    inline bool buttonUp(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x5); }
    inline bool buttonDown(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x6); }
    inline bool buttonLeft(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x7); }
    inline bool buttonRight(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x8); }
    inline bool buttonA(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x1) && nthBit32Right(this->controllers[controller].padHold.bits, 0xE); }

    // Buttons
    inline bool buttonPlus(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0xC); }

    // Gamepad specific

    inline bool tap() const { return nthBit32Right(this->controllers[ControllerID_Gamepad].padHold.bits, 0xD); }

    WrappedController controllers[5];
};
