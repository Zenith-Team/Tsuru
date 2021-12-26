#include "tsuru/inputcontrollers.h"

bool (InputControllers::*InputControllers::DPadFuncTable[4])(InputControllers::ControllerID) const = {
    &InputControllers::buttonRight,
    &InputControllers::buttonLeft,
    &InputControllers::buttonUp,
    &InputControllers::buttonDown
};
