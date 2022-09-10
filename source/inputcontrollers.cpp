#include "tsuru/inputcontrollers.h"

bool (InputControllers::*InputControllers::DPadFuncTable[4])(InputControllers::ControllerID::__type__) const = {
    &InputControllers::buttonRight,
    &InputControllers::buttonLeft,
    &InputControllers::buttonUp,
    &InputControllers::buttonDown
};
