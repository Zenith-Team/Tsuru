#pragma once

#include <stdint.h>

typedef enum VPADChan {
    //! Channel 0.
    VPAD_CHAN_0 = 0,
    //! Channel 1.
    VPAD_CHAN_1 = 1,
} VPADChan;

typedef enum {
    //! Indicates that there is pending data which can be received
    VPAD_IRC_STATUS_FLAG_HAS_DATA = 1,
    //! Indicates that another device is connected
    VPAD_IRC_STATUS_FLAG_CONNECTED = 2,
} VPADIRCStatusFlags;

typedef struct VPADAccStatus VPADAccStatus;
typedef struct VPADDirection VPADDirection;
typedef struct VPADGyroStatus VPADGyroStatus;
typedef struct VPADStatus VPADStatus;
typedef struct VPADTouchCalibrationParam VPADTouchCalibrationParam;
typedef struct VPADTouchData VPADTouchData;
typedef struct VPADVec2D VPADVec2D;
typedef struct VPADVec3D VPADVec3D;

//! Wii U GamePad buttons.
typedef enum VPADButtons {
    //! The A button.
    VPAD_BUTTON_A = 0x8000,
    //! The B button.
    VPAD_BUTTON_B = 0x4000,
    //! The X button.
    VPAD_BUTTON_X = 0x2000,
    //! The Y button.
    VPAD_BUTTON_Y = 0x1000,
    //! The left button of the D-pad.
    VPAD_BUTTON_LEFT = 0x0800,
    //! The right button of the D-pad.
    VPAD_BUTTON_RIGHT = 0x0400,
    //! The up button of the D-pad.
    VPAD_BUTTON_UP = 0x0200,
    //! The down button of the D-pad.
    VPAD_BUTTON_DOWN = 0x0100,
    //! The ZL button.
    VPAD_BUTTON_ZL = 0x0080,
    //! The ZR button.
    VPAD_BUTTON_ZR = 0x0040,
    //! The L button.
    VPAD_BUTTON_L = 0x0020,
    //! The R button.
    VPAD_BUTTON_R = 0x0010,
    //! The + button.
    VPAD_BUTTON_PLUS = 0x0008,
    //! The - button.
    VPAD_BUTTON_MINUS = 0x0004,
    //! The HOME button.
    VPAD_BUTTON_HOME = 0x0002,
    //! The SYNC button.
    VPAD_BUTTON_SYNC = 0x0001,
    //! The right stick button.
    VPAD_BUTTON_STICK_R = 0x00020000,
    //! The left stick button.
    VPAD_BUTTON_STICK_L = 0x00040000,
    //! The TV button.
    VPAD_BUTTON_TV = 0x00010000,
    //! The emulated left button on the right stick.
    VPAD_STICK_R_EMULATION_LEFT = 0x04000000,
    //! The emulated right button on the right stick.
    VPAD_STICK_R_EMULATION_RIGHT = 0x02000000,
    //! The emulated up button on the right stick.
    VPAD_STICK_R_EMULATION_UP = 0x01000000,
    //! The emulated down button on the right stick.
    VPAD_STICK_R_EMULATION_DOWN = 0x00800000,
    //! The emulated left button on the left stick.
    VPAD_STICK_L_EMULATION_LEFT = 0x40000000,
    //! The emulated right button on the left stick.
    VPAD_STICK_L_EMULATION_RIGHT = 0x20000000,
    //! The emulated up button on the left stick.
    VPAD_STICK_L_EMULATION_UP = 0x10000000,
    //! The emulated down button on the left stick.
    VPAD_STICK_L_EMULATION_DOWN = 0x08000000,
} VPADButtons;

//! Touch pad validity.
typedef enum VPADTouchPadValidity {
    //! Both X and Y touchpad positions are accurate.
    VPAD_VALID = 0x0,

    //! X position is inaccurate.
    VPAD_INVALID_X = 0x1,

    //! Y position is inaccurate.
    VPAD_INVALID_Y = 0x2,
} VPADTouchPadValidity;

//! Touch pad resolution.
typedef enum VPADTouchPadResolution {
    //! 1920 x 1080 resolution.
    VPAD_TP_1920X1080 = 0,
    //! 1280 x 720 resolution.
    VPAD_TP_1280X720 = 1,
    //! 854 x 480 resolution.
    VPAD_TP_854X480 = 2,
} VPADTouchPadResolution;

