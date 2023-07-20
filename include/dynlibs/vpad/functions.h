#pragma once

#include "dynlibs/vpad/types.h"

#ifdef __cplusplus
#include <cstring>
extern "C" {
#else
#include <string.h>
#endif

#include "dynlibs/gx2/types.h"
#include "dynlibs/os/types.h"

void InitVPADFunctionPointers(void);
void InitAcquireVPAD(void);

extern void (*VPADBASEInit)();
extern void (*VPADBASEShutdown)();
extern bool (*VPADBASEIsInit)();
extern int32_t (*VPADBASEGetMotorOnRemainingCount)(VPADChan chan);
extern int32_t (*VPADBASESetMotorOnRemainingCount)(VPADChan chan, int32_t counter);
extern void (*VPADBASESetSensorBarSetting)(VPADChan chan, int8_t setting);
extern void (*VPADBASEGetSensorBarSetting)(VPADChan chan, int8_t* outSetting);
extern int32_t (*VPADBASEGetHeadphoneStatus)(VPADChan chan);
extern void (*VPADBASEGetGameControllerMode)(VPADChan chan, int32_t* mode);
extern void (*VPADBASESetGameControllerMode)(VPADChan chan, int32_t mode);
extern void (*VPADBASEGetPowerButtonPressStatus)(VPADChan chan, uint32_t* tick, uint32_t* status);
extern void (*VPADBASESetPowerButtonPressStatus)(VPADChan chan, uint32_t tick, uint32_t status);
extern void (*VPADBASESetPowerButtonDisableMode)(VPADChan chan, uint32_t mode);
extern void (*VPADBASEClearIRCEvent)(VPADChan chan);
extern VPADIRCStatusFlags (*VPADBASEGetIRCStatus)(VPADChan chan);
extern void (*VPADInit)();
extern void (*VPADShutdown)();
extern int32_t (*VPADRead)(VPADChan chan, VPADStatus* buffers, uint32_t count, VPADReadError* outError);
extern void (*VPADGetTPCalibrationParam)(VPADChan chan, VPADTouchCalibrationParam* outParam);
extern void (*VPADSetTPCalibrationParam)(VPADChan chan, const VPADTouchCalibrationParam* param);
extern void (*VPADGetTPCalibratedPoint)(VPADChan chan, VPADTouchData* calibratedData, const VPADTouchData* uncalibratedData);
extern void (*VPADGetTPCalibratedPointEx)(VPADChan chan, VPADTouchPadResolution tpResolution, VPADTouchData* calibratedData, const VPADTouchData* uncalibratedData);
extern void (*VPADSetAccParam)(VPADChan chan, float playRadius, float sensitivity);
extern void (*VPADGetAccParam)(VPADChan chan, float* outPlayRadius, float* outSensitivity);
extern void (*VPADSetBtnRepeat)(VPADChan chan, float delaySec, float pulseSec);
extern void (*VPADEnableStickCrossClamp)(VPADChan chan);
extern void (*VPADDisableStickCrossClamp)(VPADChan chan);
extern void (*VPADSetLStickClampThreshold)(VPADChan chan, int32_t max, int32_t min);
extern void (*VPADSetRStickClampThreshold)(VPADChan chan, int32_t max, int32_t min);
extern void (*VPADGetGyroDirReviseParam)(VPADChan chan, float* param);
extern void (*VPADGetGyroZeroDriftMode)(VPADChan chan, VPADGyroZeroDriftMode* mode);
extern void (*VPADGetLStickClampThreshold)(VPADChan chan, int32_t* max, int32_t* min);
extern void (*VPADGetRStickClampThreshold)(VPADChan chan, int32_t* max, int32_t* min);
extern void (*VPADSetStickOrigin)(VPADChan chan);
extern void (*VPADDisableLStickZeroClamp)(VPADChan chan);
extern void (*VPADDisableRStickZeroClamp)(VPADChan chan);
extern void (*VPADEnableLStickZeroClamp)(VPADChan chan);
extern void (*VPADEnableRStickZeroClamp)(VPADChan chan);
extern void (*VPADSetCrossStickEmulationParamsL)(VPADChan chan, float rotationDegree, float range, float radius);
extern void (*VPADSetCrossStickEmulationParamsR)(VPADChan chan, float rotationDegree, float range, float radius);
extern void (*VPADGetCrossStickEmulationParamsL)(VPADChan chan, float* outRotationDegree, float* outRange, float* outRadius);
extern void (*VPADGetCrossStickEmulationParamsR)(VPADChan chan, float* outRotationDegree, float* outRange, float* outRadius);
extern void (*VPADSetGyroAngle)(VPADChan chan, float ax, float ay, float az);
extern void (*VPADSetGyroDirReviseBase)(VPADChan chan, VPADDirection* base);
extern void (*VPADSetGyroDirReviseParam)(VPADChan chan, float param);
extern void (*VPADSetGyroDirection)(VPADChan chan, VPADDirection* dir);
extern void (*VPADSetGyroDirectionMag)(VPADChan chan, float mag);
extern void (*VPADSetGyroMagnification)(VPADChan chan, float pitch, float yaw, float roll);
extern void (*VPADSetGyroZeroDriftMode)(VPADChan chan, VPADGyroZeroDriftMode mode);
extern void (*VPADEnableGyroZeroPlay)(VPADChan chan);
extern void (*VPADEnableGyroDirRevise)(VPADChan chan);
extern void (*VPADEnableGyroAccRevise)(VPADChan chan);
extern void (*VPADDisableGyroZeroPlay)(VPADChan chan);
extern void (*VPADDisableGyroDirRevise)(VPADChan chan);
extern void (*VPADDisableGyroAccRevise)(VPADChan chan);
extern float (*VPADIsEnableGyroZeroPlay)(VPADChan chan);
extern float (*VPADIsEnableGyroZeroDrift)(VPADChan chan);
extern float (*VPADIsEnableGyroDirRevise)(VPADChan chan);
extern float (*VPADIsEnableGyroAccRevise)(VPADChan chan);
extern void (*VPADSetGyroZeroPlayParam)(VPADChan chan, float radius);
extern void (*VPADInitGyroZeroPlayParam)(VPADChan chan);
extern void (*VPADInitGyroDirReviseParam)(VPADChan chan);
extern void (*VPADInitGyroAccReviseParam)(VPADChan chan);
extern void (*VPADStartGyroMagRevise)(VPADChan chan);
extern void (*VPADStopGyroMagRevise)(VPADChan chan);
extern void (*VPADInitGyroZeroDriftMode)(VPADChan chan);
extern bool (*VPADGetTVMenuStatus)(VPADChan chan);
extern void (*VPADSetTVMenuInvalid)(VPADChan chan, bool invalid);
extern void (*VPADDisablePowerButton)(VPADChan chan);
extern void (*VPADEnablePowerButton)(VPADChan chan);
extern int32_t (*VPADControlMotor)(VPADChan chan, uint8_t* pattern, uint8_t length);
extern void (*VPADStopMotor)(VPADChan chan);
extern int32_t (*VPADSetLcdMode)(VPADChan chan, VPADLcdMode lcdMode);
extern int32_t (*VPADGetLcdMode)(VPADChan chan, VPADLcdMode* outLcdMode);
extern int32_t (*VPADSetSensorBar)(VPADChan chan, bool on);
extern VPADSamplingCallback (*VPADSetSamplingCallback)(VPADChan chan, VPADSamplingCallback callback);

#ifdef __cplusplus
}
#endif
