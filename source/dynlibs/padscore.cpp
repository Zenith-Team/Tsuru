#include "dynlibs/os/functions.h"
#include "dynlibs/padscore/functions.h"

u32 padscoreHandle = 0;

EXPORT_DECL(void, WPADInit);
EXPORT_DECL(void, WPADShutdown);
EXPORT_DECL(int32_t, WPADProbe, WPADChan chan, WPADExtensionType* outExtensionType);
EXPORT_DECL(int32_t, WPADSetDataFormat, WPADChan chan, WPADDataFormat format);
EXPORT_DECL(void, WPADEnableURCC, int32_t enable);
EXPORT_DECL(void, WPADEnableWiiRemote, int32_t enable);
EXPORT_DECL(void, WPADRead, WPADChan chan, void* data);
EXPORT_DECL(void, WPADControlMotor, WPADChan chan, bool motorEnabled);
EXPORT_DECL(void, WPADSetAutoSleepTime, uint8_t time);
EXPORT_DECL(void, WPADDisconnect, WPADChan chan);
EXPORT_DECL(WPADConnectCallback, WPADSetConnectCallback, WPADChan chan, WPADConnectCallback callback);
EXPORT_DECL(WPADExtensionCallback, WPADSetExtensionCallback, WPADChan chan, WPADExtensionCallback callback);
EXPORT_DECL(WPADSamplingCallback, WPADSetSamplingCallback, WPADChan chan, WPADSamplingCallback callback);
EXPORT_DECL(void, KPADInit);
EXPORT_DECL(void, KPADShutdown);
EXPORT_DECL(int32_t, KPADRead, KPADChan chan, KPADStatus* data, uint32_t size);
EXPORT_DECL(int32_t, KPADReadEx, KPADChan chan, KPADStatus* data, uint32_t size, KPADError* error);

void InitAcquirePadscore(void)
{
    if (coreinitHandle == 0)
        InitAcquireOS();

    OSDynLoad_Acquire("padscore.rpl", &padscoreHandle);
}

void InitPadscoreFunctionPointers(void)
{
    u32* funcPointer = 0;

    InitAcquirePadscore();

    OS_FIND_EXPORT(padscoreHandle, WPADInit);
    OS_FIND_EXPORT(padscoreHandle, WPADShutdown);
    OS_FIND_EXPORT(padscoreHandle, WPADProbe);
    OS_FIND_EXPORT(padscoreHandle, WPADSetDataFormat);
    OS_FIND_EXPORT(padscoreHandle, WPADEnableURCC);
    OS_FIND_EXPORT(padscoreHandle, WPADEnableWiiRemote);
    OS_FIND_EXPORT(padscoreHandle, WPADRead);
    OS_FIND_EXPORT(padscoreHandle, WPADControlMotor);
    OS_FIND_EXPORT(padscoreHandle, WPADSetAutoSleepTime);
    OS_FIND_EXPORT(padscoreHandle, WPADDisconnect);
    OS_FIND_EXPORT(padscoreHandle, WPADSetConnectCallback);
    OS_FIND_EXPORT(padscoreHandle, WPADSetExtensionCallback);
    OS_FIND_EXPORT(padscoreHandle, WPADSetSamplingCallback);
    OS_FIND_EXPORT(padscoreHandle, KPADInit);
    OS_FIND_EXPORT(padscoreHandle, KPADShutdown);
    OS_FIND_EXPORT(padscoreHandle, KPADRead);
    OS_FIND_EXPORT(padscoreHandle, KPADReadEx);
}