//! Read error.
typedef enum VPADReadError {
    //! No error occurred, and data was written to the buffers.
    VPAD_READ_SUCCESS = 0,
    //! There was no sample new data available to write.
    VPAD_READ_NO_SAMPLES = -1,
    //! The requested controller or channel was invalid.
    VPAD_READ_INVALID_CONTROLLER = -2,
    //! VPAD channel is busy, perhaps being accessed by another thread
    VPAD_READ_BUSY = -4,
    //! VPAD is uninitialized, need to call VPADInit()
    VPAD_READ_UNINITIALIZED = -5,
} VPADReadError;

//! LCD mode.
typedef enum VPADLcdMode {
    //! Display is in standby and will turn back on if any buttons are pressed.
    VPAD_LCD_STANDBY = 0,
    //! Display is completely off and will remain so until explicitly changed.
    VPAD_LCD_OFF = 1,
    //! Display is on as normal.
    VPAD_LCD_ON = 0xFF,
} VPADLcdMode;

//! Gyro zero drift mode.
typedef enum VPADGyroZeroDriftMode {
    VPAD_GYRO_ZERODRIFT_LOOSE = 0,
    VPAD_GYRO_ZERODRIFT_STANDARD,
    VPAD_GYRO_ZERODRIFT_TIGHT,
    VPAD_GYRO_ZERODRIFT_NONE
} VPADGyroZeroDriftMode;

//! 2D vector.
struct VPADVec2D {
    //! x.
    float x;
    //! y.
    float y;
};

//! 3D vector.
struct VPADVec3D {
    //! x.
    float x;
    //! y.
    float y;
    //! z.
    float z;
};

//! Direction.
struct VPADDirection {
    //! x.
    VPADVec3D x;
    //! y.
    VPADVec3D y;
    //! z.
    VPADVec3D z;
};

//! Touch calibration parameter.
struct VPADTouchCalibrationParam {
    //! X offset.
    uint16_t adjustX;
    //! Y offset.
    uint16_t adjustY;
    //! X scale.
    float scaleX;
    //! Y scale.
    float scaleY;
};

//! Touch data.
struct VPADTouchData {
    //! The x-coordinate of a touched point.
    uint16_t x;
    //! The y-coordinate of a touched point.
    uint16_t y;

    //! 0 if screen is not currently being touched.
    uint16_t touched;

    //! Bitfield of #VPADTouchPadValidity to indicate how touch sample accuracy.
    uint16_t validity;
};

struct VPADAccStatus {
    VPADVec3D acc;
    float magnitude;
    float variation;
    VPADVec2D vertical;
};

struct VPADStatus {
    //! Indicates what VPADButtons are held down.
    uint32_t hold;

    //! Indicates what VPADButtons have been pressed since last sample.
    uint32_t trigger;

    //! Indicates what VPADButtons have been released since last sample.
    uint32_t release;

    //! Position of left analog stick.
    VPADVec2D leftStick;

    //! Position of right analog stick.
    VPADVec2D rightStick;

    //! Status of DRC accelorometer.
    VPADAccStatus accelorometer;

    //! Status of DRC gyro.
    VPADVec3D gyro;

    //! Status of DRC angle.
    VPADVec3D angle;

    uint8_t error;

    char _unk[0x1];

    //! Current touch position on DRC.
    VPADTouchData tpNormal;

    //! Filtered touch position, first level of smoothing.
    VPADTouchData tpFiltered1;

    //! Filtered touch position, second level of smoothing.
    VPADTouchData tpFiltered2;

    char _unk2[0x2];

    VPADDirection direction;

    //! Set to 1 if headphones are plugged in, 0 otherwise.
    bool usingHeadphones;

    //! Status of DRC magnetometer.
    VPADVec3D mag;

    //! Current volume set by the slide control.
    uint8_t slideVolume;

    //! Battery level of controller.
    uint8_t battery;

    //! Status of DRC microphone.
    uint8_t micStatus;

    //! Unknown volume related value.
    uint8_t slideVolumeEx;

    char _unk3[0x8];
};

typedef void (*VPADSamplingCallback)(VPADChan chan);
