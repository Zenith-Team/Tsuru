#pragma once

#include "tsuru/utils.h"
#include "game/wrappedcontroller.h"

class InputControllers {
public:
    ENUM_CLASS(ControllerID,
        Wiimote1,
        Wiimote2,
        Wiimote3,
        Wiimote4,
        Gamepad
    );

public:
    InputControllers()
        : controllers()
    { }

    // Initializes each controller with the appropriate ID
    void init() {
        for (u32 i = 0; i < 5; i++) {
            controllers[i].init((ControllerID::__type__) i);
        }
    }

    inline const WrappedController& ctrl(ControllerID::__type__ i) const { return this->controllers[i]; }

    // D-Pad
    inline bool buttonUp(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 4); }
    inline bool buttonDown(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 5); }
    inline bool buttonLeft(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 6); }
    inline bool buttonRight(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 7); }

    // Buttons
    inline bool buttonA(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 0) && this->ctrl(controller).isHold(1 << 13); }
    inline bool buttonB(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 0) && this->ctrl(controller).isHold(1 << 14); }
    inline bool buttonXY(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 2) && this->ctrl(controller).isHold(1 << 1); }
    inline bool buttonPlus(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 11); }
    inline bool buttonMinus(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 10); }

    // Triggers
    inline bool triggerL(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 3) && this->ctrl(controller).isHold(1 << 8) && this->ctrl(controller).isHold(1 << 16); }
    inline bool triggerR(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 3) && this->ctrl(controller).isHold(1 << 9) && this->ctrl(controller).isHold(1 << 16); }
    inline bool triggerZL(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 3) && this->ctrl(controller).isHold(1 << 16) && this->ctrl(controller).isHold(1 << 17); }
    inline bool triggerZR(ControllerID::__type__ controller) const { return this->ctrl(controller).isHold(1 << 3) && this->ctrl(controller).isHold(1 << 16) && !this->ctrl(controller).isHold(1 << 8) && !this->ctrl(controller).isHold(1 << 16) && !this->ctrl(controller).isHold(1 << 9); }

    // Gamepad specific
    inline bool tap() const { return this->controllers[ControllerID::Gamepad].isHold(1 << 12); }

    // Checks if a direction on the D-Pad is pressed
    // @param index The index of the direction to check, corresponds to Direction::DirectionType
    // @param controller The controller to check
    // @return True if the direction is pressed, false otherwise
    bool DPadDirection(u32 direction, InputControllers::ControllerID::__type__ controller) const {
        return ((this)->*(DPadFuncTable[direction]))(controller);
    }

    static bool (InputControllers::*DPadFuncTable[4])(ControllerID::__type__) const;

    WrappedController controllers[5];
};
