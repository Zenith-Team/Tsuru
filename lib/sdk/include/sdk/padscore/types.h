#pragma once

#include <stdint.h>

typedef struct WPADStatusProController WPADStatusProController;
typedef struct WPADVec2D WPADVec2D;

//! Wii Remote channel.
typedef enum WPADChan {
    //! Channel 0.
    WPAD_CHAN_0 = 0,
    //! Channel 1.
    WPAD_CHAN_1 = 1,
    //! Channel 2.
    WPAD_CHAN_2 = 2,
    //! Channel 3.
    WPAD_CHAN_3 = 3,
} WPADChan;

//! Data format.
typedef enum WPADDataFormat {
    WPAD_FMT_PRO_CONTROLLER = 22,
} WPADDataFormat;

//! Extension type.
typedef enum WPADExtensionType {
    //! Wii Remote with no extension.
    WPAD_EXT_CORE = 0,
    //! Nunchuk.
    WPAD_EXT_NUNCHUK = 1,
    //! Classic Controller.
    WPAD_EXT_CLASSIC = 2,
    //! Motion Plus.
    WPAD_EXT_MPLUS = 5,
    //! Motion Plus with Nunchuk.
    WPAD_EXT_MPLUS_NUNCHUK = 6,
    //! Motion Plus with Classic Controller.
    WPAD_EXT_MPLUS_CLASSIC = 7,
    //! Pro Controller.
    WPAD_EXT_PRO_CONTROLLER = 31,
} WPADExtensionType;

//! Wii Remote buttons.
typedef enum WPADButton {
    //! The left button of the D-pad.
    WPAD_BUTTON_LEFT = 0x0001,
    //! The right button of the D-pad.
    WPAD_BUTTON_RIGHT = 0x0002,
    //! The down button of the D-pad.
    WPAD_BUTTON_DOWN = 0x0004,
    //! The up button of the D-pad.
    WPAD_BUTTON_UP = 0x0008,
    //! The + button.
    WPAD_BUTTON_PLUS = 0x0010,
    //! The 2 button.
    WPAD_BUTTON_2 = 0x0100,
    //! The 1 button.
    WPAD_BUTTON_1 = 0x0200,
    //! The B button.
    WPAD_BUTTON_B = 0x0400,
    //! The A button.
    WPAD_BUTTON_A = 0x0800,
    //! The - button.
    WPAD_BUTTON_MINUS = 0x1000,
    //! The Z button on the Nunchuk extension.
    WPAD_BUTTON_Z = 0x2000,
    //! The C button on the Nunchuk extension.
    WPAD_BUTTON_C = 0x4000,
    //! The HOME button.
    WPAD_BUTTON_HOME = 0x8000,
} WPADButton;

//! Nunchuk buttons.
typedef enum WPADNunchukButton {
    //! The emulated left button on the Nunchuk stick or the left button of the D-pad on the Wii Remote.
    WPAD_NUNCHUK_STICK_EMULATION_LEFT = 0x0001,
    //! The emulated right button on the Nunchuk stick or the right button of the D-pad on the Wii Remote.
    WPAD_NUNCHUK_STICK_EMULATION_RIGHT = 0x0002,
    //! The emulated down button on the Nunchuk stick or the down button of the D-pad on the Wii Remote.
    WPAD_NUNCHUK_STICK_EMULATION_DOWN = 0x0004,
    //! The emulated up button on the Nunchuk stick or the up button of the D-pad on the Wii Remote.
    WPAD_NUNCHUK_STICK_EMULATION_UP = 0x0008,
    //! The Z button.
    WPAD_NUNCHUK_BUTTON_Z = 0x2000,
    //! The C button.
    WPAD_NUNCHUK_BUTTON_C = 0x4000,
} WPADNunchukButton;

