#pragma once

#include "sead/controller.h"

class WrappedController : public sead::ControllerWrapper { // Size: 0x194
public:
    WrappedController();
    virtual ~WrappedController();

    void init(u32 controllerNumber);

    void calc() override;
};
