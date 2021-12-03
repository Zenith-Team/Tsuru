#pragma once

#include <sead/runtimetypeinfo.h>
#include <sead/bitflag.h>

namespace sead {

class ControllerMgr;
class ListNode;

class ControllerInlineBase { // Size: 0x14
                             // This structure appears at the start of multiple controller class constructors and seems to be an inlined base class
    SEAD_RTTI_BASE(ControllerInlineBase)

public:
    virtual void vf20(); // deleted

    u32 _0;
    u32 _4;
    ListNode* _8;
    ControllerMgr* manager;
};

// Type 1 controller classes

class ControllerBase { // Size: 0x130
public:
    ControllerBase(u32 padBitMax, u32 leftStickCrossStartBit, u32 rightStickCrossStartBit, u32 touchKeyBit);

    u32 createStickCrossMask_();
    u32 getStickHold_(u32, const Vec2f&, f32, u32); //? Is this static? It doesn't use the this pointer at all
    u32 isIdleBase_();
    void setIdleBase_();
    void setPadRepeat(u32, u8 delays, u8 pulses);
    void updateDerivativeParams_(u32, bool);

    BitFlag32 padTrig;
    BitFlag32 padRelease;
    BitFlag32 padRepeat;
    BitFlag32 pointerFlag;
    Vec2i pointerS32;
    u8 pointerBound[16]; //? Is this a sead::BoundBox?
    u32 padHoldCounts[32];
    u8 padRepeatDelays[32];
    u8 padRepeatPulses[32];
    f32 leftStickHoldThreshold;
    f32 rightStickHoldThreshold;
    f32 leftStickReleaseThreshold;
    f32 rightStickReleaseThreshold;
    s32 padBitMax;
    u32 leftStickCrossStartBit;
    u32 rightStickCrossStartBit;
    u32 touchKeyBit;
    u32 idleFrame;
    BitFlag32 padHold;
    Vec2f pointer;
    Vec2f leftStick;
    Vec2f rightStick;
    f32 leftAnalogTrigger;
    f32 rightAnalogTrigger;
};

static_assert(sizeof(ControllerBase) == 0x130, "sead::ControllerBase size mismatch");

class Controller : public ControllerBase { // Size: 0x15C
    SEAD_RTTI_BASE(Controller)

public:
    Controller(ControllerMgr* manager);

    virtual void calc();

    virtual bool isConnected();
    virtual void calcImpl_() = 0;

    // Returns isIdleBase_()
    virtual u32 isIdle_();

    virtual void vf44(); // deleted

    ControllerInlineBase _130;  //? Is this class something along the lines of "ControllerMgrConnection"?
    u8 _144[20];                // Unknown values
};

static_assert(sizeof(Controller) == 0x15C, "sead::Controller size mismatch");

class CafeDRCController : public Controller { // Size: 0x190
    SEAD_RTTI_OVERRIDE(CafeDRCController, Controller)

public:
    struct TouchPanelInfo { // Size: 0xC
        TouchPanelInfo();

        f32* _0;    // Points to x of a Vec2f which seems to be related to default pointer positions; touchX?
        f32* _4;    // Points to y of a Vec2f which seems to be related to default pointer positions; touchY?
        u32 _8;     // Inited to 0
    };

public:
    CafeDRCController(ControllerMgr* manager);

    // Returns this->connected
    bool isConnected() override;

    void calcImpl_() override;

    // Param 2 is unused
    void updateTouchPanelInfo_(TouchPanelInfo* panelInfo, bool, f32 trigBits, f32 releaseBits);

    bool connected;
    u32 _160;
    u32 _164;
    u32 _168;
    TouchPanelInfo touchPanelInfos[3];
};

static_assert(sizeof(CafeDRCController) == 0x190, "sead::CafeDRCController size mismatch");

class CafeRemoteController : public Controller { // Size: 0x164
    SEAD_RTTI_OVERRIDE(CafeRemoteController, Controller)

public:
    CafeRemoteController(ControllerMgr* manager, u32 _15C);

    // Returns this->connected
    bool isConnected() override;

    void calcImpl_() override;

    u32 _15C; //? Wiimote number?
    s8 _160;
    s8 _161;
    bool connected;
    u8 _163;
};

static_assert(sizeof(CafeRemoteController) == 0x164, "sead::CafeRemoteController size mismatch");

class CafeDebugController : public Controller { // Size: 0x164
    SEAD_RTTI_OVERRIDE(CafeDebugController, Controller)

public:
    CafeDebugController(ControllerMgr* manager, u32 _15C);
    virtual ~CafeDebugController();

    bool isConnected() override;
    void calcImpl_() override;

    u32 _15C;
    u8 _160;
};

static_assert(sizeof(CafeDebugController) == 0x164, "sead::CafeDebugController size mismatch");

class ControllerWrapperBase : public ControllerBase { // Size: 0x174
    SEAD_RTTI_BASE(ControllerWrapperBase)

public:
    ControllerWrapperBase();
    virtual ~ControllerWrapperBase();

    virtual void calc() = 0;

    // Calls setIdleBase_()
    virtual void setIdle();

    // Returns isIdleBase_()
    virtual u32 isIdle_();

    void copyRepeatSetting(Controller* from);

    void unregister();

    void registerWith(Controller*, bool);

    void setEnable(bool enable);

    u8 _130[12]; // Unknown values
    void* _13C;
    u32 _140;
    bool enabled;
    u32 _148;
    u32 _14C;
    u8 _150[32]; // Unknown values
};

static_assert(sizeof(ControllerWrapperBase) == 0x174, "sead::ControllerWrapperBase size mismatch");

class ControllerWrapper : public ControllerWrapperBase {
    SEAD_RTTI_OVERRIDE(ControllerWrapper, ControllerWrapperBase)

public:
    ControllerWrapper();
    virtual ~ControllerWrapper();

    void calc() override;

    u32 createPadMaskFromControllerPadMask_(u32) const;
    void setPadConfig(s32 bitMax, const u8*, bool);

    u8 _174[32]; // Unknown values
};

// Type 2 controller classes

class CafeVPadDevice : public ControllerInlineBase { // Size: 0xADC
    SEAD_RTTI_OVERRIDE(CafeVPadDevice, ControllerInlineBase)

public:
    struct VPadInfo { // Size: 0xAC8
        VPadInfo();

        u8 _0[0xAC8]; // TODO: I'll do this later
    };

public:
    CafeVPadDevice(ControllerMgr* manager);

    virtual void calc();

    VPadInfo* vpadInfo;
    u8 _18[0xAD4-0x18]; // Unknown values
    s32 storedDataSetsNum;
    s32 errorCode;
};

class CafeWPadDevice : public ControllerInlineBase { // Size: 0x4D40
    SEAD_RTTI_OVERRIDE(CafeVPadDevice, ControllerInlineBase)

public:
    struct KPadInfo { // Size: 0xF08
        KPadInfo();

        u8 _0[0xF08]; // TODO: I'll do this later
    };

public:
    CafeWPadDevice(ControllerMgr* manager);

    virtual void calc();

    u8 _14[4356]; // Unknown values
    KPadInfo kpadInfos[4];
    u8 _4D38[8];  // Unknown values
};

}