//! Classic Controller buttons.
typedef enum WPADClassicButton {
    //! The up button of the D-pad.
    WPAD_CLASSIC_BUTTON_UP = 0x00000001,
    //! The left button of the D-pad.
    WPAD_CLASSIC_BUTTON_LEFT = 0x00000002,
    //! The ZR button.
    WPAD_CLASSIC_BUTTON_ZR = 0x00000004,
    //! The X button.
    WPAD_CLASSIC_BUTTON_X = 0x00000008,
    //! The A button.
    WPAD_CLASSIC_BUTTON_A = 0x00000010,
    //! The Y button.
    WPAD_CLASSIC_BUTTON_Y = 0x00000020,
    //! The B button.
    WPAD_CLASSIC_BUTTON_B = 0x00000040,
    //! The ZL button.
    WPAD_CLASSIC_BUTTON_ZL = 0x00000080,
    //! The R button.
    WPAD_CLASSIC_BUTTON_R = 0x00000200,
    //! The + button.
    WPAD_CLASSIC_BUTTON_PLUS = 0x00000400,
    //! The HOME button.
    WPAD_CLASSIC_BUTTON_HOME = 0x00000800,
    //! The - button.
    WPAD_CLASSIC_BUTTON_MINUS = 0x00001000,
    //! The L button.
    WPAD_CLASSIC_BUTTON_L = 0x00002000,
    //! The down button of the D-pad.
    WPAD_CLASSIC_BUTTON_DOWN = 0x00004000,
    //! The right button of the D-pad.
    WPAD_CLASSIC_BUTTON_RIGHT = 0x00008000,
    //! The emulated left button on the left stick.
    WPAD_CLASSIC_STICK_L_EMULATION_LEFT = 0x00010000,
    //! The emulated right button on the left stick.
    WPAD_CLASSIC_STICK_L_EMULATION_RIGHT = 0x00020000,
    //! The emulated down button on the left stick.
    WPAD_CLASSIC_STICK_L_EMULATION_DOWN = 0x00040000,
    //! The emulated up button on the left stick.
    WPAD_CLASSIC_STICK_L_EMULATION_UP = 0x00080000,
    //! The emulated left button on the right stick.
    WPAD_CLASSIC_STICK_R_EMULATION_LEFT = 0x00100000,
    //! The emulated right button on the right stick.
    WPAD_CLASSIC_STICK_R_EMULATION_RIGHT = 0x00200000,
    //! The emulated down button on the right stick.
    WPAD_CLASSIC_STICK_R_EMULATION_DOWN = 0x00400000,
    //! The emulated up button on the right stick.
    WPAD_CLASSIC_STICK_R_EMULATION_UP = 0x00800000,
} WPADClassicButton;

//! Pro Controller buttons.
typedef enum WPADProButton {
    //! The up button of the D-pad.
    WPAD_PRO_BUTTON_UP = 0x00000001,
    //! The left button of the D-pad.
    WPAD_PRO_BUTTON_LEFT = 0x00000002,
    //! The ZR button.
    WPAD_PRO_TRIGGER_ZR = 0x00000004,
    //! The X button.
    WPAD_PRO_BUTTON_X = 0x00000008,
    //! The A button.
    WPAD_PRO_BUTTON_A = 0x00000010,
    //! The Y button.
    WPAD_PRO_BUTTON_Y = 0x00000020,
    //! The B button.
    WPAD_PRO_BUTTON_B = 0x00000040,
    //! The ZL button.
    WPAD_PRO_TRIGGER_ZL = 0x00000080,
    //! Reserved.
    WPAD_PRO_RESERVED = 0x00000100,
    //! The right trigger button.
    WPAD_PRO_TRIGGER_R = 0x00000200,
    //! The + button.
    WPAD_PRO_BUTTON_PLUS = 0x00000400,
    //! The HOME button.
    WPAD_PRO_BUTTON_HOME = 0x00000800,
    //! The - button.
    WPAD_PRO_BUTTON_MINUS = 0x00001000,
    //! The left trigger button.
    WPAD_PRO_TRIGGER_L = 0x00002000,
    //! The down button of the D-pad.
    WPAD_PRO_BUTTON_DOWN = 0x00004000,
    //! The right button of the D-pad.
    WPAD_PRO_BUTTON_RIGHT = 0x00008000,
    //! The right stick button.
    WPAD_PRO_BUTTON_STICK_R = 0x00010000,
    //! The left stick button.
    WPAD_PRO_BUTTON_STICK_L = 0x00020000,
    //! The emulated up button on the left stick.
    WPAD_PRO_STICK_L_EMULATION_UP = 0x00200000,
    //! The emulated down button on the left stick.
    WPAD_PRO_STICK_L_EMULATION_DOWN = 0x00100000,
    //! The emulated left button on the left stick.
    WPAD_PRO_STICK_L_EMULATION_LEFT = 0x00040000,
    //! The emulated right button on the left stick.
    WPAD_PRO_STICK_L_EMULATION_RIGHT = 0x00080000,
    //! The emulated up button on the right stick.
    WPAD_PRO_STICK_R_EMULATION_UP = 0x02000000,
    //! The emulated down button on the right stick.
    WPAD_PRO_STICK_R_EMULATION_DOWN = 0x01000000,
    //! The emulated left button on the right stick.
    WPAD_PRO_STICK_R_EMULATION_LEFT = 0x00400000,
    //! The emulated right button on the right stick.
    WPAD_PRO_STICK_R_EMULATION_RIGHT = 0x00800000,
} WPADProButton;

//! 2D vector.
struct WPADVec2D {
    //! x.
    int16_t x;
    //! y.
    int16_t y;
};

struct WPADStatusProController {
    char _0[0x28];

    //! A value from WPADExtensionType.
    uint8_t extensionType;

