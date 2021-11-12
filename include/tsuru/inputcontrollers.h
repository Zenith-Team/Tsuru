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
        controllers[0].init(ControllerID_Wiimote1);
        controllers[1].init(ControllerID_Wiimote2);
        controllers[2].init(ControllerID_Wiimote3);
        controllers[3].init(ControllerID_Wiimote4);
        controllers[4].init(ControllerID_Gamepad);
    }

    // D-Pad

    inline bool buttonUp(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x5); }
    inline bool buttonDown(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x6); }
    inline bool buttonLeft(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x7); }
    inline bool buttonRight(ControllerID controller) const { return nthBit32Right(this->controllers[controller].padHold.bits, 0x8); }

    // Gamepad specific

    inline bool tap() const { return nthBit32Right(this->controllers[ControllerID_Gamepad].padHold.bits, 0xD); }

    // TODO: There's more we can do here

    WrappedController controllers[5];
};
