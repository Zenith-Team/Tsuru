#pragma once

#include "dynlibs/padscore/types.h"

#ifdef __cplusplus
#include <cstring>
extern "C" {
#else
#include <string.h>
#endif

#include "dynlibs/os/types.h"

void InitPadscoreFunctionPointers(void);
void InitAcquirePadscore(void);

extern void (*WPADInit)();
extern void (*WPADShutdown)();
extern int32_t (*WPADProbe)(WPADChan chan, WPADExtensionType* outExtensionType);
extern int32_t (*WPADSetDataFormat)(WPADChan chan, WPADDataFormat format);
extern void (*WPADEnableURCC)(int32_t enable);
extern void (*WPADEnableWiiRemote)(int32_t enable);
extern void (*WPADRead)(WPADChan chan, void* data);
extern void (*WPADControlMotor)(WPADChan chan, bool motorEnabled);
extern void (*WPADSetAutoSleepTime)(uint8_t time);
extern void (*WPADDisconnect)(WPADChan chan);
extern WPADConnectCallback (*WPADSetConnectCallback)(WPADChan chan, WPADConnectCallback callback);
extern WPADExtensionCallback (*WPADSetExtensionCallback)(WPADChan chan, WPADExtensionCallback callback);
extern WPADSamplingCallback (*WPADSetSamplingCallback)(WPADChan chan, WPADSamplingCallback callback);
extern void (*KPADInit)();
extern void (*KPADShutdown)();
extern int32_t (*KPADRead)(KPADChan chan, KPADStatus* data, uint32_t size);
extern int32_t (*KPADReadEx)(KPADChan chan, KPADStatus* data, uint32_t size, KPADError* error);

#ifdef __cplusplus
}
#endif
