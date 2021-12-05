#pragma once

#include "sead/task.h"
#include "sead/list.h"
#include "sead/ptrarray.h"
#include "sead/controller.h"

namespace sead {

class ControllerMgr : public CalculateTask { // Size: 0xE8
    SEAD_RTTI_OVERRIDE(ControllerMgr, CalculateTask)
    SEAD_SINGLETON_TASK(ControllerMgr)

public:
    ControllerMgr(const TaskConstructArg& arg);
    virtual ~ControllerMgr();

    void prepare() override;

    void calc() override;

    void initialize(u32, Heap* heap);
    void initializeDefault(Heap* heap);

    // TODO: Figure out how to use this func
    u32 getControlDevice(u32 deviceID);

    static TaskBase* construct(const TaskConstructArg& arg);

    OffsetList<ControllerInlineBase> devices;
    PtrArray<ControllerBase> controllers;
};

static_assert(sizeof(ControllerMgr) == 0xE8, "sead::ControllerMgr size mismatch");

}