    uint8_t err;
    char unk[0x2];
    uint32_t buttons;
    WPADVec2D leftStick;
    WPADVec2D rightStick;
    char unk2[0x8];
    WPADDataFormat dataFormat;
};

typedef void (*WPADSamplingCallback)(WPADChan chan);
typedef void (*WPADExtensionCallback)(WPADChan chan, int32_t status);
typedef void (*WPADConnectCallback)(WPADChan chan, int32_t status);

//! Wii Remote channel.
typedef enum WPADChan KPADChan;
//! Data format.
typedef enum WPADDataFormat KPADDataFormat;
//! Extension type.
typedef enum WPADExtensionType KPADExtensionType;

typedef struct KPADStatus KPADStatus;
typedef struct KPADVec2D KPADVec2D;
typedef struct KPADVec3D KPADVec3D;

//! Error.
typedef enum KPADError {
    //! No error occurred, and data was written to the buffers.
    KPAD_ERROR_OK = 0,
    //! There was no sample new data available to write.
    KPAD_ERROR_NO_SAMPLES = -1,
    //! The requested controller or channel was invalid.
    KPAD_ERROR_INVALID_CONTROLLER = -2,
    //! WPAD is uninitialized, shouldn't happen unless WPADShutdown() is manually called
    KPAD_ERROR_WPAD_UNINIT = -3,
    //! KPAD channel is busy, perhaps being accessed by another thread
    KPAD_ERROR_BUSY = -4,
    //! KPAD is uninitialized, need to call KPADInit()
    KPAD_ERROR_UNINITIALIZED = -5,
} KPADError;

//! 2D vector.
struct KPADVec2D {
    //! x.
    float x;
    //! y.
    float y;
};

//! 3D vector.
struct KPADVec3D {
    //! x.
    float x;
    //! y.
    float y;
    //! z.
    float z;
};

//! A structure conataining the Wii Remote data.
struct KPADStatus {
    //! Indicates what KPADButtons are held down.
    uint32_t hold;

    //! Indicates what KPADButtons have been pressed since last sample.
    uint32_t trigger;

    //! Indicates what KPADButtons have been released since last sample.
    uint32_t release;

    //! Indicates the value of the acceleration sensor.
    KPADVec3D acc;

    //! Indicates the magnitude of acceleration.
    float accMagnitude;

    //! Indicates the variation in acceleration.
    float accVariation;

    //! Indicates the position where the Wii Remote is pointing.
    KPADVec2D pos;

    char unk3[3 * 4];

    //! Angle.
    KPADVec2D angle;

    char unk2[8 * 4];

    //! Value from KPADExtensionType.
    uint8_t extensionType;

    //! Value from KPADError.
    int8_t error;

    //! Validity of the result.
    int8_t posValid;

    //! Value from KPADDataFormat.
    uint8_t format;

    //! Extension data, check with extensionType to see what is valid to read.
    union {
        //! Structure to use when extension type is set to \link WPAD_EXT_NUNCHUK \endlink.
        struct
        {
            //! Position of the analog stick.
            KPADVec2D stick;
            //! Indicates the value of the acceleration sensor.
            KPADVec3D acc;
            //! Indicates the magnitude of acceleration.
            float accMagnitude;
            //! Indicates the variation in acceleration.
            float accVariation;
            //! Indicates what buttons are held down.
            uint32_t hold;
            //! Indicates what buttons have been pressed since last sample.
            uint32_t trigger;
            //! Indicates what buttons have been released since last sample.
            uint32_t release;
        } nunchuck;

        //! Structure to use when extension type is set to \link WPAD_EXT_CLASSIC \endlink.
        struct
        {
            //! Indicates what buttons are held down.
            uint32_t hold;
            //! Indicates what buttons have been pressed since last sample.
            uint32_t trigger;
            //! Indicates what buttons have been released since last sample.
            uint32_t release;
            //! Position of left analog stick.
            KPADVec2D leftStick;
            //! Position of right analog stick.
            KPADVec2D rightStick;
            //! Left trigger.
            float leftTrigger;
            //! Right trigger.
            float rightTrigger;
        } classic;

        //! Structure to use when extension type is set to \link WPAD_EXT_PRO_CONTROLLER \endlink.
        struct
        {
            //! Indicates what buttons are held down.
            uint32_t hold;
            //! Indicates what buttons have been pressed since last sample.
            uint32_t trigger;
            //! Indicates what buttons have been released since last sample.
            uint32_t release;
            //! Position of left analog stick.
            KPADVec2D leftStick;
            //! Position of right analog stick.
            KPADVec2D rightStick;
            //! Is charging flag.
            int32_t charging;
            //! Is wired flag.
            int32_t wired;
        } pro;

        char unk[20 * 4];
    };

    char unk4[16 * 4];
};
